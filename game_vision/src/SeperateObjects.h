/*
 *        Name: SeperateObjects.h
 *
 *  Created on: 9 Jul 2017
 *      Author: sheun
 *
 *      Description: create RegionOfinterest objects.
 */

#ifndef SEPERATEOBJECTS_H_
#define SEPERATEOBJECTS_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <stdlib.h>

#include "BinaryImage.h"
#include "RecordProcessedImage.h"
#include "RegionOfInterest.h"
class SeperateObjects {

private:
	cv::Mat mGrayScale;
	cv::Mat mOriginal_image_clone;
	cv::Mat mColorCrop;

	RecordProcessedImage m_record_processed_image;

public:

/** *****************************************************************************************
	 *  @name       SeperateObjects
	 *
	 *  @brief      constructor
	 *
	 *
	 *  @param      cv::Mat: grayscale image
	 *  @param      cv::Mat: unprocessed pre-grayscale image
	****************************************************************************************/
	SeperateObjects(cv::Mat grayscaleImage, cv::Mat & image);
	virtual ~SeperateObjects() = default;

/** *****************************************************************************************
	 *  @name       BoundBox
	 *
	 *  @brief      identify a region of interest and get their X and Y coordinates in the image frame
	 *
	 *
	 *  @param      std::shared_ptr< BinaryImage>: Binary image
	 *  @param      bool: indicate wheather an image should be saved
    ****************************************************************************************/
	void BoundBox(std::shared_ptr< BinaryImage>  Binary, bool saveImage);


};

#endif /* SEPERATEOBJECTS_H_ */
