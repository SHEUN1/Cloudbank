/*
 * 		  Name: RecordProcessedImage.h
 *
 *  Created on: 1 Jun 2018
 *      Author: Olu Adebari
 *
 * Description: save images into system file directory
 */

#ifndef RECORDPROCESSEDIMAGE_H_
#define RECORDPROCESSEDIMAGE_H_

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <opencv2/opencv.hpp>
#include "BinaryImage.h"

class RecordProcessedImage {
private:
	std::unordered_set<std::string> m_existing_dir;

public:
	RecordProcessedImage();
	virtual ~RecordProcessedImage() = default;

/** *****************************************************************************************
	 *  @name		saveImage
	 *
	 *  @brief		save image into destination folder
	 *
	 *  @param      cv::Mat: image to save
	 *
	 *  @param 		std::string: name of destination folder
	 *
	 *  @param 		std::string: file name
	 ****************************************************************************************/
	void saveImage(const cv::Mat &capturedFrame, std::string fileDestination, std::string fileName);

/** *****************************************************************************************
	 *  @name		getCreatedDir
	 *
	 *  @brief		receive collection of directories that have been created
	 *
	 *  @return 	std::unordered_set<std::string>: collection of directories
	 ****************************************************************************************/
	std::unordered_set<std::string> getCreatedDir() const;


};

#endif /* RECORDPROCESSEDIMAGE_H_ */
