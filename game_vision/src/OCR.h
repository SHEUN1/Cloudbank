/*
 * 		  Name:OCR.h
 *
 *  Created on: 18 Aug 2017
 *      Author: Olu Adebari
 *
 * Description:Identify characters in the image
 */

#ifndef OCR_H_
#define OCR_H_

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/text/ocr.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
#include <string>
#include "ImageText.h"

class OCR {

public:
	OCR();
	virtual ~OCR() = default;

/** *****************************************************************************************
	  *  @Name		 FindSuitableOcrValues
	  *
	  *  @brief      display results of all possible oem and psmode values to determine the
	  *  			 most suitable values.
	  *
	  *  @param      cv::Mat &img: Original non-processed image frame
	  ****************************************************************************************/
	void FindSuitableOcrValues(cv::Mat &img);

/** *****************************************************************************************
	 *  @Name 		GetWordsAndLocations
	 *
	 *  @brief      get ImageText objects containing identified text in an image and their locations
	 *
	 *  @param      cv::Mat &img:  Original non-processed image frame
	 *
	 *  @return		std::vector< std::shared_ptr<ImageText> >: collection of ImageText objects
	 ****************************************************************************************/
	std::vector< std::shared_ptr<ImageText> >  GetWordsAndLocations(cv::Mat &img);
};

#endif /* OCR_H_ */
