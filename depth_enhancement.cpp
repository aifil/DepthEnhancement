/*
* Author: Frederic GARCIA BECERRO
* Email: frederic.garcia.becerro@gmail.com
* Website: http://www.frederic-garcia-becerro.com
*/

#include <depth_enhancement.h>
// Include Data Fusion class
#include <c_datafusion.h>

DepthEnhancement::DepthEnhancement() : m_DataFusion(NULL) {}
DepthEnhancement::~DepthEnhancement()
{
	delete m_DataFusion;
}

void DepthEnhancement::setResolution(int width, int height)
{
	m_sXRes = width;
	m_sYRes = height;

	D_Fusion_2D_3D_2DW = m_sXRes; // By default we booked the maximum memory, considering VGA Res
	D_Fusion_2D_3D_2DH = m_sYRes;
	D_Fusion_2D_3D_2DSIZE = (D_Fusion_2D_3D_2DW * D_Fusion_2D_3D_2DH);
	D_Fusion_2D_3D_2DSIZE_RGB = (D_Fusion_2D_3D_2DW * D_Fusion_2D_3D_2DH * 3);

	D_Fusion_2D_3D_Spatial_downsample_rate = 0; // Default downsampling rate, can be [0,4] but I set it to 0 in order to book enough memory
	D_Fusion_2D_3D_2DW_DS = (D_Fusion_2D_3D_2DW >> D_Fusion_2D_3D_Spatial_downsample_rate);
	D_Fusion_2D_3D_2DH_DS = (D_Fusion_2D_3D_2DH >> D_Fusion_2D_3D_Spatial_downsample_rate);
	D_Fusion_2D_3D_2DSIZE_DS = (D_Fusion_2D_3D_2DW_DS * D_Fusion_2D_3D_2DH_DS);

	D_MEM_s32_DS = D_Fusion_2D_3D_2DSIZE_DS * sizeof(s32);
	D_MEM_u16_DS = D_Fusion_2D_3D_2DSIZE_DS * sizeof(u16);
	D_MEM_u08_DS = D_Fusion_2D_3D_2DSIZE_DS * sizeof(u08);
	D_MEM_s32 = D_Fusion_2D_3D_2DSIZE * sizeof(s32);
	D_MEM_u16 = D_Fusion_2D_3D_2DSIZE * sizeof(u16);
	D_MEM_u08 = D_Fusion_2D_3D_2DSIZE * sizeof(u08);
	D_MEM_RGB_u08 = D_Fusion_2D_3D_2DSIZE * 3;

	D_Fusion_2D_3D_MEM_SIZE = (21*D_MEM_s32_DS + 2*D_MEM_u16_DS + 5*D_MEM_u08_DS + 2*D_MEM_u16 + 7*D_MEM_u08 + D_MEM_RGB_u08); // Totally required memory

	updateDataFusion();
}

void DepthEnhancement::setScaleFactor(short index)
{
	index = std::max((short)0,std::min((short)4, index));
	m_sScaleFactor = index;
	D_Fusion_ScaleFactor = m_sScaleFactor;   // Scale factor: 1x,2x,4x,8x,16x

	updateDataFusion();
}

void DepthEnhancement::setSigmaSpatial(int value)
{
	value = std::max(0,std::min(100, value));
	if (m_DataFusion) m_DataFusion->SetSigmaS(value);
}

void DepthEnhancement::setSigmaRange(int value)
{
	value = std::max(0,std::min(100, value));
	if (m_DataFusion) m_DataFusion->SetSigmaR(value);
}

void DepthEnhancement::setSigmaCredMap(int value)
{
	value = std::max(0,std::min(100, value));
	if (m_DataFusion) m_DataFusion->SetSigmaQ(value);
}

