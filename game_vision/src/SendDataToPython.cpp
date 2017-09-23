/*
 * SendDataToPython.cpp
 *
 *  Created on: 14 Aug 2017
 *      Author: sheun
 *
 *      send data over to python project
 */

#include "SendDataToPython.h"

SendDataToPython::SendDataToPython() {
	cout<<"sending image data to python"<<endl;

}

SendDataToPython::~SendDataToPython() {

}

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
	 *  @param      vector which will hold y coordinates of each object/region
	 *  @param 		vector<Rect> boundRectWorld will hold the corner points of the rectangle that acts as the bounded box
	 *  @return     python dictionary
	 ****************************************************************************************/

boost::python::dict SendDataToPython::objectInformationToDict(vector< vector<KeyPoint> > vectorToSend, vector<int>x_coordinate,vector<int>y_coordinate,  vector<Rect> boundRectWorld, pair< vector<string>, vector < pair< int , int  > > > words)
{

	//iterator for each objects
	typename vector< vector<KeyPoint> >::iterator iterEachObject;
	//iterator for each keypoint for each object
	typename vector<KeyPoint>::iterator iterKeyPoints;

	//map/dictionary will hold the keypoints acciociated with each object
	boost::python::dict keypointMap;
	int i = 0;

	for (iterEachObject = vectorToSend.begin(); iterEachObject != vectorToSend.end(); ++iterEachObject)
	{

		//feature arrays

		boost::python::list objectInformation;// overall list that will hold objects coordinate position in the image and its feature point
		boost::python::list keyPointList; // list holding objects keypoint
		boost::python::list coorPointList; // list holding objects x and y coordinates in the image.
		boost::python::list boundBoxCorners; // list holding objects boundBoxCorners in the image.

		coorPointList.append(x_coordinate[i]);
		coorPointList.append(y_coordinate[i]);


		objectInformation.append(coorPointList);

		boundBoxCorners.append(boundRectWorld[i].width);
		boundBoxCorners.append(boundRectWorld[i].height);
		boundBoxCorners.append(boundRectWorld[i].x);
		boundBoxCorners.append(boundRectWorld[i].y);

		objectInformation.append(boundBoxCorners);

		//get information of every identified keypoint of the objects and put that into a list
		for(iterKeyPoints = iterEachObject->begin(); iterKeyPoints != iterEachObject->end(); ++iterKeyPoints)
		{

			boost::python::list individualKeypointArray;

			individualKeypointArray.append(iterKeyPoints->pt.x);
			individualKeypointArray.append(iterKeyPoints->pt.y);
			individualKeypointArray.append(iterKeyPoints->size);
			individualKeypointArray.append(iterKeyPoints->angle);
			individualKeypointArray.append(iterKeyPoints->response);
			individualKeypointArray.append(iterKeyPoints->octave);
			keyPointList.append(individualKeypointArray);
		}

		objectInformation.append(keyPointList);
		keypointMap[i] = objectInformation;

		++i;

	}

	//letter list that will be added to the end of the key point map.
	boost::python::list letters;

	boost::python::list collectionOfletters;

	for(uint32_t i = 0; i<words.first.size();i++)
	{

		collectionOfletters.append(words.first[i]);
	}
	//letters.append(collectionOfletters);
	vector < pair< int , int  > > wordXYPairs = words.second;
	boost::python::list XYPairs;

	for (uint32_t i = 0; i<wordXYPairs.size();i++)
	{

		boost::python::list coordinate;
		coordinate.append(wordXYPairs[i].first);
		coordinate.append(wordXYPairs[i].second);

		XYPairs.append(coordinate);
	}

	//append to the end of the map the identified characters in the image frame and there locations in the image

	letters.append(XYPairs);

	letters.append(collectionOfletters);

	keypointMap[i] = letters;

	return keypointMap;
}
