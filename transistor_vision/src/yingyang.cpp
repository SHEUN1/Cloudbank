/*
 * yingyang.cpp
 *
 *  Created on: 13 Jun 2017
 *      Author: sheun
 */

#include "yingyang.h"

ying_yang::ying_yang() {


}

ying_yang::~ying_yang() {

}
Mat1b ying_yang::binary (Mat1b img)
{

	 Mat1b binaryImage;
	 //create binary image
	 threshold(img, binaryImage, 0.5, 255, THRESH_BINARY | CV_THRESH_OTSU);
	 //clean up the binary image i.e. remove small blobs
	 return cleanupBinary(binaryImage);
}
Mat1b ying_yang::binary_Inverse (Mat1b img)
{
	double alpha = 2.2;//contrast control
	int beta = 50;//brightness control
	Mat1b contrasted, binaryImage, binaryImage_inv;
	img.convertTo(contrasted, -1, alpha, beta);

	threshold(contrasted, binaryImage,0.5,255,THRESH_BINARY| CV_THRESH_OTSU);
	binaryImage = cleanupBinary(binaryImage);
	//inverse the binary image
	binaryImage_inv = cv::Scalar::all(255)-binaryImage ;
	return binaryImage_inv;
}




//remove  small blobs in binary images
Mat1b ying_yang::cleanupBinary(Mat1b Binary)
{
		Mat se1 = getStructuringElement(MORPH_RECT, Size(10, 10));
	    Mat se2 = getStructuringElement(MORPH_RECT, Size(4, 4));

	    // Perform closing then opening
	    Mat mask;
	    morphologyEx(Binary, mask, MORPH_CLOSE, se1);
	    morphologyEx(mask, mask, MORPH_OPEN, se2);

	    // Filter the output
	    Mat1b out = Binary.clone();
	    out.setTo(Scalar(0), mask == 0);

	    return out;
}
