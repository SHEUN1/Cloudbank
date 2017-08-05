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
	 threshold(img, binaryImage, 100, 255, THRESH_BINARY | CV_THRESH_OTSU);
	 return cleanupBinary(binaryImage);
}
Mat1b ying_yang::binary_Inverse (Mat1b img)
{
	Mat1b binaryImage, binaryImage_inv;
	Mat1b contrasted;
	binaryImage = imadjust(img, contrasted,1,Vec2i(0, 255),Vec2i(0, 255));
	imshow("contrasted Image", contrasted);
	imshow("orignal grayscale", img);
	threshold(img, binaryImage,100,255,THRESH_BINARY| CV_THRESH_OTSU);
	binaryImage_inv = cv::Scalar::all(255)- cleanupBinary(binaryImage);
	return binaryImage_inv;
}
Mat1b ying_yang::imadjust(const Mat1b& src, Mat1b& dst, int tol, Vec2i in, Vec2i out)
{
    // src : input CV_8UC1 image
    // dst : output CV_8UC1 imge
    // tol : tolerance, from 0 to 100.
    // in  : src image bounds
    // out : dst image buonds

    dst = src.clone();

    tol = max(0, min(100, tol));

    if (tol > 0)
    {
        // Compute in and out limits

        // Histogram
        vector<int> hist(256, 0);
        for (int r = 0; r < src.rows; ++r) {
            for (int c = 0; c < src.cols; ++c) {
                hist[src(r,c)]++;
            }
        }

        // Cumulative histogram
        vector<int> cum = hist;
        for (int i = 1; i < hist.size(); ++i) {
            cum[i] = cum[i - 1] + hist[i];
        }

        // Compute bounds
        int total = src.rows * src.cols;
        int low_bound = total * tol / 100;
        int upp_bound = total * (100-tol) / 100;
        in[0] = distance(cum.begin(), lower_bound(cum.begin(), cum.end(), low_bound));
        in[1] = distance(cum.begin(), lower_bound(cum.begin(), cum.end(), upp_bound));

    }

    // Stretching
    float scale = float(out[1] - out[0]) / float(in[1] - in[0]);
    for (int r = 0; r < dst.rows; ++r)
    {
        for (int c = 0; c < dst.cols; ++c)
        {
            int vs = max(src(r, c) - in[0], 0);
            int vd = min(int(vs * scale + 0.5f) + out[0], out[1]);
            dst(r, c) = saturate_cast<uchar>(vd);
        }
    }

    return dst;
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
