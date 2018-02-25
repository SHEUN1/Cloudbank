/*

* yingyang.h
 *
 *  Created on: 13 Jun 2017
 *      Author: sheun
 *
 *      return a binary image
 */
#ifndef CONVERTTOBINARYIMAGE_H_
#define CONVERTTOBINARYIMAGE_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

class convertToBinaryImage {

private:

	/**
		 *****************************************************************************************
		 *  @brief      clean up a binary image (CPU Version)
		 *
		 *  @usage      remove small blobs from a binary image
		 *
		 *  @param      Binary image you want to clean
		 *
		 *  @return     Binary image
		 ****************************************************************************************/

	cv::Mat cleanupBinary (cv::Mat Binary);
	/**
		 *****************************************************************************************
		 *  @brief      clean up a binary image (GPU Version)
		 *
		 *  @usage      remove small blobs from a binary image
		 *
		 *
		 *  @param      Binary image you want to clean
		 *
		 *  @return     Binary image
		 ****************************************************************************************/
	cv::cuda::GpuMat cleanupBinary (cv::cuda::GpuMat Binary);
	/**
		 *****************************************************************************************
		 *  @brief      Watershed segmentation
		 *
		 *  @usage      use watershed segmentation method to create binary image
		 *
		 *  @param      Binary Image
		 *  @param      original (non-grayscale image)
		 *
		 *  @return     Mat Binary image
		 ****************************************************************************************/
	cv::Mat  Watershed(cv::Mat Binary, cv::Mat origanal_image);

public:
	convertToBinaryImage();
	virtual ~convertToBinaryImage() = default;

	 /**
	 	 *****************************************************************************************
	 	 *  @brief      binary converter
	 	 *
	 	 *  @usage      convert grayscale image into i binary image using the watershed segmentation method
	 	 *
	 	 *  @param      grayscale image
	 	 *  @param      origanal (non-grayscale image)
	 	 *  @param		0 = use OpenCL, 1 = use CUDA
	 	 *
	 	 *  @return     Mat Binary image
	 	 ****************************************************************************************/

	cv::Mat Binary (cv::Mat const &img, cv::Mat origanal, int run_on_cuda_GPU);
	/**
		 *****************************************************************************************
		 *  @brief      binary image converter on inverse of a grayscale image
		 *
		 *  @usage      Heighten contrast on and convert grayscale image into a binary image using the watershed segmentation method
		 *
		 *
		 *  @param      grayscale image
		 *  @param      original (non-grayscale image)
		 *  @param		0 = use OpenCL, 1 = use CUDA
		 *
		 *  @return     Mat Binary image
		 ****************************************************************************************/
	cv::Mat BinaryInverse (cv::Mat const &img, cv::Mat origanal, int run_on_cuda_GPU);


};

#endif
