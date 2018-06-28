//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Process the captured video game frame, analyse and then send data over to Python caller
//============================================================================

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include <chrono>
#include <ctime>

#include <functional>
#include <future>


#include "convertToBinaryImage.h"
#include "SeperateObjects.h"
#include "featureextraction.h"
#include "SendDataToPython.h"
#include "OCR.h"
#include "recordProcessedImage.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>


using namespace boost::python;

boost::python::dict vision_analysis()
{
	auto recordBoundBox = true;
	auto recordCurrentFrame = false;
	auto recordDarkContrastBinaryImage = true;
	auto recordLightContrastBinaryImage = true ;
	auto recordDarkContrastIdentifiedObjects = true;
	auto recordLightContrastIdentifiedObjects = true ;
	auto recordDarkContrastIdentifiedObjectsFeatures = true;
	auto recordLightContrastIdentifiedObjectsFeatures = true ;

	static uint32_t starting_frame_number = 1;
	uint32_t Number_of_frames_to_record = 1000;

	//get  time at execution
	using time_variable = std::chrono::high_resolution_clock::time_point;

	time_variable start = std::chrono::high_resolution_clock::now();

	//hold coordinates to be later inserted for dark contrast objects
	std::vector<int>dark_x_coordinate;
	std::vector<int>dark_y_coordinate;
	//hold coordinates to be later inserted for light contrast objects
	std::vector<int>light_x_coordinate;
	std::vector<int>light_y_coordinate;


	//read current video_game frame
	//cv::Mat img = cv::imread("../game_vision/current_game_frame/current_game_frame.jpg");
	cv::Mat img = cv::imread("/home/sheun/Downloads/Portal-bilde-640x480.jpg");
	//get words in frame
	OCR capture_words_in_image;

	auto chracterInfo = std::async(std::launch::async,std::bind(&OCR::GetWordsAndLocations, capture_words_in_image,std::ref(img)));

	//convert to grayscale
	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_RGB2GRAY);

	//smooth image
	blur(gray, gray, cv::Size(3,3));

	//this is he image on which the bounded boxes will be drawn on
	cv::Mat original_image_clone = img.clone();

	//convert to binary
	convertToBinaryImage mConvertToBinaryImage;
	cv::Mat binary_image_dark_contrast  = mConvertToBinaryImage.Binary(gray,img);
	cv::Mat binary_image_light_contrast = mConvertToBinaryImage.BinaryInverse(gray,img);

	//get objects in each world view (light and dark contrast images) and put each of them into a vector
	enum contrastOriginOfObjects {darkComtrastImage, lightContrastImage};
	SeperateObjects frame_objects (gray,original_image_clone);
	std::vector<cv::Rect> bound_rect_for_dark_contrast_frame;
	std::vector<cv::Rect> bound_rect_for_light_contrast_frame;
	auto dark_contrast_frame_objects  = std::async(std::launch::async,std::bind(&SeperateObjects::BoundBox, &frame_objects,binary_image_dark_contrast, 	darkComtrastImage,
										std::ref(dark_x_coordinate), 	std::ref(dark_y_coordinate), 	std::ref(bound_rect_for_dark_contrast_frame),	recordDarkContrastIdentifiedObjects));

	auto light_contrast_frame_objects = std::async(std::launch::async,std::bind(&SeperateObjects::BoundBox, &frame_objects,binary_image_light_contrast, lightContrastImage,
										std::ref(light_x_coordinate), 	std::ref(light_y_coordinate), 	std::ref(bound_rect_for_light_contrast_frame),	recordLightContrastIdentifiedObjects));


	dark_contrast_frame_objects.wait();
	light_contrast_frame_objects.wait();
	//Append/combine boundbox vectors so that all objects can be put into the python dictionary
	bound_rect_for_dark_contrast_frame.insert(bound_rect_for_dark_contrast_frame.end(), bound_rect_for_light_contrast_frame.begin(), bound_rect_for_light_contrast_frame.end());


	//get feature points of each object

	using surf_OCL = cv::xfeatures2d::SURF;

	feature_extraction <surf_OCL> features_of_objects;
	//std::vector< std::vector< cv::KeyPoint > > features_of_dark_world_objects  = features_of_objects.FeaturePoints_OCL(dark_contrast_frame_objects.get()  ,0, false);
	auto features_of_dark_world_objects = std::async(std::launch::async,std::bind(&feature_extraction <surf_OCL>::FeaturePoints_OCL,
											&features_of_objects,dark_contrast_frame_objects.get()  ,0, recordDarkContrastIdentifiedObjectsFeatures));

	//std::vector< std::vector< cv::KeyPoint > > features_of_light_world_objects = features_of_objects.FeaturePoints_OCL(light_contrast_frame_objects.get() ,1, false);
	auto features_of_light_world_objects = std::async(std::launch::async,std::bind(&feature_extraction <surf_OCL>::FeaturePoints_OCL,
											&features_of_objects,light_contrast_frame_objects.get()  ,1, recordLightContrastIdentifiedObjectsFeatures));

	auto Object_features_for_dark_contrast = features_of_dark_world_objects.get();
	auto Object_features_for_light_contrast = features_of_light_world_objects.get();
	//Append/combine feature vectors so that all objects can be put into the python dictionary
	Object_features_for_dark_contrast.insert(Object_features_for_dark_contrast.end(), Object_features_for_light_contrast.begin(), Object_features_for_light_contrast.end());

	dark_x_coordinate.insert(dark_x_coordinate.end(), light_x_coordinate.begin(), light_x_coordinate.end());
	dark_y_coordinate.insert(dark_y_coordinate.end(), light_y_coordinate.begin(), light_y_coordinate.end());



	//Optional code: record frames with bounded boxes drawn on into their own directories.
	recordProcessedImage saveProcessedImages (starting_frame_number++, Number_of_frames_to_record);
	if (starting_frame_number >= Number_of_frames_to_record){
		starting_frame_number = 1;
	}

	if(recordBoundBox){
		auto recordBoundBoxAsync =  std::async(std::launch::async,std::bind(&recordProcessedImage::boundbox, saveProcessedImages,std::ref(original_image_clone)));
	}

	if (recordCurrentFrame){
		auto recordCurrentFrameAsync = std::async(std::launch::async,std::bind(&recordProcessedImage::capturedframe, saveProcessedImages,std::ref(img)));

	}
	if (recordDarkContrastBinaryImage){
		auto recordDarkContrastBinaryImageAsync = std::async(std::launch::async,std::bind(&recordProcessedImage::dark_world_Binary, saveProcessedImages,std::ref(binary_image_dark_contrast)));
	}

	if(recordLightContrastBinaryImage){
		auto recordLightContrastBinaryImageAsync = std::async(std::launch::async,std::bind(&recordProcessedImage::light_world_Binary, saveProcessedImages,std::ref(binary_image_light_contrast)));
	}


	//get time at end of image processing and print it
	time_variable end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start ).count();
	std::cout<< "this program took about " << duration<< " milliseconds to process the image" << std::endl;
	//send data of objects in image to python
	chracterInfo.wait();
	SendDataToPython python_features_of_objects;
	boost::python::dict send_to_python_Object_info= python_features_of_objects.SendObjectInformationToDict(Object_features_for_dark_contrast, dark_x_coordinate, dark_y_coordinate, bound_rect_for_dark_contrast_frame, chracterInfo.get());

	return send_to_python_Object_info;

}



int main()
{

	Py_Initialize();
	vision_analysis();

	return 0;

}

BOOST_PYTHON_MODULE(opencv)
{

	//definition that the python program will call  and retrieve information from the c++ code.
	 def("vision", vision_analysis);

}
