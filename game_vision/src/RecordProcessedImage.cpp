/*
 * 		  Name: RecordProcessedImage.cpp
 *
 *  Created on: 1 Jun 2018
 *      Author: Olu Adebari
 *
 * Description: save images into system file directory
 */

#include "RecordProcessedImage.h"

RecordProcessedImage::RecordProcessedImage(){}


void RecordProcessedImage::saveImage(const cv::Mat &capturedFrame, std::string fileDestination, std::string fileName){
	char file [200];
	if (m_existing_dir.find(fileDestination)==m_existing_dir.end()){
		std::string cmdExecution = "mkdir -p " + fileDestination;
		system(cmdExecution.c_str());
		m_existing_dir.insert(fileDestination);
	}
	sprintf(file,"%s/%s",fileDestination.c_str(), fileName.c_str());
	imwrite(file,capturedFrame);
}

std::unordered_set<std::string> RecordProcessedImage::getCreatedDir() const {
	return m_existing_dir;
}
