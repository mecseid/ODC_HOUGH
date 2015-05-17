#include "IntegralImage.h"

cv::Mat IntegralImage(const cv::Mat *image)
{
	cv::Mat sumImage(image->rows, image->cols, CV_8UC1);
	sumImage.at<unsigned char>(0, 0) = image->at<unsigned char>(0, 0);

	for (int i = 1; i < image->rows; i++)
	{
		sumImage.at<unsigned char>(i, 0) = image->at<unsigned char>(i, 0) + sumImage.at<unsigned char>(i - 1, 0);
	}
	for (int i = 1; i < image->cols; i++)
	{
		sumImage.at<unsigned char>(0, i) = image->at<unsigned char>(0, i) + sumImage.at<unsigned char>(0, i - 1);
	}
	for (int i = 1; i < image->rows; i++)
	{
		for (int j = 1; j < image->cols; j++)
		{
			sumImage.at<unsigned char>(i, j) = image->at<unsigned char>(i, j) + sumImage.at<unsigned char>(i - 1, j)
					+ sumImage.at<unsigned char>(i, j - 1) + sumImage.at<unsigned char>(i - 1, j - 1);
		}
	}
	return sumImage;
}
