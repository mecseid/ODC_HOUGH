#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

struct position
{
	int x;
	int y;
};

cv::Mat strelDisk34();

cv::Mat strelDisk64();

cv::Mat strelDisk68();

cv::Mat strelDisk98();

cv::Mat applyLut(const cv::Mat *image, const cv::Mat lookUpTable);

cv::Mat applyLut(const cv::Mat *image, const cv::Mat lutOne, const cv::Mat lutTwo);

#endif /* INCLUDES_H_ */
