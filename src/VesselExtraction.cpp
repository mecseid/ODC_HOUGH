#include "VesselExtraction.h"

cv::Mat vesselExtraction(const cv::Mat *image, int structOne, int structTwo, double percentage)
{
	//cv::Mat B1 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(structOne, 4));
	cv::Mat B1 = strelDisk34();
	cv::Mat B2 = strelDisk64();
	//cv::Mat B2 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(structTwo, 4));
	cv::Mat dilate;
	cv::dilate(*image, dilate, B2);
	cv::Mat erodeOne;
	cv::erode(dilate, erodeOne, B2);
	cv::dilate(*image, dilate, B1);
	cv::Mat erodeTwo;
	cv::erode(dilate, erodeTwo, B1);

	cv::Mat vessel = erodeOne - erodeTwo;

	double min, max;
	cv::minMaxLoc(vessel, &min, &max);
	cv::Mat res = vessel > (max * percentage);
	cv::medianBlur(res, vessel, 5);
	return vessel;
}
