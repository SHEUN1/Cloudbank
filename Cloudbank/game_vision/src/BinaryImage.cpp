/*
 * 	Name:BinaryImage.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Olu Adebari
 *
 *  Description: Binary image class containing binary image and regions of interest extracted from a binary image
 */

#include "BinaryImage.h"

BinaryImage::BinaryImage(uint32_t ID, cv::Mat binaryImage):m_ID(ID), m_binary_image(binaryImage) {}


uint32_t BinaryImage::getID () const
{
	return m_ID;
}

cv::Mat BinaryImage::getBinaryImage () const
{
	return m_binary_image;
}


void BinaryImage::addRegionOfInterest (std::shared_ptr<RegionOfInterest> ROI)
{
	m_regions_of_interest.insert({ROI->getBinaryImageID(),ROI});
	m_all_regions_of_interest.push_back(ROI);
}

void BinaryImage::addRegionOfInterest ( uint32_t region_of_interests_ID, cv::Mat region_of_interest, int x_coordinate, int y_coordinate, cv::Rect boundedBox)
{
	m_all_regions_of_interest.emplace_back(std::make_shared<RegionOfInterest>(m_ID, region_of_interests_ID, region_of_interest,x_coordinate, y_coordinate,boundedBox));
	m_regions_of_interest.insert({m_all_regions_of_interest.back()->getBinaryImageID(),m_all_regions_of_interest.back()});
}
std::shared_ptr<RegionOfInterest> BinaryImage::getRegionOfInterestByID (uint32_t ID) const
{
	auto ROI = m_regions_of_interest.find(ID);
	if (ROI!=m_regions_of_interest.end()){
		return ROI->second;
	}
	return nullptr;
}


std::vector< std::shared_ptr<RegionOfInterest> > BinaryImage::getAllRegionsOfInterest() const
{

	return m_all_regions_of_interest;
}

