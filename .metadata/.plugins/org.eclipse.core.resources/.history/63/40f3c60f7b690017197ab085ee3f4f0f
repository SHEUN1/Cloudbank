//============================================================================
// Name        : transistor_vision.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <algorithm>

#include "yingyang.h"
#include "SeperateObjects.h"

using namespace std;
using namespace cv;


int main() {

	//get image
	Mat3b img = imread("/home/sheun/Pictures/transistor_images/transistor2.jpg");
	//grayscale, and use imadjust for high constrast version
	Mat1b gray;
	//convert to grayscale
	cvtColor(img, gray, COLOR_RGB2GRAY);
	//smooth image
	blur(gray, gray, Size(3,3));
    //convert to binary
	ying_yang world_view;
	Mat1b dark_world_view = world_view.binary(gray);
	Mat1b light_world_view = world_view.binary_Inverse(gray);
	imshow("dark world view", dark_world_view);
	imshow("light world view", light_world_view);

	SeperateObjects worldObjects;
	Mat1b bound_box_world_dark = worldObjects.BoundBox(dark_world_view);
	Mat1b bound_box_world_light = worldObjects.BoundBox(light_world_view);
	namedWindow( "Objects for the dark world", CV_WINDOW_NORMAL );
	namedWindow( "Objects for the light world", CV_WINDOW_NORMAL );
	imshow ("Objects for the dark world", bound_box_world_dark);
	imshow ("Objects for the light world", bound_box_world_light);

	cvWaitKey();
	return 0;
}
