/*
 * featureextraction.cpp
 *
 *  Created on: 24 Jul 2017
 *      Author: sheun
 *
 *      Identify and extract features from objects
 */

#include "featureextraction.h"

feature_extraction::feature_extraction() {
	cout<<"extracting features"<<endl;

}

feature_extraction::~feature_extraction() {

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

vector< vector<KeyPoint> > feature_extraction::featurePoints(vector<Mat> images,int world_number, bool save_image_result, int extractorType)
{

// CPU SURF extraction
if(extractorType == 2)
{
	vector<Mat> images_clone = images;
		int minHessian = 400;
		Ptr<SURF> detector = SURF::create(minHessian);
		//Hold all keypoints for 1 object temporarly
		vector<KeyPoint> keypoints_hold_1_image;
		//hold every keypoint for every object. This is the vector that will be returned
		vector< vector<KeyPoint> > keypoints;

		char file [200];
		int lock_dark_file = 0;
		int lock_light_file = 0;

		Mat img_keypoints_1;

		for(uint32_t i = 0; i < images.size(); i++)
		{

			detector->detect(images_clone[i], keypoints_hold_1_image);
			keypoints.push_back(keypoints_hold_1_image);

			//Draw keypoints
			drawKeypoints(images_clone[i], keypoints[i], img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

			//save regions of interest into a folder
			if ( save_image_result == true)
			{
				if (world_number == 0)
				{
					if (lock_dark_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/*");lock_dark_file++; }
					sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/Image%d.jpg",i);
				}
				else if(world_number == 1)
				{
					if (lock_light_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/*");lock_light_file++; }
					sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/Image%d.jpg",i);
				}

				imwrite(file,img_keypoints_1);
			}
		}


	 return keypoints;
}

// CPU SIFT extraction
if(extractorType == 3)
{
	vector<Mat> images_clone = images;
	int minHessian = 400;
	Ptr<SIFT> detector = SIFT::create(minHessian);
	//Hold all keypoints for 1 object temporarly
	vector<KeyPoint> keypoints_hold_1_image;
	//hold every keypoint for every object. This is the vector that will be returned
	vector< vector<KeyPoint> > keypoints;
	char file [200];
	int lock_dark_file = 0;
	int lock_light_file = 0;
	Mat img_keypoints_1;
	//
	//
	for(uint32_t i = 0; i < images.size(); i++)
	{

		detector->detect(images_clone[i], keypoints_hold_1_image);
		keypoints.push_back(keypoints_hold_1_image);

		//Draw keypoints
		drawKeypoints(images_clone[i], keypoints[i], img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

		//save regions of interest into a folder
		if ( save_image_result == true)
		{
			if (world_number == 0)
			{
				if (lock_dark_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/*");lock_dark_file++; }
				sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/Image%d.jpg",i);
			}
			else if(world_number == 1)
			{
				if (lock_light_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/*");lock_light_file++; }
				sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/Image%d.jpg",i);
			}

			imwrite(file,img_keypoints_1);
		}
	}


 return keypoints;
}

//cuda surf extraction
	cv::cuda::SURF_CUDA  surf;

	vector<Mat> images_clone = images;
	vector<cv::cuda::GpuMat > images_clone_gpu;

	for(uint32_t i = 0; i < images_clone.size(); i++)
	{
		//gpu surf will not take small sizes. objects have been resized to accommodate this.
		resize(images_clone[i], images_clone[i],  cvSize(200 , 200 ) );

		cv::cuda::GpuMat images_clone_1_image;
		images_clone_1_image.upload(images_clone[i]);
		images_clone_gpu.push_back(images_clone_1_image);

	}

		//Hold all keypoints for 1 object temporarly
		vector<KeyPoint> keypoints_hold_1_image;
		//hold every keypoint for every object. This is the vector that will be returned
		vector< vector<KeyPoint> > keypoints;

		char file [200];
		int lock_dark_file = 0;
		int lock_light_file = 0;

		Mat img_keypoints_1;

		for(uint32_t i = 0; i < images.size(); i++)
		{
			cv::cuda::GpuMat keypoints1GPU,descriptors1GPU;
			surf(images_clone_gpu[i], cv::cuda::GpuMat(), keypoints1GPU, descriptors1GPU);
			surf.downloadKeypoints(keypoints1GPU, keypoints_hold_1_image);
			keypoints.push_back(keypoints_hold_1_image);

			//Draw keypoints
			drawKeypoints(images_clone[i], keypoints[i], img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

			//save regions of interest into a folder
			if ( save_image_result == true)
			{
				if (world_number == 0)
				{
					if (lock_dark_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/*");lock_dark_file++; }
					sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_darkFeatures_images/Image%d.jpg",i);
				}
				else if(world_number == 1)
				{
					if (lock_light_file == 0) {system("exec rm -r ../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/*");lock_light_file++; }
					sprintf(file,"../game_vision/cloudbank_images/objects_with_feature_points/trasistor_vision_lightFeatures_images/Image%d.jpg",i);
				}

				imwrite(file,img_keypoints_1);
			}

		}


	 return keypoints;


}


