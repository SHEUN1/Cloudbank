/*
 * featureextraction.h
 *
 *  Created on: 24 Jul 2017
 *      Author: sheun
 *
 *      Identify and extract features from objects
 */

#ifndef FEATUREEXTRACTION_H_
#define FEATUREEXTRACTION_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"


using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

class feature_extraction {
public:
	feature_extraction();
	virtual ~feature_extraction();

/**
	 *****************************************************************************************
	 *  @brief      get feature points of each objects in the vector
	 *
	 *
	 *
	 *
	 *  @param      vector of objects
	 *  @param      indicate which directory to save separated object/regions images (only effective is last parameter is set to "true"). 0 = darkworld/non-contrasted binary image; 1 = lightworld/contrasted binary images
	 *  @param 		true = save separated objects/regions in directory of your choice
	 *  @param		DEFAULT = SIFT, 2 = ORB, 3 = BRISK, 4 = SURF
	 *  @return     vector of keypoints per object
	 ****************************************************************************************/

	vector< vector<KeyPoint> > featurePoints (vector<Mat> image,int world_number, bool save_image_result, int extractorType=0);


};

#endif /* FEATUREEXTRACTION_H_ */
