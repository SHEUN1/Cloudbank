/*
 *       Name: SendDataToPython.cpp
 *
 *  Created on: 14 Aug 2017
 *      Author: Olu Adebari
 *
 * Description: send data over to Python project
 */

#include "SendDataToPython.h"

SendDataToPython::SendDataToPython() {
	std::cout<<"sending image data to python"<<std::endl;

}



boost::python::dict SendDataToPython::SendObjectInformationToDict(std::vector< std::shared_ptr<BinaryImage> > binaryImages, std::vector< std::shared_ptr<ImageText> > words)
{
	boost::python::dict object_data_dictionary;

	auto dict_index=0;
	for (const auto & binaryImage : binaryImages){

		for (const auto & roi : binaryImage->getAllRegionsOfInterest()){

			//feature arrays
			boost::python::list objectInformation;
			boost::python::list keyPointList;
			boost::python::list coorPointList;
			boost::python::list boundBoxCorners;

			coorPointList.append(roi->getXCoordinate());
			coorPointList.append(roi->getYCoordinate());
			objectInformation.append(coorPointList);

			boundBoxCorners.append(roi->getBoundedBox().width);
			boundBoxCorners.append(roi->getBoundedBox().height);
			boundBoxCorners.append(roi->getBoundedBox().x);
			boundBoxCorners.append(roi->getBoundedBox().y);
			objectInformation.append(boundBoxCorners);

			for (const auto & keyPoint : roi->getFeaturePoints()){
				boost::python::list individualKeypointArray;
				individualKeypointArray.append(keyPoint.pt.x);
				individualKeypointArray.append(keyPoint.pt.y);
				individualKeypointArray.append(keyPoint.size);
				individualKeypointArray.append(keyPoint.angle);
				individualKeypointArray.append(keyPoint.response);
				individualKeypointArray.append(keyPoint.octave);
				keyPointList.append(individualKeypointArray);
			}

			objectInformation.append(keyPointList);
			object_data_dictionary[dict_index++] = objectInformation;
		}

	}



	boost::python::list all_text_in_image;

	boost::python::list collectionOfletters;
	for(const auto & word : words ){
		boost::python::list text_information;
		boost::python::list words_python_list_form;
		boost::python::list coordinates_python_list_form;
		words_python_list_form.append(word->getText());
		coordinates_python_list_form.append(word->getXCoordinate());
		coordinates_python_list_form.append(word->getYCoordinate());
		text_information.append(words_python_list_form);
		text_information.append(coordinates_python_list_form);
		all_text_in_image.append(text_information);
	}


	object_data_dictionary[dict_index] = all_text_in_image;
	return object_data_dictionary;
}
