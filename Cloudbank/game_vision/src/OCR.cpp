/*
 * 		  Name:OCR.cpp
 *
 *  Created on: 18 Aug 2017
 *      Author: Olu Adebari
 *
 * Description:Identify characters in the image
 */

#include "OCR.h"

OCR::OCR() {
	std::cout<<"getting words from the frame"<<std::endl;

}


std::vector< std::shared_ptr<ImageText> > OCR::GetWordsAndLocations(cv::Mat &img)
{

	std::vector< std::shared_ptr<ImageText> > text_in_image;
	cv::Ptr<cv::text::OCRTesseract> ocr = cv::text::OCRTesseract::create(NULL, "eng" , NULL, 2 , 3 );
	std::string output;
	std::vector<cv::Rect>   boxes;
	std::vector<std::string> words;
	std::vector<float>  confidences;
	uint32_t x_coordinate;
	uint32_t y_coordinate;

	ocr->run(img, output, &boxes, &words, &confidences, 0);


	auto i = 0;
	for(auto const &box : boxes)
	{

		x_coordinate = ((box.x + box.width) / 2);
		y_coordinate = ((box.y + box.height) / 2);

		text_in_image.emplace_back(new ImageText(words[i++],x_coordinate,y_coordinate));
	}


	return text_in_image;

}

void OCR::FindSuitableOcrValues(cv::Mat &img)
{
	//tesseract documentation: https://github.com/tesseract-ocr/tesseract/blob/master/doc/tesseract.1.asc
	for (uint32_t oem = 0; oem < 4; ++oem)
	{
		for (uint32_t psmode = 0; psmode < 11; ++psmode)
		{
			std::cout<<"oem: "<< oem <<" psmode: "<< psmode <<std::endl;
			cv::Ptr<cv::text::OCRTesseract> ocr = cv::text::OCRTesseract::create(NULL , "eng", NULL , oem , psmode );


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
