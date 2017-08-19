/*
 * OCR.h
 *
 *  Created on: 18 Aug 2017
 *      Author: sheun
 */
#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include "opencv2/text/ocr.hpp"
#include<iostream>
#include<vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <string>
#ifndef OCR_H_
#define OCR_H_

using namespace cv;
using namespace std;
class OCR {
private:
	typedef pair<int,int> coordinates;
	typedef string words;
public:
	OCR();
	virtual ~OCR();

/**
 *****************************************************************************************
 *  @brief      optional:Iterate and display results through all possible oem and psmode values so that you determine the
						 most suitable values by printing the results out.

 *  @param      Original (non-processed) image frame
 *  @return
 ****************************************************************************************/
	void find_suitable_ocr_values(Mat img);
/**
 *****************************************************************************************
 *  @brief      optional:Iterate and display results through all possible oem and psmode values so that you determine the
						 most suitable values
 *
 *  @param      Original (non-processed) image frame
 *  @return     pair of characters in images and their associated x and y positions.
 ****************************************************************************************/
	pair< vector<string>, vector < pair< int , int  > > >  getWords(Mat img);
};

#endif /* OCR_H_ */
