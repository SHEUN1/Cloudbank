//============================================================================
// Name        : main.cpp
// Author      : Olu Adebari
// Description : Process the captured video game frame, analyse and then send data over to Python caller program
//============================================================================

#include <iostream>
#include <vector>
#include <chrono>
#include <future>
#include <memory>
#include <string>
#include <opencv2/opencv.hpp>

#include "SeperateObjects.h"
#include "SendDataToPython.h"
#include "OCR.h"
#include "RegionOfInterest.h"
#include "BinaryImage.h"
#include "FeatureExtraction.h"
#include "RecordProcessedImage.h"
#include "ConvertToBinaryImage.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>



boost::python::dict processImageFrame()
{

	auto save_current_frame_with_bounded_boxes = true;
	auto save_current_frame = true;
	auto save_binary_image_of_current_frame = true;
	auto save_regions_of_interest_from_current_frame_binary_image = true;
	auto save_regions_of_interest_from_current_frame_binary_image_features_points = true;

	static uint32_t starting_frame_number = 1;
	uint32_t Number_of_frames_to_record = 1000;

	auto image_processing_start_time = std::chrono::high_resolution_clock::now();

	//read current video_game frame
	cv::Mat img = cv::imread("../game_vision/current_game_frame/current_game_frame.jpg");

	//get words in frame
	OCR capture_words_in_image;
	auto words_and_coordinates = std::async(std::launch::async,std::bind(&OCR::GetWordsAndLocations, capture_words_in_image,std::ref(img)));

	//convert to grayscale
	cv::Mat gray = cv::Mat::zeros(img.size(), img.type());
	cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);

	//smooth image
	blur(gray, gray, cv::Size(3,3));

	cv::Mat image_with_bounded_boxes_drawn_on = img.clone();

	//create binary images
	std::vector< std::shared_ptr<BinaryImage> > binary_images;
	binary_images.emplace_back(std::make_shared<BinaryImage> (1, ConvertToBinaryImage().convertToBinary(gray,img)));
	binary_images.emplace_back(std::make_shared<BinaryImage> (2, ConvertToBinaryImage().convertToBinaryInverse(gray,img)));

	//extract regions of interest within an image
	SeperateObjects seperate_regions_of_interest (gray,image_with_bounded_boxes_drawn_on);
	auto get_binary_image_1_ROI_objects  = std::async(std::launch::async,std::bind(&SeperateObjects::BoundBox, &seperate_regions_of_interest,binary_images[0] ,save_regions_of_interest_from_current_frame_binary_image));
	auto get_binary_image_2_ROI_objects = std::async(std::launch::async,std::bind(&SeperateObjects::BoundBox, &seperate_regions_of_interest,binary_images[1] ,save_regions_of_interest_from_current_frame_binary_image));

	get_binary_image_1_ROI_objects.wait();
	get_binary_image_2_ROI_objects.wait();


	//extract feature points for each region of interest
	using surf_OCL = cv::xfeatures2d::SURF;

	FeatureExtraction <surf_OCL> features_of_objects;

	auto get_feature_points_for_binary_1_ROI_objects = std::async(std::launch::async,std::bind(&FeatureExtraction <surf_OCL>::extractFeaturePoints,
											&features_of_objects,binary_images[0],save_regions_of_interest_from_current_frame_binary_image_features_points));

	auto get_feature_points_for_binary_2_ROI_objects = std::async(std::launch::async,std::bind(&FeatureExtraction <surf_OCL>::extractFeaturePoints,
											&features_of_objects,binary_images[1], save_regions_of_interest_from_current_frame_binary_image_features_points));

	get_feature_points_for_binary_1_ROI_objects.wait();
	get_feature_points_for_binary_2_ROI_objects.wait();



	//Optional code: record frames with bounded boxes drawn on into their own directories.
	std::string current_frame_file_name = "Image"+std::to_string(starting_frame_number)+".jpg";
	RecordProcessedImage saveProcessedImages;
	if (starting_frame_number >= Number_of_frames_to_record){
		starting_frame_number = 1;
	}

	if(save_current_frame_with_bounded_boxes){
		auto recordBoundBoxAsync =  std::async(std::launch::async,std::bind(&RecordProcessedImage::saveImage, saveProcessedImages,std::ref(image_with_bounded_boxes_drawn_on),"../game_vision/cloudbank_images/Frame/bounded_boxes/",current_frame_file_name ));
	}

	if (save_current_frame){
		auto recordCurrentFrameAsync = std::async(std::launch::async,std::bind(&RecordProcessedImage::saveImage, saveProcessedImages,std::ref(img),"../game_vision/cloudbank_images/Frame/Unprocessed/",current_frame_file_name));

	}
	if (save_binary_image_of_current_frame){
		for (auto const & binary_image : binary_images){
			auto recordCurrentFrameAsync = std::async(std::launch::async,std::bind(&RecordProcessedImage::saveImage, saveProcessedImages,binary_image->getBinaryImage(),"../game_vision/cloudbank_images/Frame/Binary/binaryImage_ID_"+std::to_string(binary_image->getID()),current_frame_file_name));

		}

	}
	++starting_frame_number;
	auto image_processing_end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(image_processing_end_time - image_processing_start_time ).count();
	std::cout<< "this program took about " << duration<< " milliseconds to process the image" << std::endl;

	words_and_coordinates.wait();

	//send extracted image frame in python form into calling python process
	SendDataToPython python_features_of_objects;
	boost::python::dict send_to_python_Object_info= python_features_of_objects.SendObjectInformationToDict(binary_images, words_and_coordinates.get());

	return send_to_python_Object_info;

}



int main()
{

	Py_Initialize();
	processImageFrame();

	return 0;

}

BOOST_PYTHON_MODULE(opencv)
{
	 def("ProcessGameFrame", processImageFrame);
}
