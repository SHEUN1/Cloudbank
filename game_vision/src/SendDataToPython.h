/*
 * SendDataToPython.h
 *
 *  Created on: 14 Aug 2017
 *      Author: sheun
 *
 *      send data over to python project
 */

#ifndef SENDDATATOPYTHON_H_
#define SENDDATATOPYTHON_H_



#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>


class SendDataToPython {
public:
	SendDataToPython();
	virtual ~SendDataToPython() = default;

/**
	 *****************************************************************************************
	 *  @brief      create python dictionary to send over to python code file
	 *
	 *	@usage 		dictionary will contain
	 *				Objects: position in image and keypoints
	 *				OCR charters: characters and their position in the image
	 *
	 *
	 *  @param      vector of feature per objects
	 *  @param 		vector of x coordinates per object
	 *  @param 		vector of y coordinates per object
	 *  @param      (pair< vector<string>, vector < pair< int , int  > > >): pair of characters in images and their associated x and y positions.
	 *  @param 		vector<Rect> boundRectWorld will hold the corner points of the rectangle that acts as the bounded box
	 *  @return     python dictionary
	 ****************************************************************************************/

	boost::python::dict SendObjectInformationToDict(std::vector< std::vector<cv::KeyPoint> > vectorToSend, std::vector<int>x_coordinate,std::vector<int>y_coordinate, std::vector<cv::Rect> boundRectWorld ,std::pair< std::vector<std::string>,  std::vector < std::pair< int , int  > > > words);
};

#endif /* SENDDATATOPYTHON_H_ */
