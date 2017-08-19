/*
 * OCR.cpp
 *
 *  Created on: 18 Aug 2017
 *      Author: sheun
 */

#include "OCR.h"

OCR::OCR() {
	cout<<"getting words from the frame"<<endl;

}

OCR::~OCR() {

}
//get words in frame and their locations points in the image
 pair< vector<string>, vector < pair < int , int  > > > OCR::getWords(Mat img)
{

	Ptr<cv::text::OCRTesseract> ocr = cv::text::OCRTesseract::create(NULL /*datapath*/, "eng" /*lang*/, NULL /*whitelist*/, 2 /*oem*/, 3 /*psmode*/);
	string output;
	vector<Rect>   boxes;
	vector<string> words;
	vector<float>  confidences;
	int x_coordinate;
	int y_coordinate;

	ocr->run(img, output, &boxes, &words, &confidences, 0);
	cout<<words.size()<<endl;

	pair< int , int  > coordinates;
	vector < pair< int , int  > > coordinatesPairs;
	for(uint32_t i = 0; i < words.size(); i++)
	{

		x_coordinate = ((boxes[i].x + boxes[i].width) / 2);
		y_coordinate = ((boxes[i].y + boxes[i].height) / 2);

		coordinates.first = x_coordinate;
		coordinates.second = y_coordinate;
		coordinatesPairs.push_back(coordinates);

	}

	pair< vector<string>, vector < pair<int , int> > > wordsInfo;

	wordsInfo.first = words;
	wordsInfo.second = coordinatesPairs;
	//vector < pair< vector<string>, pair< vector<int>,vector<int> > > > WordsandCoordinates;
	//WordsandCoordinates[0]  = wordsInfo;

	return wordsInfo;

}
//Iterate and display results through all possible oem and psmode values so that you determine the
//most suitable values
void OCR::find_suitable_ocr_values(Mat img)
{
	for (int a = 0; a<4; ++a)
	{
		for (int b=0;b<11;++b)
		{
			cout<<"oem: "<<a<<" psmode: "<<b<<endl;
			Ptr<cv::text::OCRTesseract> ocr = cv::text::OCRTesseract::create(NULL /*datapath*/, "eng" /*lang*/, NULL /*whitelist*/, a /*oem*/, b /*psmode*/);
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

			string output;
			vector<Rect>   boxes;
			vector<string> words;
			vector<float>  confidences;

			ocr->run(img, output, &boxes, &words, &confidences, 0);
			for (uint32_t i = 0; i<words.size(); i++)
			{
				cout<<words[i]<<endl;
			}

		}
	}


}
