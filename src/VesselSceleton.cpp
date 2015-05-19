#ifndef VESSELSCELETON_H_
#define VESSELSCELETON_H_

#include "includes.h"

cv::Mat getSkeleton(const cv::Mat *image)
{
	cv::Mat img = image->clone();
	cv::threshold(img, img, 127, 255, cv::THRESH_BINARY);
	cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
	cv::Mat temp;
	cv::Mat eroded;

	cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

	bool done;
	do
	{
		cv::erode(img, eroded, element);
		cv::dilate(eroded, temp, element); // temp = open(img)
		cv::subtract(img, temp, temp);
		cv::bitwise_or(skel, temp, skel);
		eroded.copyTo(img);

		done = (cv::countNonZero(img) == 0);
	} while (!done);
	return skel;
}

cv::Mat vesselSceleton(const cv::Mat *vessel)
{
	cv::Mat skel;
	skel = getSkeleton(vessel);
	// Not sure we want this
	//cv::medianBlur(skel, skel, 3);
	return skel;
}

#endif
