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
	Mat1b imadjust(const Mat1b& src, Mat1b& dst, int tol, Vec2i in, Vec2i out);
	Mat1b cleanupBinary (Mat1b Binary);
public:
	ying_yang();
	virtual ~ying_yang();
	Mat1b binary (Mat1b img);
	Mat1b binary_Inverse (Mat1b img);


};

#endif
