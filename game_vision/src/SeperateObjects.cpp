/*
 *        Name: SeperateObjects.cpp
 *
 *  Created on: 9 Jul 2017
 *      Author: Olu Adebari
 *
 * Description: create RegionOfinterest objects.
 */

#include "SeperateObjects.h"


SeperateObjects::SeperateObjects(cv::Mat grayscaleImage, cv::Mat & image) : mGrayScale(grayscaleImage), mOriginal_image_clone(image) {

	std::cout<<"identyfying objects in seperate objects class"<<std::endl;


}

void SeperateObjects::BoundBox(std::shared_ptr< BinaryImage>  Binary, bool saveImage)
{
	auto image_to_crop_out_objects = mOriginal_image_clone.clone();
	//bounded box will be draw on this copy of the original image instead
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	//find contours
	findContours(Binary->getBinaryImage(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

	 /// Get the moments(weighted average of image pixels intensities )
	  std::vector<cv::Moments> mu(contours.size());
	  for( uint32_t i = 0; i < contours.size(); i++ )
	     { mu[i] = moments( contours[i], false ); }

	  ///  Get the mass centres:
	    std::vector<cv::Point2f> mc( contours.size() );
	    for( uint32_t i = 0; i < contours.size(); i++ )
	       { mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

	//Approximate contours to polygons + get bounding rects
	std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	cv::Rect boundRect;

	//delete all images in a folder
	if (saveImage)
	{
		std::string cmdExecution = "exec rm -rf ../game_vision/cloudbank_images/objects/objects_belonging_to_binary_"+ std::to_string(Binary->getID())+"/*";
		system(cmdExecution.c_str());
	}


	for(uint32_t i = 0; i < contours.size(); ++i)
	{

		approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);

		//remove bounded box that covers the entire frame.
		if (((boundingRect(cv::Mat(contours_poly[i])).width == mGrayScale.cols) && (boundingRect(cv::Mat(contours_poly[i])).height == mGrayScale.rows)))
		{
			continue;
		}

		boundRect = boundingRect(cv::Mat(contours_poly[i]));
		cv::Scalar color( rand()&255, rand()&255, rand()&255 );
		rectangle (mOriginal_image_clone, boundRect.tl(), boundRect.br(), color, 2,8,0);


		Binary->addRegionOfInterest(i, mGrayScale(boundRect),((boundRect.x + boundRect.width) / 2), ((boundRect.y + boundRect.height) / 2),boundingRect(cv::Mat(contours_poly[i])));
	    //save regions of interest into a folder
	    if (saveImage)
	    {
	    	m_record_processed_image.saveImage(image_to_crop_out_objects(boundRect),"../game_vision/cloudbank_images/objects/objects_belonging_to_binary_"+ std::to_string(Binary->getID()),
	    		"Image_"+std::to_string(Binary->getID())+"_ID_"+std::to_string(i)+".jpg");
		}


	}


}
