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
#include <opencv2/opencv.hpp>

typedef enum
{
	RGBD_ENH = 0,
	UML_RGB_ENH,
	UML_ENH,
	PWAS_RGB_ENH,
	PWAS_ENH,
	JBU_ENH,
	BIL_ENH,
	JBUK_ENH,
	NJBU_ENH,
	NAFDU_ENH
} Enhancement_filters;

typedef enum
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

class c_DataFusion;

class DepthEnhancement
{
public:
	explicit DepthEnhancement();
	~DepthEnhancement();

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
	void updateDataFusion();
	void setResolution(int width, int height);
private:
	c_DataFusion *m_DataFusion; // Instance to Data Fusion class

	cv::Mat m_cvDepthImage; // Depth map
	cv::Mat m_cvRGBImage; // Guidance image

	short   m_sXRes; // X Resolution
	short   m_sYRes; // Y Resolution
	short   m_sScaleFactor; // Scale Factor
};

#endif // DepthEnhancement_H
