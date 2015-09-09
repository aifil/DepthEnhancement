/*
* Author: Frederic GARCIA BECERRO
* Email: frederic.garcia.becerro@gmail.com
* Website: http://www.frederic-garcia-becerro.com
*/

#ifndef DepthEnhancement_H
#define DepthEnhancement_H

// Std
#include <fstream>
#include <string>

// OpenCV
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/contrib/contrib.hpp"
// Include Data Fusion class
#include "c_datafusion.h"

enum
{
	RGBD_ENH = 0,
	UML_RGB_ENH,
	UML_ENH,
	PWAS_RGB_ENH,
	PWAS_ENH,
	JBU_ENH,
	BIL_ENH,
	JBU_ENH,
	NJBU_ENH,
	NAFDU_ENH
} Enhancement_filters;

enum
{
	GDANCE_I_RGB_RES = 0,
	GDANCE_I_RES,
	DWNSMP_I_RES,
	DMAP_RES,
	DWNSMP_DMAP_RES,
	CRED_MAP_RES,
	DWNSMP_CRED_MAP_RES,
	BLEND_MASK_RES,
	ENH_DMAP_RES
} Enhancement_results;

class DepthEnhancement
{
public:
	explicit DepthEnhancement();
	~DepthEnhancement();

	void setResolution(int width, int height);
	void setScaleFactor(short index);

	void setSigmaSpatial(int value);
	void setSigmaRange(int value);
	void setSigmaCredMap(int value);

	void loadDepthMap(const cv::Mat &depth_mat);
	void loadImage(const cv::Mat &image_mat);

	void applyFilter(int filterIndex);
	cv::Mat resultImage(int resultIndex);
	void saveResultImage(const std::string &filename, int resultIndex);
	void printAbout();
private:
	void on_ui_cb_dataFusion_Display_currentIndexChanged(int index);

	void updateDataFusion();
private:
	c_DataFusion *m_DataFusion; // Instance to Data Fusion class

	cv::Mat m_cvDepthImage; // Depth map
	cv::Mat m_cvRGBImage; // Guidance image
	bool    m_bDepthImageLoaded; // Flag to indicate loaded depth map
	bool    m_bRGBImageLoaded; // Flag to indicate loaded RGB image

	short   m_sXRes; // X Resolution
	short   m_sYRes; // Y Resolution
	short   m_sScaleFactor; // Scale Factor
};

#endif // DepthEnhancement_H
