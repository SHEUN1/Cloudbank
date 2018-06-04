/*
 * recordProcessedImage.h
 *
 *  Created on: 1 Jun 2018
 *      Author: sheun
 *
 *    save/record processed images for the current frame being analysed
 */

#ifndef RECORDPROCESSEDIMAGE_H_
#define RECORDPROCESSEDIMAGE_H_

#include <iostream>
#include <opencv2/opencv.hpp>

class recordProcessedImage {
private:
	uint32_t mFrameNumber;
	char mFile [200];
	uint32_t mNumber_of_frames_to_record;

public:
	recordProcessedImage(uint32_t mFrameNumber, uint32_t Number_of_frames_to_record);
	virtual ~recordProcessedImage(){};

	/**
	 *****************************************************************************************
	 *  @brief		Optional: save processed image frames of current captured video game frame.

	 *  @param      <Mat>un-modified origanal image frame
	 ****************************************************************************************/
	void capturedframe(cv::Mat const &capturedFrame);

	/**
	 *****************************************************************************************
	 *  @brief		Optional: save processed image frames of current captured video game frame
	 *  						displaying bounded boxes.
	 *
	 *
	 *  @param      <Mat>image with bounded box draw on it
	 ****************************************************************************************/
	void boundbox(cv::Mat const &Original_image_clone);

	/**
	 *****************************************************************************************
	 *  @brief		Optional: save processed image frames of current captured video game frame
	 *  						in binary form.
	 *
	 *  @param      <Mat>binary image frame for the dark world
	 ****************************************************************************************/
	void dark_world_Binary(cv::Mat const &dark_world_view);

	/**
	 *****************************************************************************************
	 *  @brief		Optional: save processed image frames of current captured video game frame
	 *  						in inverse binary form.
	 *
	 *  @param      <Mat>binary image frame for the light world
	 ****************************************************************************************/
	void light_world_Binary(cv::Mat const &light_world_view);

};

#endif /* RECORDPROCESSEDIMAGE_H_ */