void DepthEnhancement::loadDepthMap(const cv::Mat &depth_mat)
{
	if (depth_mat.channels() != 1)
	{
		printf("error: depth map channels != 1\n");
		return;
	}

	if (depth_mat.type() == CV_32FC1 || depth_mat.type() == CV_64FC1 || depth_mat.type() == CV_32SC1)
	{
		double minVal, maxVal;
		cv::minMaxLoc(depth_mat, &minVal, &maxVal);
		printf("depth_mat minval = %le\n", minVal);
		printf("depth_mat maxval = %le\n", maxVal);

		cv::Mat depth_mat2 = depth_mat.clone();
		depth_mat2 += -minVal + 1.0;
		depth_mat2 *= 1023.0/ (maxVal - minVal);
		depth_mat2.convertTo(m_cvDepthImage, CV_16U);

		cv::minMaxLoc(m_cvDepthImage, &minVal, &maxVal);
		printf("m_cvDepthImage minval = %le\n", minVal);
		printf("m_cvDepthImage maxval = %le\n", maxVal);
	}
	else if (depth_mat.type() != CV_16U)
	{
		depth_mat.convertTo(m_cvDepthImage, CV_16U);
	}

	cv::Mat out8;
	cv::Mat out = m_cvDepthImage.clone();

	out.convertTo(out8, CV_8U, 255.0 / 2000.0);
	cv::imwrite("originDepthMap.png", out8);
}

void DepthEnhancement::loadDepthMap(const std::string &textfile, const cv::Size &size)
{
	// Depth data to be filtered
	m_cvDepthImage.create(size, CV_16U);
	std::string filename = textfile.substr(0, textfile.size() - 4);

	unsigned short* l_pBuffer = (unsigned short*)m_cvDepthImage.data;
	std::ifstream l_fp_in;  // Declaration of input stream
	l_fp_in.open(textfile, std::ios::in);  // Open the input file stream
	if (l_fp_in.is_open())
	{
		unsigned short l_usAux;

		for (short y = 0; y<m_sYRes; y++)
		{
			for (short x = 0; x<m_sXRes; x++)
			{
				l_fp_in >> l_usAux; // Depth
				*l_pBuffer++ = l_usAux;
			}
		}
		l_fp_in.close();   // close the streams
	}

	cv::Mat out8;
	cv::Mat out = m_cvDepthImage.clone();
	out /= 16.0;
	out.convertTo(out8, CV_8U);
	cv::imwrite(std::string(filename + std::string(".png")), out8);
}

void DepthEnhancement::loadImage(const cv::Mat &image_mat)
{
	if (image_mat.type() != CV_8UC1 || image_mat.type() != CV_8UC3)
	{
		if (image_mat.channels() == 3)
			image_mat.convertTo(m_cvRGBImage, CV_8UC3);
		else
			image_mat.convertTo(m_cvRGBImage, CV_8UC1);
	}
	else
		m_cvRGBImage = image_mat.clone();

	if (m_cvRGBImage.channels() == 1)
		cv::cvtColor(m_cvRGBImage, m_cvRGBImage, CV_GRAY2RGB);
	else
		cv::cvtColor(m_cvRGBImage, m_cvRGBImage, CV_BGR2RGB);

	setResolution(m_cvRGBImage.cols, m_cvRGBImage.rows);
}

void DepthEnhancement::applyFilter(int filterIndex)
{
	if (m_cvDepthImage.empty() || m_cvRGBImage.empty())
	{
		printf("error: no depth map or image\n");
		return;
	}

	switch (filterIndex)
	{
		case RGBD_ENH: // RGB-D Filter
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, RGBD_FILTER);
			m_DataFusion->UML_RGB_Filter();
		break;
		case UML_RGB_ENH: // UML Filter (RGB)
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, UML_RGB_FILTER);
			m_DataFusion->UML_RGB_Filter();
			break;
		case UML_ENH: // UML Filter (Grayscale)
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, UML_FILTER);
			m_DataFusion->UML_Filter();
			break;
		case PWAS_RGB_ENH: // PWAS Filter (RGB)
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, PWAS_RGB_FILTER);
			m_DataFusion->PWAS_RGB_Filter();
			break;
		case PWAS_ENH: // PWAS Filter (Grayscale)
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, PWAS_FILTER);
			m_DataFusion->PWAS_Filter();
			break;
		case JBU_ENH: // JBU Filter
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, JBU_FILTER);
			m_DataFusion->JBU_Filter();
			break;
		case BIL_ENH: // Bilateral Filter
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, NULL, BF_FILTER);
			m_DataFusion->BF_Filter();
			break;
		case JBUK_ENH: // JBU Filter (Kopf et al.)
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, LITERATURE_FILTERS);
			m_DataFusion->JBU_Filter_Kopf();
			break;
		case NJBU_ENH: // NJBU Filter (Kim et al.)
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, LITERATURE_FILTERS);
			m_DataFusion->NJBU_Filter_Kim();
			break;
		case NAFDU_ENH: // NAFDU Filter (Chan et al.)
			m_DataFusion->DataProcessing((unsigned short*)m_cvDepthImage.data, (unsigned char*)m_cvRGBImage.data, LITERATURE_FILTERS);
			m_DataFusion->NAFDU_Filter_Chan();
			break;
		default:
			printf("error: no such filter\n");
			break;
	}
}

