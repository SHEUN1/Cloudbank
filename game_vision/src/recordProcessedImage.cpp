/*
 * recordProcessedImage.cpp
 *
 *  Created on: 1 Jun 2018
 *      Author: sheun
 *
 *      save/record processed images for the current frame being analysed
 */

#include "recordProcessedImage.h"

recordProcessedImage::recordProcessedImage(uint32_t  FrameNumber, uint32_t Number_of_frames_to_record):mFrameNumber(FrameNumber), mNumber_of_frames_to_record(Number_of_frames_to_record)  {}

/**
 *****************************************************************************************
 *  @brief		Optional: save processed image frames of current captured video game frame.
 *
 *  @param      <Mat>un-modified origanal image frame
 ****************************************************************************************/

void recordProcessedImage::capturedframe(cv::Mat const &capturedFrame){
	sprintf(mFile,"../game_vision/cloudbank_images/Frame/Image%d.jpg",mFrameNumber);
	imwrite(mFile,capturedFrame);
}

/**
 *****************************************************************************************
 *  @brief		Optional: save processed image frames of current captured video game frame
 *  						displaying bounded boxes.
 *
 *  @param      <Mat>image with bounded box draw on it
 ****************************************************************************************/
void recordProcessedImage::boundbox(cv::Mat const &Original_image_clone){
	sprintf(mFile,"../game_vision/cloudbank_images/Bounded_box_on_image/Image%d.jpg",mFrameNumber);
	imwrite(mFile,Original_image_clone);
}

/**
 *****************************************************************************************
 *  @brief		Optional: save processed image frames of current captured video game frame
 *  						in binary form.
 *
 *  @param      <Mat>binary image frame for the dark world
 ****************************************************************************************/
void recordProcessedImage::dark_world_Binary(cv::Mat const &dark_world_view){
	sprintf(mFile,"../game_vision/cloudbank_images/objects_waterfall_binary/darkworld/Image%d.jpg",mFrameNumber);
	imwrite(mFile,dark_world_view);
}

/**
 *****************************************************************************************
 *  @brief		Optional: save processed image frames of current captured video game frame
 *  						in inverse binary form.
 *
 *  @param      <Mat>binary image frame for the light world
 ****************************************************************************************/

void recordProcessedImage::light_world_Binary(cv::Mat const &light_world_view){
	sprintf(mFile,"../game_vision/cloudbank_images/objects_waterfall_binary/lightworld/Image%d.jpg",mFrameNumber);
	imwrite(mFile,light_world_view);

}

