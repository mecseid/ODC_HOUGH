#include "ExudateCandidates.h"
#include <iostream>

/**
 * Matlab-os bwmorph emulálás bridge kapcsolóval
 * A bináris képen a nem közvetlen, 1 távolságra lévő bitek összekapcsolása
 *
 */
cv::Mat bwMorphBridge(const cv::Mat *image)
{
	/* Octave-ból LookUpTable */
	cv::Mat lookUpTable =
			(cv::Mat_<float>(1, 1024) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	cv::Mat res;
	cv::threshold(*image, res, 0, 1, cv::THRESH_BINARY);
	int lastPC = std::numeric_limits<int>::max();
	for (int pointCount = cv::countNonZero(res); pointCount < lastPC; pointCount = cv::countNonZero(res))
	{
		lastPC = pointCount;
		res = applyLut(image, lookUpTable);
	}
	res *= 255;
	return res;
}

cv::Mat exudateCandidates(const cv::Mat *image, int structOne, int structTwo, double threshold)
{
	cv::Mat B1 = strelDisk68();
	cv::Mat B2 = strelDisk98();
	cv::Mat dilate1, dilate2;
	cv::dilate(*image, dilate1, B1);
	cv::dilate(*image, dilate2, B2);
	cv::Mat edge = dilate2 - dilate1;
	// Valós számmá konvertáljuk a pixeleket
	edge.convertTo(edge, CV_32F, 1);

	double min, max;
	cv::minMaxLoc(edge, &min, &max);
	edge /= max;
	cv::Mat bwEdge = edge > threshold;
	// Bridge the pixels
	bwEdge = bwMorphBridge(&bwEdge);
	// A képen található "lyukak" elsimítása
	// Vissza unsigned char-ra
	bwEdge.convertTo(bwEdge, CV_8UC1, 1);
	cv::Mat res;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
	cv::morphologyEx(bwEdge, res, cv::MORPH_OPEN, kernel);
	/*
	 cv::Mat inv;
	 cv::bitwise_not( bwEdge, inv );
	 std::vector<std::vector<cv::Point>> contours;
	 cv::findContours( inv, contours, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE );
	 for( std::vector<cv::Point> contour : contours ) {
	 cv::drawContours( inv, contour, 0, 255, -1 );
	 }
	 cv::Mat res;
	 cv::bitwise_not( inv, res );
	 */
	return res;
}
