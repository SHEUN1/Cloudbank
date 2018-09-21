/*
 * 	Name:BinaryImage.h
 *
 *  Created on: 13 Sep 2018
 *      Author: Olu Adebari
 *
 *  Description: Binary image class containing binary image and regions of interest extracted from a binary image
 */

#ifndef BINARYIMAGE_H_
#define BINARYIMAGE_H_

#include "RegionOfInterest.h"
#include <vector>
#include <memory>
#include <unordered_map>

class BinaryImage {
private:

	const uint32_t m_ID;
	const cv::Mat m_binary_image;
	std::unordered_map<uint32_t, std::shared_ptr<RegionOfInterest> > m_regions_of_interest;
	std::vector < std::shared_ptr<RegionOfInterest> >  m_all_regions_of_interest;

public:

/**	*****************************************************************************************
	 *  @name      BinaryImage
	 *
	 *  @brief     Constructor
	 *
	 *  @param     uint32_t: ID for binaryImage
	 *  @param     cv::Mat: binary image
	 ****************************************************************************************/
	BinaryImage(uint32_t ID, cv::Mat binaryImage);
	virtual ~BinaryImage() = default;

/**	*****************************************************************************************
	 *  @name      getID
	 *
	 *	@brief     get the ID for the region of interest.
	 *
	 *  @return    uint32_t: ID for the region of interest.
	 ****************************************************************************************/
	 uint32_t getID () const;

/**	*****************************************************************************************
	 *  @name      getBinaryImage
	 *
	 *  @brief     get Binary image.
	 *
	 *  @return    cv::Mat: get Binary image.
	 ****************************************************************************************/
	 cv::Mat getBinaryImage () const;

/**	*****************************************************************************************
	 *  @name      addRegionOfInterest
	 *
	 *  @brief     add a region of interest
	 *
	 *  @param     std::shared_ptr<RegionOfInterest>: region of interest
	 ****************************************************************************************/
	void addRegionOfInterest (std::shared_ptr<RegionOfInterest>  ROI);

/**	*****************************************************************************************
	 *  @name      addRegionOfInterest
	 *
	 *  @brief     add a region of interest
	 *
	 *  @param 	   uint32_t: region of interest unique ID
	 *  @param 	   cv::Mat: region of interest
	 *  @param     int: coordinate of the region of axis within the image along the x axis
	 *  @param     int: coordinate of the region of axis within the image along the y axis
	 *  @param     cv::Rec: bounded Box of the region of interest
	 ****************************************************************************************/
	void addRegionOfInterest ( uint32_t region_of_interests_ID, cv::Mat region_of_interest, int x_coordinate, int y_coordinate, cv::Rect boundedBox);

/**	*****************************************************************************************
	 *  @name      getRegionOfInterestByID
	 *
	 *  @brief	   get a region of interest based on its ID
	 *
	 *	@param	   uint32_t: ID of requested region of interest image
	 *
	 *  @return    std::shared_ptr<RegionOfInterest>: a region of interest
	 ****************************************************************************************/
	std::shared_ptr<RegionOfInterest> getRegionOfInterestByID (uint32_t ID) const;

/**	*****************************************************************************************
	 *  @name      getAllRegionsOfInterest
	 *
	 *  @brief     get all regions of interest images currently held
	 *
	 *  @return    std::vector< std::shared_ptr<RegionOfInterest> > : regions of interest
	 ****************************************************************************************/
	std::vector< std::shared_ptr<RegionOfInterest> > getAllRegionsOfInterest() const;
};

#endif /* BINARYIMAGE_H_ */
