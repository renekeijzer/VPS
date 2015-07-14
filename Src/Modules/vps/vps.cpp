#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "VpsController.h"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;


int main( int argc, const char** argv )
{
    VideoCapture cap(0); // open the default camera
    VpsController controller (cap);
    for(;;){}
    return 0;
}
