/*
 *       Name: RegionOfInterest.h
 *
 *  Created on: 13 Sep 2018
 *      Author: Olu Adebari
 *
 * Desrciption: Object containing a region of interest within an image and its location
 */

#ifndef REGIONOFINTEREST_H_
#define REGIONOFINTEREST_H_

#include <vector>
#include <opencv2/opencv.hpp>

class RegionOfInterest {
private:
	const uint32_t m_binary_image_ID;
	const uint32_t m_region_of_interests_ID;
    cv::Mat m_region_of_interest;
	const uint32_t m_x_coordinate, m_y_coordinate;
	std::vector< cv::KeyPoint > m_feature_points;
	const cv::Rect m_bounded_box;

public:
	RegionOfInterest(uint32_t binary_image_ID, uint32_t region_of_interests_ID, cv::Mat region_of_interest, int x_coordinate, int y_coordinate, cv::Rect boundedBox);
	virtual ~RegionOfInterest() = default;

/**	*****************************************************************************************
	 *  @name       getBinaryImageID
	 *
	 *	@brief		get the Binary Image ID that the region of interest originated from.
	 *
	 *  @return     uint32_t: BinaryImage ID
	 ****************************************************************************************/
	uint32_t getBinaryImageID() const;

/**	*****************************************************************************************
	 *  @name       getBoundedBox
	 *
	 *	@brief		get bounded box for region of image
	 *
	 *  @return     cv::Rect: bounded box for region of image
	 ****************************************************************************************/
	cv::Rect getBoundedBox() const;


/**	*****************************************************************************************
	 *  @name       getRegionOfInterestID
	 *
	 *	@brief		get region of interest ID.
	 *
	 *  @return     uint32_t: region of interest ID.
	 ****************************************************************************************/
	uint32_t getRegionOfInterestID() const;

/**	*****************************************************************************************
	 *  @name       setFeaturePoints
	 *
	 *	@brief		set feature points for image for region of interest image.
	 *
	 *  @param 		std::vector< cv::KeyPoint > : feature points
	 ****************************************************************************************/
	void setFeaturePoints (std::vector< cv::KeyPoint > feature_points);

/**	*****************************************************************************************
	 *  @name       getFeaturePoints
	 *
	 *	@brief		get feature points of image for region of interest image.
	 *
	 *  @return     std::vector< cv::KeyPoint >: get images feature points
	 ****************************************************************************************/
	std::vector< cv::KeyPoint > getFeaturePoints () const;

/**	*****************************************************************************************
	 *  @name       getImage
	 *
	 *  @brief		get region of interest image
	 *
	 *  @return     cv::Mat: get region of interest image
	 ****************************************************************************************/
	cv::Mat getImage () const;

/**	*****************************************************************************************
	 *  @name       getXCoordinate
	 *
	 *	@brief		get location of region of interest image text within an image along the X axis
	 *
	 *  @return     uint32_t: get X coordinate of region of interest.
	 ****************************************************************************************/
	uint32_t getXCoordinate () const;

/**	*****************************************************************************************
	 *  @name       getYCoordinate
	 *
	 *	@brief		get location of region of interest image text within an image along the Y axis
	 *
	 *  @return     uint32_t: get Y coordinate of region of interest.
	 ****************************************************************************************/
	uint32_t getYCoordinate () const;


};

#endif /* REGIONOFINTEREST_H_ */
