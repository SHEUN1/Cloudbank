/*
 * SeperateObjects.h
 *
 *  Created on: 9 Jul 2017
 *      Author: sheun
 */
#ifndef SEPERATEOBJECTS_H_
#define SEPERATEOBJECTS_H_

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <algorithm>
#include <stdlib.h>
#include <map>


using namespace std;
using namespace cv;



class SeperateObjects {

private:


public:

	SeperateObjects();
	virtual ~SeperateObjects();
	//return an grayscaleimage with bound boxes around each object in the image
	vector <Mat>  BoundBox(Mat Binary, Mat origanal_image, Mat Original_image_clone, int world_number, vector<int>& x_coordinate, vector<int>& y_coordinate, bool save_image_result);


};

#endif /* SEPERATEOBJECTS_H_ */
