/*
 * yingyang.cpp
 *
 *  Created on: 13 Jun 2017
 *      Author: sheun
 *
 *      return a binary image
 */

#include "convertToBinaryImage.h"

convertToBinaryImage::convertToBinaryImage() {

std::cout<<"converting to binary"<<std::endl;
}

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
 cv::Mat convertToBinaryImage::Watershed(cv::Mat  binary_image, cv::Mat origanal_image)
{
	    // Use the distance transform algorithm

	 	//hold output matrix result of distance transform function
	    cv::Mat  distance;

	    //CV_CV_DIST_L2_L2 = Euclidian distance and using a 3x3 mask change last parameter "3" to 5  for a more accurate distance estimation
	    //default output image type is CV_32F
	    cv::distanceTransform(binary_image, distance, CV_DIST_L2, 3);

	    // Normalize the distance image within range {0.0-1.0} to threshold it
	    cv::normalize(distance, distance, 0, 1., cv::NORM_MINMAX);

	    // Threshold to obtain the peaks
	    // This will be the markers for the foreground objects
	    cv::threshold(distance, distance, 0.043, 1., CV_THRESH_BINARY);

	    // Dilate a bit the distance image
	    //use  convolution matrix masking
	    cv::Mat kernel = cv::Mat::ones(3, 3, CV_8UC1);
	    dilate(distance, distance, kernel);


	    // Create the CV_8U (unsigned 8bit/pixel) version of the distance image so to get pixel values between 0-255
	    // It is needed for findContours()
	    cv::Mat  distance_8u;
	    distance.convertTo(distance_8u, CV_8U);

	    // Find total markers
	    std::vector< std::vector<cv::Point> > contours;
	    findContours(distance_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	    // Create the marker image for the watershed algorithm
	    cv::Mat  markers = cv::Mat ::zeros(distance.size(), CV_32SC1);

	    // Draw the foreground markers
	    for (size_t i = 0; i < contours.size(); i++){
	        drawContours(markers, contours, static_cast<int>(i), cv::Scalar::all(static_cast<int>(i)+1), -1);
	    }

	    // Perform the watershed algorithm
	    cv::watershed(origanal_image, markers);

	   // the markers image will be -1 at the boundaries of the regions
	    cv::Mat region = cv::Mat ::zeros(markers.size(), CV_32SC1); //markers==-1;
	    cv::compare(markers, -1, region, cv::CMP_EQ);

	    return region;
}
 /**
 	 *****************************************************************************************
 	 *  @brief      binary image converter
 	 *
 	 *  @usage      convert grayscale image into a binary image using the watershed segmentation method
 	 *
 	 *  @param      grayscale image
 	 *  @param      original (non-grayscale image)
 	 *  @param		0 = use OpenCL, 1 = use CUDA
 	 *
 	 *  @return     Mat Binary image
 	 ****************************************************************************************/
cv::Mat  convertToBinaryImage::Binary (cv::Mat const &grayscale_original_img,cv::Mat original_img, int run_on_cuda_GPU)
{
	 cv::Mat  binaryImage;

	 //create binary image
	 threshold(grayscale_original_img, binaryImage, 0.5, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	 //clean up the binary image i.e. remove small blobs

	 cv::cuda::GpuMat binaryImageGPU;

	 if (run_on_cuda_GPU == 0){

		 binaryImage = cleanupBinary(binaryImage);

	 }

	 else  if (run_on_cuda_GPU == 1) {

		 binaryImageGPU.upload(binaryImage);

		 binaryImageGPU = cleanupBinary(binaryImageGPU);

		 binaryImageGPU.download(binaryImage);

	 }

	 cv::Mat Binary_post_watershed = Watershed(binaryImage,  original_img);


	 return Binary_post_watershed;
}

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
cv::Mat  convertToBinaryImage::BinaryInverse (cv::Mat const &img, cv::Mat origanal, int run_on_cuda_GPU)
{
	//contrast control
	auto alpha = 2.2;

	//brightness control
	auto beta = 50;

	cv::Mat  contrasted, binaryImage, binaryImage_inv;
	img.convertTo(contrasted, -1, alpha, beta);

	cv::threshold(contrasted, binaryImage,0.5,255,cv::THRESH_BINARY| CV_THRESH_OTSU);

	if (run_on_cuda_GPU == 0){

		binaryImage = cleanupBinary(binaryImage);
	}

	else  if (run_on_cuda_GPU == 1) {
		cv::cuda::GpuMat binaryImageGPU;
		binaryImageGPU.upload(binaryImage);

		binaryImageGPU = cleanupBinary(binaryImageGPU);
		binaryImageGPU.download(binaryImage);
	}

	//inverse the binary image
	bitwise_not(binaryImage, binaryImage_inv);

	cv::Mat  Binary_post_watershed = Watershed(binaryImage_inv,  origanal);

	return Binary_post_watershed;
}


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
cv::Mat  convertToBinaryImage::cleanupBinary(cv::Mat binary_image)
{
		cv::Mat  se1 = getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10));
	    cv::Mat  se2 = getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));

	    // Perform closing then opening
	    cv::Mat  mask;
	    cv::morphologyEx(binary_image, mask, cv::MORPH_CLOSE, se1);
	    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, se2);

	    // Filter the output
	    cv::Mat  CleanedBinaryImage = binary_image.clone();

	    CleanedBinaryImage.setTo(cv::Scalar(0), mask==0);
	    //cv::compare(mask, 0, CleanedBinaryImage, cv::CMP_EQ);
	    return CleanedBinaryImage;
}
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
cv::cuda::GpuMat convertToBinaryImage::cleanupBinary(cv::cuda::GpuMat Binary)
{

		cv::Mat  se1 = getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)),
				 se2 = getStructuringElement(cv::MORPH_RECT, cv::Size(4, 4));

	    // Perform closing then opening
	    cv::cuda::GpuMat mask;
	    cv::Ptr<cv::cuda::Filter> openFilter1 = cv::cuda::createMorphologyFilter(cv::MORPH_CLOSE, Binary.type(), se1);
	    openFilter1->apply(Binary, mask);

	    cv::Ptr<cv::cuda::Filter> openFilter2 = cv::cuda::createMorphologyFilter(cv::MORPH_OPEN, mask.type(), se2);
	    openFilter2->apply(mask, mask);

	    //download binary image onto the cpu
	    cv::Mat  Binary_to_CPU, mask_to_CPU;
	    Binary.download(Binary_to_CPU);
	    mask.download(mask_to_CPU);

	    // Filter the output
	    cv::Mat  CleanedBinaryImage = Binary_to_CPU.clone();
	    CleanedBinaryImage.setTo(cv::Scalar(0), mask_to_CPU == 0);
	    cv::cuda::GpuMat CleanedBinaryImage_to_GPU;
	    CleanedBinaryImage_to_GPU.upload(CleanedBinaryImage);
	    return CleanedBinaryImage_to_GPU;
}
