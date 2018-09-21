/*
 * 	      Name: ImageText.h
 *
 *  Created on: 14 Sep 2018
 *      Author: Olu Adebari
 *
 * Description: Object containing identified text in an image and its location
 */

#ifndef IMAGETEXT_H_
#define IMAGETEXT_H_

#include <opencv2/opencv.hpp>
#include <string>

class ImageText {
private:
	const std::string m_text;
	const uint32_t m_x_coordinate, m_y_coordinate;

public:
/**	*****************************************************************************************
	 *  @name      ImageText
	 *
	 *	@brief     constructor
	 *
	 *  @param     std::string: recognised characters within image
	 *  @param     uint32_t: location if text within an in the x axis
	 *  @param     uint32_t: location if text within an in the y axis
	 ****************************************************************************************/
	ImageText(std::string text, uint32_t xCoordinate, uint32_t yCoordinate);
	virtual ~ImageText() = default;

/**	*****************************************************************************************
	 *  @name      getText
	 *
	 *	@brief	   get identified text
	 *
	 *  @return    std::string: get text
	 ****************************************************************************************/
	std::string getText()const;

/**	*****************************************************************************************
	 *  @name      getXCoordinate
	 *
	 *	@brief	   get location of image text within an image along the x axis
	 *
	 *  @return    uint32_t: get x coordinate
	 ****************************************************************************************/
	uint32_t getXCoordinate() const;

/**	*****************************************************************************************
	 *  @name      getYCoordinate
	 *
	 *	@brief	   get location of image text within an image along the y axis
	 *
	 *  @return    uint32_t: get y coordinate
	 ****************************************************************************************/
	uint32_t getYCoordinate() const;
};

#endif /* IMAGETEXT_H_ */
