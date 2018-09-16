/*
 *        Name: ConvertToBinaryImage.h
 *
 *  Created on: 13 Jun 2017
 *      Author: Olu Adebari
 *
 *  Description: convert an image into a binary image.
 */
#ifndef CONVERTTOBINARYIMAGE_H_
#define CONVERTTOBINARYIMAGE_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

class ConvertToBinaryImage {

private:

/** *****************************************************************************************
	 *  @name      cleanupBinary
	 *
	 *  @brief     remove a small amount of noise from a binary image
	 *
	 *  @param     cv::Mat: Binary image
	 *
	 *  @return    cv::Mat: Binary image
	 ****************************************************************************************/

	cv::Mat cleanUpBinary (cv::Mat Binary);

/** *****************************************************************************************
	 *  @name      watershedSegmentation
	 *
	 *  @brief     use the Watershed segmentation method to create a segmented binary image
	 *
	 *  @param     cv::Mat: Binary Image
	 *  @param     cv::Mat: original non-grayscale image
	 *
	 *  @return    cv::Mat: segmented Binary image
	 ****************************************************************************************/
	cv::Mat  watershedSegmentation(cv::Mat binary_image, cv::Mat origanal_colour_image);

public:
	ConvertToBinaryImage();
	virtual ~ConvertToBinaryImage() = default;

 /** *****************************************************************************************
	 *  @name       convertToBinary
	 *
	 *  @brief      convert grayscale image into a binary image
	 *
	 *  @param      cv::Mat: grayscale image
	 *  @param      cv::Mat: origanal non-grayscale image
	 *
	 *  @return     Mat Binary image
	 ****************************************************************************************/

	cv::Mat convertToBinary (cv::Mat const &img, cv::Mat origanal);

/** *****************************************************************************************
	 *  @name       convertToBinaryInverse
	 *
	 *  @brief      convert grayscale image into a binary image
	 *
	 *  @param      cv::Mat: grayscale image
	 *  @param      cv::Mat: origanal non-grayscale image
	 *
	 *  @return     Mat Binary image
	 ****************************************************************************************/
	cv::Mat convertToBinaryInverse (cv::Mat const &img, cv::Mat origanal);


};

#endif
