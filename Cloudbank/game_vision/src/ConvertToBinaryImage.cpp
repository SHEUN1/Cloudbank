/*
 *        Name: ConvertToBinaryImage.cpp
 *
 *  Created on: 13 Jun 2017
 *      Author: Olu Adebari
 *
 *  Description: convert an image into a binary image.
*/
#include "ConvertToBinaryImage.h"

ConvertToBinaryImage::ConvertToBinaryImage() {

	std::cout<<"converting to binary"<<std::endl;
}


 cv::Mat ConvertToBinaryImage:: watershedSegmentation(cv::Mat binary_image, cv::Mat origanal_colour_image)
{
	 // increase/decrese this value to reduce/increase the number of objects segmented respectively
	 auto markerThreshold =  0.043;

	//hold output matrix result of distance transform function
	cv::Mat  distance;

	cv::distanceTransform(binary_image, distance, CV_DIST_L2, 3);

	cv::normalize(distance, distance, 0, 1., cv::NORM_MINMAX);

	// Threshold to obtain the peaks. Markers for the foreground objects
	cv::threshold(distance, distance, markerThreshold, 1., CV_THRESH_BINARY);

	//convolution matrix masking
	cv::Mat kernel = cv::Mat::ones(3, 3, CV_8UC1);
	dilate(distance, distance, kernel);

	cv::Mat  distance_8u;
	distance.convertTo(distance_8u, CV_8U);

	// Find total markers
	std::vector< std::vector<cv::Point> > contours;
	findContours(distance_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	// Create the marker image for the watershed algorithm
	cv::Mat markers = cv::Mat ::zeros(distance.size(), CV_32SC1);

	// Draw the foreground markers
	for (size_t i = 0; i < contours.size(); ++i){
		drawContours(markers, contours, static_cast<int>(i), cv::Scalar::all(static_cast<int>(i)+1), -1);
	}

	// Perform the watershed algorithm
	cv::watershed(origanal_colour_image, markers);

   // the markers image will be -1 at the boundaries of the regions
	cv::Mat region = cv::Mat ::zeros(markers.size(), CV_32SC1);
	cv::compare(markers, -1, region, cv::CMP_EQ);

	return region;
}

cv::Mat  ConvertToBinaryImage::convertToBinary (cv::Mat const &grayscale_original_img,cv::Mat original_img)
{
	 cv::Mat binary_image, segmented_binary_image;

	 cv::threshold(grayscale_original_img, binary_image, 0.5, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	 binary_image = cleanUpBinary(binary_image);

	 segmented_binary_image = watershedSegmentation(binary_image,  original_img);

	 return segmented_binary_image;
}


cv::Mat  ConvertToBinaryImage::convertToBinaryInverse (cv::Mat const &img, cv::Mat origanal)
{
	//contrast control
	auto alpha = 2.2;

	//brightness control
	auto beta = 50;

	cv::Mat  contrasted, binary_image, binaryImage_inv, segmented_binary_image;
	img.convertTo(contrasted, -1, alpha, beta);

	cv::threshold(contrasted, binary_image,0.5,255,cv::THRESH_BINARY| CV_THRESH_OTSU);

	binary_image = cleanUpBinary(binary_image);

	//inverse the binary image
	bitwise_not(binary_image, binaryImage_inv);

	segmented_binary_image = watershedSegmentation(binaryImage_inv,  origanal);

	return segmented_binary_image;
 }



cv::Mat  ConvertToBinaryImage::cleanUpBinary(cv::Mat binary_image)
{
	auto  se1 = getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10));
	auto  se2 = getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));

	// Perform closing then opening
	cv::Mat  mask, cleaned_Binary_Image;
	cv::morphologyEx(binary_image, mask, cv::MORPH_CLOSE, se1);
	cv::morphologyEx(mask, mask, cv::MORPH_OPEN, se2);

	// Filter the output
	cleaned_Binary_Image = binary_image.clone();

	cleaned_Binary_Image.setTo(cv::Scalar(0), mask==0);

	return cleaned_Binary_Image;
}

