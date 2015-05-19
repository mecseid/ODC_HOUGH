#include "includes.h"
#include <iostream>

cv::Mat strelDisk34()
{
	return (cv::Mat_<unsigned char>(5, 5) << 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
}

cv::Mat strelDisk64()
{
	return (cv::Mat_<unsigned char>(11, 11) << 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0);
}

cv::Mat strelDisk68()
{
	return (cv::Mat_<unsigned char>(11, 11) << 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
}

cv::Mat strelDisk98()
{
	return (cv::Mat_<unsigned char>(17, 17) << 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0);
}

/*
 * 1 LookUpTable alkalmazása a képre
 */
cv::Mat applyLut(const cv::Mat *image, const cv::Mat lookUpTable)
{
	cv::Mat dst(*image);
	if (dst.type() != CV_16UC1)
	{
		dst.convertTo(dst, CV_16UC1, 1);
	}
	uint16_t data[] =
	{ 256, 32, 4, 128, 16, 2, 64, 8, 1 };
	cv::Mat k(3, 3, CV_16UC1, data);

	filter2D(dst, dst, CV_16UC1, k);
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 1; j < dst.cols; j++)
		{
			dst.at<unsigned char>(i, j) = lookUpTable.at<unsigned char>(0, dst.at<unsigned char>(i, j));
		}
	}

	dst.convertTo(dst, image->type());
	return dst;
}

/*
 * 2 LookUpTable alkalmazása a képre (Matlab-os átírás miatt)
 */
cv::Mat applyLut(const cv::Mat *image, const cv::Mat lutOne, const cv::Mat lutTwo)
{
	cv::Mat dst = applyLut(image, lutOne);
	dst = applyLut(image, lutTwo);
	return dst;
}

cv::Mat fillTheHoles(const cv::Mat *image, unsigned char threshold)
{
	cv::Mat imageThresh;
	cv::threshold(*image, imageThresh, threshold, 255, cv::THRESH_BINARY);
	// Loop through the border pixels and if they're black, floodFill from there
	cv::Mat mask = imageThresh.clone();
	for (int i = 0; i < mask.cols; i++)
	{
		if (mask.at<unsigned char>(0, i) == 0)
		{
			cv::floodFill(mask, cv::Point(i, 0), 255, 0, 10, 10);
		}
		if (mask.at<unsigned char>(mask.rows - 1, i) == 0)
		{
			cv::floodFill(mask, cv::Point(i, mask.rows - 1), 255, 0, 10, 10);
		}
	}
	for (int i = 0; i < mask.rows; i++)
	{
		if (mask.at<unsigned char>(i, 0) == 0)
		{
			cv::floodFill(mask, cv::Point(0, i), 255, 0, 10, 10);
		}
		if (mask.at<unsigned char>(i, mask.cols - 1) == 0)
		{
			cv::floodFill(mask, cv::Point(mask.cols - 1, i), 255, 0, 10, 10);
		}
	}

	// Compare mask with original.
	cv::Mat newImage = image->clone();
	for (int row = 0; row < mask.rows; ++row)
	{
		for (int col = 0; col < mask.cols; ++col)
		{
			if (mask.at<char>(row, col) == 0)
			{
				newImage.at<char>(row, col) = 255;
			}
		}
	}
	return newImage;
}
