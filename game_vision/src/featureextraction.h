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

#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

#include "tbb/tbb.h"

using namespace tbb;
template<typename T>
class feature_extraction {
private:
	void save_ROI_images (int world_number, int lock_dark_file, int lock_light_file, cv::Mat img_keypoints_1, uint32_t UROI_number);
public:
	feature_extraction();
	virtual ~feature_extraction() = default;

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

	std::vector< std::vector<cv::KeyPoint> > FeaturePoints_OCL (std::vector<cv::Mat> const &image,int world_number, bool save_image_result);

	std::vector< std::vector<cv::KeyPoint> > FeaturePoints_CUDA (std::vector<cv::Mat> image,int world_number, bool save_image_result);


};

template <typename T>
void feature_extraction<T>::save_ROI_images (int world_number, int lock_dark_file, int lock_light_file, cv::Mat img_keypoints_1, uint32_t ROI_number)
{
	char file [200];

	if (world_number == 0)
	{
		if (lock_dark_file == 0) {system("exec rm -rf ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/*");lock_dark_file++; }
		sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/Image%d.jpg",ROI_number);
	}
	else if(world_number == 1)
	{
		if (lock_light_file == 0) {system("exec rm -rf ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/*");lock_light_file++; }
		sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/Image%d.jpg",ROI_number);
	}

	imwrite(file,img_keypoints_1);
}

template <typename T>
feature_extraction<T>::feature_extraction()
{

	std::cout<<"extracting features"<<std::endl;
}

template <typename T>
std::vector < std::vector< cv::KeyPoint > > feature_extraction<T>::FeaturePoints_OCL(std::vector<cv::Mat> const &images,int world_number, bool save_image_result)
{

		std::vector<cv::Mat> images_clone = images;
		int minHessian = 400;
		cv::Ptr<T> detector = T::create(minHessian);
		//Hold all keypoints for 1 object temporarily
		std::vector<cv::KeyPoint> keypoints_hold_1_image;
		//hold every keypoint for every object. This is the vector that will be returned
		std::vector< std::vector<cv::KeyPoint> > keypoints;


		int lock_dark_file = 0;
		int lock_light_file = 0;

		cv::Mat img_keypoints_1;

		for(uint32_t i = 0; i < images.size(); i++)
		{

			detector->detect(images_clone[i], keypoints_hold_1_image);
			keypoints.push_back(keypoints_hold_1_image);

			//Draw keypoints
			drawKeypoints(images_clone[i], keypoints[i], img_keypoints_1, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

			//save regions of interest into a folder

			if ( save_image_result == true)
			{
				save_ROI_images ( world_number,  lock_dark_file,  lock_light_file,  img_keypoints_1, i);
			}
		}


	 return keypoints;


}

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
 *  @param		(DEFAULT/NO VALUE) = SURF_CUDA, 2 = SURF_CPU, 3 = SIFT_CPU
 *  @return     vector of keypoints per object
 ****************************************************************************************/

template <typename T>
std::vector < std::vector< cv::KeyPoint > > feature_extraction<T>::FeaturePoints_CUDA(std::vector<cv::Mat> images,int world_number, bool save_image_result)
{
//GPU SURF extraction



	T surf;
	std::vector<cv::Mat> imagesMAT;
	std::vector< cv::cuda::GpuMat > images_clone_gpu;
	cv::Mat imagesingleMAT;
	/*for(auto image : images)
	{
		imagesingleMAT = image.getMat(cv::ACCESS_READ);
		imagesMAT.push_back(imagesingleMAT);
	}*/
	//for(uint32_t i = 0; i < images.size(); i++)
	tbb::parallel_for( size_t(0), images.size(), [&]( size_t i )
	{
		//gpu surf will not take small sizes. objects have been resized to accommodate this.
		resize(images[i], images[i],  cvSize(200 , 200 ) );

		cv::cuda::GpuMat images_clone_1_image;
		images_clone_1_image.upload(images[i]);
		images_clone_gpu.push_back(images_clone_1_image);

	});

		//Hold all keypoints for 1 object temporarly
		std::vector<cv::KeyPoint> keypoints_hold_1_image;
		//hold every keypoint for every object. This is the vector that will be returned
		std::vector< std::vector<cv::KeyPoint> > keypoints(images.size());


		int lock_dark_file = 0;
		int lock_light_file = 0;

		//cv::Mat img_keypoints_1;

		//for(uint32_t i = 0; i < images.size(); i++)
		tbb::parallel_for( size_t(0), images.size(), [&]( size_t i )
		{
			cv::Mat img_keypoints_1;
			cv::cuda::GpuMat keypoints1GPU,descriptors1GPU;
			surf(images_clone_gpu[i], cv::cuda::GpuMat(), keypoints1GPU, descriptors1GPU);
			surf.downloadKeypoints(keypoints1GPU, keypoints_hold_1_image);
			keypoints[i]=keypoints_hold_1_image;

			//Draw keypoints
			drawKeypoints(images[i], keypoints[i], img_keypoints_1, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

			//save regions of interest into a folder
			if ( save_image_result == true)
			{
				save_ROI_images ( world_number,  lock_dark_file,  lock_light_file,  img_keypoints_1, i);

			}

		});


	 return keypoints;


}

#endif /* FEATUREEXTRACTION_H_ */
