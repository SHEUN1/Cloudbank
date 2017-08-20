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


#include<stdio.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <algorithm>
#include <map>
#include <iterator>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

using namespace std;
using namespace cv;

class SendDataToPython {
public:
	SendDataToPython();
	virtual ~SendDataToPython();

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
	 *  @return     python dictionary
	 ****************************************************************************************/

	boost::python::dict objectInformationToDict(vector< vector<KeyPoint> > vectorToSend, vector<int>x_coordinate,vector<int>y_coordinate,  pair< vector<string>, vector < pair< int , int  > > > testing);
};

#endif /* SENDDATATOPYTHON_H_ */
