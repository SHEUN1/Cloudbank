/*
 *        Name: ImageText.cpp
 *
 *  Created on: 14 Sep 2018
 *      Author: Olu Adebari
 *
 * Description: Object containing identified text in an image and its location
 */

#include "ImageText.h"

ImageText::ImageText(std::string text, uint32_t xCoordinate, uint32_t yCoordinate) : m_text(text), m_x_coordinate(xCoordinate), m_y_coordinate(yCoordinate) {

}

std::string ImageText::getText()const
{
	return m_text;
}


uint32_t ImageText::getXCoordinate() const
{
	return m_x_coordinate;
}


uint32_t ImageText::getYCoordinate() const
{
	return m_y_coordinate;
}

