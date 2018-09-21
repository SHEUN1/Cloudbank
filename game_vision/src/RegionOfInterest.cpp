/*
 *       Name: RegionOfInterest.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Olu Adebari
 *
 * Desrciption: Object containing a region of interest within an image and its location
 */


#include "RegionOfInterest.h"

RegionOfInterest::RegionOfInterest(uint32_t binary_image_ID, uint32_t region_of_interests_ID, cv::Mat region_of_interest, int x_coordinate, int y_coordinate, cv::Rect boundedBox) :  m_binary_image_ID(binary_image_ID),  m_region_of_interests_ID(region_of_interests_ID) , m_region_of_interest(region_of_interest), m_x_coordinate(x_coordinate), m_y_coordinate(y_coordinate), m_bounded_box(boundedBox)
{

}

uint32_t RegionOfInterest::getBinaryImageID() const
{
	return m_binary_image_ID;
}

cv::Rect RegionOfInterest::getBoundedBox() const
{
	return m_bounded_box;
}

uint32_t RegionOfInterest::getRegionOfInterestID() const
{
	return m_region_of_interests_ID;
}

void RegionOfInterest::setFeaturePoints (std::vector< cv::KeyPoint > feature_points)
{
	m_feature_points = feature_points;
}

std::vector< cv::KeyPoint > RegionOfInterest::getFeaturePoints () const
{
	return m_feature_points;
}

cv::Mat RegionOfInterest::getImage () const
{
	return m_region_of_interest;
}

uint32_t RegionOfInterest::getXCoordinate () const
{
	return m_x_coordinate;
}

uint32_t RegionOfInterest::getYCoordinate () const
{
	return m_y_coordinate;
}
