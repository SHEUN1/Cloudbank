/*
 * featureextraction.cpp
 *
 *  Created on: 24 Jul 2017
 *      Author: sheun
 */

#include "featureextraction.h"

feature_extraction::feature_extraction() {
	// TODO Auto-generated constructor stub

}

feature_extraction::~feature_extraction() {
	// TODO Auto-generated destructor stub
}

vector<vector<KeyPoint> > feature_extraction::featurePoints(vector<Mat1b> images)
{
	vector<Mat1b> images_clone = images;
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	vector<vector<KeyPoint> > keypoints;
	char file [50];
	for(int i = 0; i < images.size(); i++)
	{
		detector -> detect(images[i], keypoints[i]);
		//Draw keypoints
		Mat img_keypoints_1;
		drawKeypoints(images_clone[i], keypoints[i], img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
		//save regions of interest into a folder
		sprintf(file,"../../trasistor_vision_saved_images_features/Image%d.jpg",i);
		imwrite(file,img_keypoints_1);
	}

 return keypoints;
}

