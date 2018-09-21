/*
 *       Name: SendDataToPython.h
 *
 *  Created on: 14 Aug 2017
 *      Author: Olu Adebari
 *
 * Description: send data over to Python project
 */

#ifndef SENDDATATOPYTHON_H_
#define SENDDATATOPYTHON_H_



#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <memory>
#include "BinaryImage.h"
#include "ImageText.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>


class SendDataToPython {
public:
	SendDataToPython();
	virtual ~SendDataToPython() = default;

/** *****************************************************************************************
	 *  @Name 		SendObjectInformationToDict
	 *
	 *  @brief      create a Python dictionary to send over to Python code file
	 *
	 *
	 *  @param      std::vector< std::shared_ptr<BinaryImage> >: vector of BinaryuImages
	 *  @param 		std::vector< std::shared_ptr<ImageText> >:  Vector of ImageText
	 *
	 *  @return     Python dictionary
	 ****************************************************************************************/

	boost::python::dict SendObjectInformationToDict(std::vector< std::shared_ptr<BinaryImage> > binaryImages, std::vector< std::shared_ptr<ImageText> > words);
};

#endif /* SENDDATATOPYTHON_H_ */
