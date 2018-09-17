/*
 *        Name: FeatureExtraction.h
 *
 *  Created on: 24 Jul 2017
 *      Author: Olu Adebari
 *
 * Description: Identify and extract feature points from images
 */

#ifndef FEATUREEXTRACTION_H_
#define FEATUREEXTRACTION_H_

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

#include "BinaryImage.h"
#include "RecordProcessedImage.h"

template<typename T>
class FeatureExtraction {
private:
	RecordProcessedImage m_record_processed_image;
public:
	FeatureExtraction();
	virtual ~FeatureExtraction() = default;

/*******************************************************************************************
	 *  @name   extractFeaturePoints
	 *
	 *  @brief  get feature points of each objects in the vector
	 *
	 *  @param  std::shared_ptr<BinaryImage>: binary image
	 *  @param 	bool: save image with feature points into directory
	 ****************************************************************************************/

	void extractFeaturePoints (std::shared_ptr<BinaryImage> binary, bool save_image_result);

};


template <typename T>
FeatureExtraction<T>::FeatureExtraction()
{

	std::cout<<"extracting features"<<std::endl;
}

template <typename T>
void FeatureExtraction<T>::extractFeaturePoints (std::shared_ptr<BinaryImage> binary, bool save_image_result)
{
	auto min_hessian = 400;
	auto detector = T::create(min_hessian);
	std::vector<cv::KeyPoint> detected_keypoints;


	//delete contents within a file
	if (save_image_result)
	{
		std::string cmd_execution = "exec rm -rf ../game_vision/cloudbank_images/objects/objects_with_feature_points/objects_belonging_to_binary_"+ std::to_string(binary->getID())+"/*";
		system(cmd_execution.c_str());

	}

	cv::Mat img_with_keypoints_drawn_on;

	for(auto ROI : binary->getAllRegionsOfInterest())
	{
		detector->detect(ROI->getImage(), detected_keypoints);
		ROI->setFeaturePoints(detected_keypoints);

		drawKeypoints(ROI->getImage(), ROI->getFeaturePoints(), img_with_keypoints_drawn_on, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

		//save images within a file
		if ( save_image_result)
		{
			m_record_processed_image.saveImage(img_with_keypoints_drawn_on,"../game_vision/cloudbank_images/objects/objects_with_feature_points/objects_belonging_to_binary_"+ std::to_string(binary->getID()),
				    		"Image_"+std::to_string(binary->getID())+"_ID_"+std::to_string(ROI->getRegionOfInterestID())+".jpg");
		}
	}

}

#endif /* FEATUREEXTRACTION_H_ */