void DepthEnhancement::saveResultImage(const std::string &filename/* *.pgm */, int resultIndex)
{
	cv::imwrite(filename, resultImage(resultIndex));
}

cv::Mat DepthEnhancement::resultImage(int resultIndex)
{
	cv::Mat l_cvImage;
	unsigned char* l_ucData;
	unsigned short* l_usData;
	unsigned char* l_ucData_cv;
	unsigned short* l_usData_cv;
	long l_lSize;

	if (m_cvDepthImage.empty() || m_cvRGBImage.empty())
	{
		printf("error: no depth map or image\n");
		return cv::Mat();
	}

	switch (resultIndex)
	{
	case GDANCE_I_RGB_RES: // Guidance Image I_RGB
		l_cvImage.create(cv::Size(m_sXRes, m_sYRes), CV_8UC3);
		l_ucData = m_DataFusion->GetGuidanceImageRGB();
		l_ucData_cv = (unsigned char*)l_cvImage.data;
		l_lSize = m_sXRes*m_sYRes*3;
		while (l_lSize--)
			*l_ucData_cv++ = *l_ucData++;
		break;
	case GDANCE_I_RES: // Guidance Image I
		l_cvImage.create(cv::Size(m_sXRes, m_sYRes), CV_8UC1);
		l_ucData = m_DataFusion->GetGuidanceImage();
		l_ucData_cv = (unsigned char*)l_cvImage.data;
		l_lSize = m_sXRes*m_sYRes;
		while (l_lSize--)
			*l_ucData_cv++ = *l_ucData++;
		break;
	case DWNSMP_I_RES: // Downsampled Guidance Image I_ds
		l_cvImage.create(cv::Size(m_sXRes>>m_sScaleFactor, m_sYRes>>m_sScaleFactor), CV_8UC1);
		l_ucData = m_DataFusion->GetGuidanceImage_ds();
		l_ucData_cv = (unsigned char*)l_cvImage.data;
		l_lSize = (m_sXRes>>m_sScaleFactor)*(m_sYRes>>m_sScaleFactor);
		while (l_lSize--)
			*l_ucData_cv++ = *l_ucData++;
		break;
	case DMAP_RES: // Depth Map D
		l_cvImage.create(cv::Size(m_sXRes, m_sYRes), CV_16UC1);
		l_usData = m_DataFusion->GetDepthMap();
		l_usData_cv = (unsigned short*)l_cvImage.data;
		l_lSize = m_sXRes*m_sYRes;
		while (l_lSize--)
		{
			if (*l_usData == MLF_APP_MAX_DISTANCE)
				*l_usData_cv++ = 0;
			else
				*l_usData_cv++ = *l_usData;
			l_usData++;
		}
		break;
	case DWNSMP_DMAP_RES: // Downsampled Depth Map D_ds
		l_cvImage.create(cv::Size(m_sXRes>>m_sScaleFactor, m_sYRes>>m_sScaleFactor), CV_16UC1);
		l_usData = m_DataFusion->GetDepthMap_ds();
		l_usData_cv = (unsigned short*)l_cvImage.data;
		l_lSize = (m_sXRes>>m_sScaleFactor)*(m_sYRes>>m_sScaleFactor);
		while (l_lSize--)
		{
			if (*l_usData == MLF_APP_MAX_DISTANCE)
				*l_usData_cv++ = 0;
			else
				*l_usData_cv++ = *l_usData;
			l_usData++;
		}
		break;
	case CRED_MAP_RES: // Credibility Map Q
		l_cvImage.create(cv::Size(m_sXRes, m_sYRes), CV_8UC1);
		l_ucData = m_DataFusion->GetCredibilityMap();
		l_ucData_cv = (unsigned char*)l_cvImage.data;
		l_lSize = m_sXRes*m_sYRes;
		while (l_lSize--)
			*l_ucData_cv++ = 255-*l_ucData++; // Invert the image for display reasons
		break;
	case DWNSMP_CRED_MAP_RES: // Credibility Map Q_ds
		l_cvImage.create(cv::Size(m_sXRes>>m_sScaleFactor, m_sYRes>>m_sScaleFactor), CV_8UC1);
		l_ucData = m_DataFusion->GetCredibilityMap_ds();
		l_ucData_cv = (unsigned char*)l_cvImage.data;
		l_lSize = (m_sXRes>>m_sScaleFactor)*(m_sYRes>>m_sScaleFactor);
		while (l_lSize--)
			*l_ucData_cv++ = 255-*l_ucData++; // Invert the image for display reasons
		break;
	case BLEND_MASK_RES: // Blending Mask B
		l_cvImage.create(cv::Size(m_sXRes, m_sYRes), CV_8UC1);
		l_ucData = m_DataFusion->GetBlendingMask();
		l_ucData_cv = (unsigned char*)l_cvImage.data;
		l_lSize = m_sXRes*m_sYRes;
		while (l_lSize--)
			*l_ucData_cv++ = *l_ucData++;
		break;
	case ENH_DMAP_RES: // Enhanced Depth Map J
		l_cvImage.create(cv::Size(m_sXRes, m_sYRes), CV_16UC1);
		l_usData = m_DataFusion->GetEnhancedDepthData();
		l_usData_cv = (unsigned short*)l_cvImage.data;
		l_lSize = m_sXRes*m_sYRes;
		while (l_lSize--)
		{
			if (*l_usData == MLF_APP_MAX_DISTANCE)
				*l_usData_cv++ = 0;
			else
				*l_usData_cv++ = *l_usData;
			l_usData++;
		}
		break;
	default:
		printf("error: no such result index\n");
		break;
	}
	return l_cvImage;
}

