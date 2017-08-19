/*

* yingyang.h
 *
 *  Created on: 13 Jun 2017
 *      Author: sheun
 */
#ifndef YINGYANG_H_
#define YINGYANG_H_

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <algorithm>


using namespace std;
using namespace cv;



class ying_yang {

private:


	Mat cleanupBinary (Mat Binary);
	Mat  Watershed(Mat Binary, Mat origanal_image);
public:
	ying_yang();
	virtual ~ying_yang();
	Mat binary (Mat img, Mat origanal);
	Mat binary_Inverse (Mat img, Mat origanal);


};

#endif
