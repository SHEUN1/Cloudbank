/*
 * SendDataToPython.h
 *
 *  Created on: 14 Aug 2017
 *      Author: sheun
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

	boost::python::dict featurePointToDict(vector< vector<KeyPoint> > vectorToSend);
};

#endif /* SENDDATATOPYTHON_H_ */
