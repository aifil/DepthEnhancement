/*
* Author: Frederic GARCIA BECERRO
* Email: frederic.garcia.becerro@gmail.com
* Website: http://www.frederic-garcia-becerro.com
*/

#include <depth_enhancement.h>

int main(int argc, char *argv[])
{
	cv::Mat limg8 = cv::imread(argv[1]);
	cv::Mat d = cv::imread(argv[2]);


	printf("DepthEnhancement\n");
	DepthEnhancement depth_enh;
	printf("setScaleFactor\n");
	depth_enh.setScaleFactor(3);
	printf("load data\n");
	depth_enh.loadImage(limg8);
	depth_enh.loadDepthMap(d);

	depth_enh.setSigmaCredMap(10);
	depth_enh.setSigmaRange(10);
	depth_enh.setSigmaSpatial(10);
	printf("applyFilter\n");
	depth_enh.applyFilter(Enhancement_filters::RGBD_ENH);
	printf("resultImage\n");
	cv::Mat enhmap = depth_enh.resultImage(Enhancement_results::ENH_DMAP_RES);
	printf("enhmap8\n");
	cv::Mat enhmap8;
	if (enhmap.type() == CV_8UC1 || enhmap.type() == CV_8UC3)
		enhmap8 = enhmap;
	else
	{
		if (enhmap.channels() == 1)
		{
			double minVal, maxVal;
			cv::minMaxLoc(enhmap, &minVal, &maxVal);
			enhmap.convertTo(enhmap8, CV_8UC1, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));
		}
		else
		{
			printf("error: (enhmap.channels != 1) && (size of type > 1byte)\n");
		}
	}
	printf("imwrite enhance_dmap.png\n");
	cv::imwrite("enhance_dmap.png", enhmap8);
	return 0;
}
