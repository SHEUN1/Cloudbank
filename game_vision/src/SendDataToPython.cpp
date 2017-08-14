/*
 * SendDataToPython.cpp
 *
 *  Created on: 14 Aug 2017
 *      Author: sheun
 */

#include "SendDataToPython.h"

SendDataToPython::SendDataToPython() {
	// TODO Auto-generated constructor stub

}

SendDataToPython::~SendDataToPython() {
	// TODO Auto-generated destructor stub
}


boost::python::dict SendDataToPython::featurePointToDict(vector< vector<KeyPoint> > vectorToSend)
{
	//iterator for each objects
	typename vector< vector<KeyPoint> >::iterator iterEachObject;
	//iterator for each keypoint for each object
	typename vector<KeyPoint>::iterator iterKeyPoints;

	//feature array
	boost::python::list keyPointList;

	//map/dictionary will hold the keypoints acciociated with each object
	boost::python::dict keypointMap;
	int i = 0;


	for (iterEachObject = vectorToSend.begin(); iterEachObject != vectorToSend.end(); ++iterEachObject)
	{
		// hold a collection of all keypoints belonging to the object
		boost::python::list CollectionOfKeypointArrayForEachObject;

		//create a list of individual keypoints
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

		CollectionOfKeypointArrayForEachObject.append(keyPointList);
		keypointMap[i] = CollectionOfKeypointArrayForEachObject;
		++i;

	}

	return keypointMap;
}