void DepthEnhancement::printAbout()
{
	std::string str = std::string("About:\n\n");
	str += std::string("This tool implements the RGB-D, UML and PWAS filters presented at:\n\n")+
		std::string("Real-Time Depth Enhancement by Fusion for RGB-D Cameras\n")+
		std::string("Garcia, F. and Aouada, D. and Solignac, T. and Mirbach, B. and Ottersten, B.\n")+
		std::string("IET Computer Vision, v.7:5, pp.1-11, 2013\n\n")+
		std::string("A New Multi-lateral Filter for Real-Time Depth Enhancement\n")+
		std::string("Garcia, F. and Aouada, D. and Mirbach, B. and Solignac, T. and Ottersten, B.\n")+
		std::string("IEEE International Conference on Advanced Video and Signal-Based Surveillance (AVSS), pp.42-47, 2011\n\n")+
		std::string("Pixel Weighted Average Strategy for Depth Sensor Data Fusion\n")+
		std::string("Garcia, F. and Mirbach, B. and Ottersten, B. and Grandidier, F. and Cuesta, A.\n")+
		std::string("IEEE International Conference on Image Processing (ICIP), pp.2805-2808, 2010\n\n")+
		std::string("Download the papers at http://www.frederic-garcia-becerro.com\n");
	printf("%s", str.c_str());
}

void DepthEnhancement::updateDataFusion()
{
	float s, r, q;
	if (m_DataFusion)
	{
		s = m_DataFusion->GetSigmaS();
		r = m_DataFusion->GetSigmaR();
		q = m_DataFusion->GetSigmaQ();
		delete m_DataFusion;
		m_DataFusion = NULL;
	}
	else
	{
		s = r = q = 10;
	}

	m_DataFusion = new c_DataFusion(D_Fusion_2D_3D_2DW, D_Fusion_2D_3D_2DH, D_Fusion_ScaleFactor);
	m_DataFusion->SetSigmaS(s);
	m_DataFusion->SetSigmaR(r);
	m_DataFusion->SetSigmaQ(q);
}
