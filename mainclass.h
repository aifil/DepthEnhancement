/*
* Author: Frederic GARCIA BECERRO
* Email: frederic.garcia.becerro@gmail.com
* Website: http://www.frederic-garcia-becerro.com
*/

#ifndef MainClass_H
#define MainClass_H

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

class MainClass
{
public:
    explicit MainClass();

    void setResolution(int width, int height);
    void setScaleFactor(short index);

    void setMaxPaletteValue(short value);
    void setMinPaletteValue(short value);

    void setSigmaSpatial(int value);
    void setSigmaRange(int value);
    void setSigmaCredMap(int value);
private:
    void on_ui_pb_LoadDepthMap_clicked();
    void on_ui_pb_LoadGuidImage_clicked();
    void on_ui_pb_ApplyFilter_clicked();
    void on_ui_cb_dataFusion_Display_currentIndexChanged(int index);
    void on_ui_pb_SaveDisplayedImage_clicked();
    void on_actionAbout_triggered();

    void on_ui_cb_dataFusion_Downsampling_currentIndexChanged(int index);
private:
    c_DataFusion *m_DataFusion; // Instance to Data Fusion class

    cv::Mat m_cvDepthImage; // Depth map
    cv::Mat *m_cvRGBImage; // Guidance image
    bool    m_bDepthImageLoaded; // Flag to indicate loaded depth map
    bool    m_bRGBImageLoaded; // Flag to indicate loaded RGB image

    short   m_sXRes; // X Resolution
    short   m_sYRes; // Y Resolution
    short   m_sMaxPaletteValue; // Max palette value
    short   m_sMinPaletteValue; // Min palette value
    short   m_sScaleFactor; // Scale Factor
};

#endif // MainClass_H
