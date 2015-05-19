#ifndef FINALEXUDATEDETECTION_H_
#define FINALEXUDATEDETECTION_H_

#include "includes.h"
#include <iostream>
#include <vector>

/**
 * @param preImage Zöld kép
 */
cv::Mat finalExudateDetection(const cv::Mat *preImage, const cv::Mat *candidateImage, double beta, double gamma)
{
	double min, maxIntensity;
	cv::Mat maskedImage = *preImage & *candidateImage;
	cv::minMaxLoc(maskedImage, &min, &maxIntensity);
	double mean = cv::mean(maskedImage, *candidateImage).val[0];
	double thresh = maxIntensity * beta;
	cv::Mat pathces = *preImage > thresh;
	pathces &= *candidateImage;
	pathces = fillTheHoles(&pathces);
	cv::Mat strongEdge = preImage->clone();
	cv::Mat candMean;
	cv::bitwise_not(*candidateImage, candMean);
	candMean &= mean;
	strongEdge = (strongEdge & *candidateImage) | candMean;
	cv::GaussianBlur(strongEdge, strongEdge, cv::Size(7, 7), 2);
	cv::Canny(strongEdge, strongEdge, gamma, 0);
	cv::Mat oppositeStrongEdge;
	cv::bitwise_not(strongEdge, oppositeStrongEdge);
	cv::Mat erodedCandidate;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ERODE, cv::Size(4, 4));
	cv::erode(*candidateImage, erodedCandidate, kernel);
	cv::bitwise_not(erodedCandidate, erodedCandidate);
	strongEdge = (strongEdge - erodedCandidate) > 0;

	std::vector < std::vector < cv::Point >> contours;
	std::vector < cv::Vec4i > hierarchy;
	cv::findContours(pathces, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	cv::Mat result = cv::Mat::zeros(pathces.size(), CV_8UC1);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		cv::Mat tmp = cv::Mat::zeros(pathces.size(), CV_8UC1);
		cv::Scalar color = cv::Scalar(255);
		cv::drawContours(tmp, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
		tmp &= strongEdge;
		if (cv::sum(tmp).val[0] != 0)
		{
			cv::drawContours(result, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
		}
	}
	//TODO: Nem az igazi
	return result;
}

#endif
