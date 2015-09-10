/*
* Author: Frederic GARCIA BECERRO
* Email: frederic.garcia.becerro@gmail.com
* Website: http://www.frederic-garcia-becerro.com
*/

#include <depth_enhancement.h>

int main(int argc, char *argv[])
{
	
	cv::Mat limg8 = cv::imread(argv[1]);
	cv::Mat d;

	std::string arg2 = argv[2];
	std::string ext = arg2.substr(arg2.size() - 4, 4);
	bool text = (ext == std::string(".txt"));

	printf("DepthEnhancement\n");
	DepthEnhancement depth_enh;

	printf("load data\n");
	depth_enh.loadImage(limg8);
	if (text)
		depth_enh.loadDepthMap(arg2, limg8.size());
	else
	{
		d = cv::imread(arg2, 0);
		depth_enh.loadDepthMap(d);
	}

	printf("setScaleFactor\n");
	depth_enh.setScaleFactor(0);
	
	printf("setSigma\n");
	depth_enh.setSigmaCredMap(10);
	depth_enh.setSigmaRange(10);
	depth_enh.setSigmaSpatial(10);
	
	printf("applyFilter\n");
	int filter = atoi(argv[3]);
	printf("filter = %d\n", filter);
	depth_enh.applyFilter(filter);
	
	printf("resultImage\n");
	int result = Enhancement_results::ENH_DMAP_RES;
	cv::Mat enhmap = depth_enh.resultImage(result);
	
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
	cv::imwrite(std::string(std::string("dmap_") + std::to_string(filter) + std::string(".png")), enhmap8);

	return 0;
}
