/*
 * OCR.cpp
 *
 *  Created on: 18 Aug 2017
 *      Author: sheun
 *
 *      Identify characters in the image
 */

#include "OCR.h"

OCR::OCR() {
	std::cout<<"getting words from the frame"<<std::endl;

}


/**
 *****************************************************************************************
 *  @brief      optional:Iterate and display results through all possible oem and psmode values so that you determine the
						 most suitable values
 *
 *  @param      Original (non-processed) image frame
 *  @return     pair of characters in images and their associated x and y positions.
 ****************************************************************************************/
 std::pair< std::vector<std::string>, std::vector < std::pair < int , int  > > > OCR::GetWordsAndLocations(cv::Mat img)
{

	cv::Ptr<cv::text::OCRTesseract> ocr = cv::text::OCRTesseract::create(NULL /*datapath*/, "eng" /*lang*/, NULL /*whitelist*/, 2 /*oem*/, 3 /*psmode*/);
	std::string output;
	std::vector<cv::Rect>   boxes;
	std::vector<std::string> words;
	std::vector<float>  confidences;
	int x_coordinate;
	int y_coordinate;

	ocr->run(img, output, &boxes, &words, &confidences, 0);

	// collection of x,y positions of all characters in the image
	std::pair< int , int  > coordinates;

	// individual x,y pairs positions of characters in the image
	std::vector < std::pair< int , int  > > coordinates_pairs;

	for(auto const &box : boxes)
	{
		x_coordinate = ((box.x + box.width) / 2);
		y_coordinate = ((box.y + box.height) / 2);

		coordinates.first = x_coordinate;
		coordinates.second = y_coordinate;
		coordinates_pairs.push_back(coordinates);
	}

	//Characters in the image and their locations within the frame
	std::pair< std::vector<std::string>, std::vector < std::pair<int , int> > > words_and_coordinates;

	words_and_coordinates.first = words;
	words_and_coordinates.second = coordinates_pairs;


	return words_and_coordinates;

}

 /**
  *****************************************************************************************
  *  @brief      optional:Iterate and display results through all possible oem and psmode values so that you determine the
 						 most suitable values by printing the results out.
  *
  *  @param      Original (non-processed) image frame
  *  @return
  ****************************************************************************************/
void OCR::FindSuitableOcrValues(cv::Mat img)
{
	for (uint32_t a = 0; a<4; a++)
	{
		for (uint32_t b=0;b<11;b++)
		{
			std::cout<<"oem: "<<a<<" psmode: "<<b<<std::endl;
			cv::Ptr<cv::text::OCRTesseract> ocr = cv::text::OCRTesseract::create(NULL /*datapath*/, "eng" /*lang*/, NULL /*whitelist*/, a /*oem*/, b /*psmode*/);
			/* oem value choice:
			    0 = Original Tesseract only.
			    1 = Neural nets LSTM only.
				2 = Tesseract + LSTM.
				3 = Default, based on what is available.

				psm value choice:
				0 = Orientation and script detection (OSD) only.
				1 = Automatic page segmentation with OSD.
				2 = Automatic page segmentation, but no OSD, or OCR.
				3 = Fully automatic page segmentation, but no OSD. (Default)
				4 = Assume a single column of text of variable sizes.
				5 = Assume a single uniform block of vertically aligned text.
				6 = Assume a single uniform block of text.
				7 = Treat the image as a single text line.
				8 = Treat the image as a single word.
				9 = Treat the image as a single word in a circle.
				10 = Treat the image as a single character.
		     */

			std::string output;
			std::vector<cv::Rect>   boxes;
			std::vector<std::string> words;
			std::vector<float>  confidences;

			ocr->run(img, output, &boxes, &words, &confidences, 0);

			for (auto const &word : words)
			{
				std::cout<<word<<std::endl;
			}

		}
	}


}
