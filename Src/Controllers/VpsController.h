#ifndef __VPSCONTROLLER__
#define __VPSCONTROLLER__
#include "mingw.thread.h"
#include "Waypoint.h"
#include "opencv2/opencv.hpp"
#include <ctime>

class VpsController{
public:
	VpsController(cv::VideoCapture & feed);
private:
	cv::VideoCapture & feed;
	cv::Mat currentImage, prevImage;


	void run();

	time_t start;
	time_t elapsedTime;

	std::map<time_t, Waypoint> Map;
	bool running;

};


#endif