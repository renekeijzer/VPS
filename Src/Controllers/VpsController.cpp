#include "VpsController.h"

VpsController::VpsController(cv::VideoCapture & feed) : 
feed (feed), running(false)
{
	start = elapsedTime = time_t(0);
	running = true;
	std::thread VpsThread(&VpsController::run, this);
	VpsThread.detach();

}


void VpsController::run(){
	while(running){
		prevImage = currentImage;
		feed >> currentImage;


		std::this_thread::sleep_for(std::chrono::seconds(1));
		elapsedTime = time_t(0);
	}
}