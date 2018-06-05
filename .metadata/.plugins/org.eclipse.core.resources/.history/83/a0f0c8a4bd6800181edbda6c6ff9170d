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


#include "convertToBinaryImage.h"
#include "SeperateObjects.h"
#include "featureextraction.h"
#include "SendDataToPython.h"
#include "OCR.h"
#include "recordProcessedImage.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>


#define timeNow() std::chrono::high_resolution_clock::now();

using namespace boost::python;

boost::python::dict vision_analysis()
{
		static uint32_t starting_frame_number = 0;
		static uint32_t activateImageCapture = 0;

		//get  time at execution
		using time_variable = std::chrono::high_resolution_clock::time_point;


		time_variable start = timeNow();


		//hold coordinates to be later inserted for dark contrast objects
		std::vector<int>dark_x_coordinate;
		std::vector<int>dark_y_coordinate;
		//hold coordinates to be later inserted for light contrast objects
		std::vector<int>light_x_coordinate;
		std::vector<int>light_y_coordinate;

		int systemRem;
		// turn on script that save get current frame from video game
		if (activateImageCapture == 0)
		{
			systemRem = system("../game_vision/gstream_command_to_capture_image &");
			if (systemRem == -1){
				throw std::runtime_error("failed to start screen capture software");
			}
			++activateImageCapture;

		}

	    //read current video_game frame
	    cv::Mat img = cv::imread("../game_vision/current_game_frame.jpg");


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
		std::vector<cv::Mat> dark_contrast_frame_objects  = frame_objects.BoundBox(binary_image_dark_contrast, darkComtrastImage, dark_x_coordinate, dark_y_coordinate, bound_rect_for_dark_contrast_frame,true);
		std::vector<cv::Mat> light_contrast_frame_objects = frame_objects.BoundBox(binary_image_light_contrast, lightContrastImage, light_x_coordinate, light_y_coordinate, bound_rect_for_light_contrast_frame,true);


		//Append/combine boundbox vectors so that all objects can be put into the python dictionary
		bound_rect_for_dark_contrast_frame.insert(bound_rect_for_dark_contrast_frame.end(), bound_rect_for_light_contrast_frame.begin(), bound_rect_for_light_contrast_frame.end());


		//get feature points of each object

		using surf_OCL = cv::xfeatures2d::SURF;

		feature_extraction <surf_OCL> features_of_objects;
		std::vector< std::vector< cv::KeyPoint > > features_of_dark_world_objects  = features_of_objects.FeaturePoints_OCL(dark_contrast_frame_objects  ,0, true);
	    std::vector< std::vector< cv::KeyPoint > > features_of_light_world_objects = features_of_objects.FeaturePoints_OCL(light_contrast_frame_objects ,1, true);

		//Append/combine feature vectors so that all objects can be put into the python dictionary
		features_of_dark_world_objects.insert(features_of_dark_world_objects.end(), features_of_light_world_objects.begin(), features_of_light_world_objects.end());

		dark_x_coordinate.insert(dark_x_coordinate.end(), light_x_coordinate.begin(), light_x_coordinate.end());
		dark_y_coordinate.insert(dark_y_coordinate.end(), light_y_coordinate.begin(), light_y_coordinate.end());

		//get words in frame
		OCR capture_words_in_image;

		//hold x,y coordinates of words in the frame
		using coordinates = std::pair<int, int > ;

		std::pair< std::vector<std::string>, std::vector < coordinates > > chracterInfo = capture_words_in_image.GetWordsAndLocations(img);

		//Optional code: record frames with bounded boxes drawn on into their own directories.
		recordProcessedImage saveProcessedImages (starting_frame_number++,50);
		saveProcessedImages.boundbox(original_image_clone);
		//saveProcessedImages.capturedframe(img);
		//saveProcessedImages.dark_world_Binary(binary_image_dark_contrast);
		//saveProcessedImages.light_world_Binary(binary_image_light_contrast);


		//get time at end of image processing and print it
		time_variable end = timeNow();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start ).count();
		std::cout<< "this program took about " << duration<< " milliseconds to process the image" << std::endl;
		//send data of objects in image to python
		SendDataToPython python_features_of_objects;
		boost::python::dict send_to_python_Object_info= python_features_of_objects.SendObjectInformationToDict(features_of_dark_world_objects, dark_x_coordinate, dark_y_coordinate, bound_rect_for_dark_contrast_frame, chracterInfo);

		return send_to_python_Object_info;

}



int main()
{

	vision_analysis();

	return 0;

}

BOOST_PYTHON_MODULE(opencv)
{

	//definition that the python program will call  and retrieve information from the c++ code.
	 def("vision", vision_analysis);

}
