#ifndef LOCALIZEOPTICDISC_H_
#define LOCALIZEOPTICDISC_H_

#include "includes.h"

position localizeOpticDisk(const cv::Mat *image, double windSize)
{
	char meanImage[image->rows][image->cols];
	for (int i = windSize + 1; i < image->rows; i++)
	{
		for (int j = windSize + 1; j < image->cols; j++)
		{
			meanImage[i][j] = image->at<cv::Vec3b>(i - windSize - 1, j - windSize - 1)[1]
					+ image->at<cv::Vec3b>(i + windSize, j + windSize)[1]
					- image->at<cv::Vec3b>(i + windSize, j - windSize - 1)[1]
					- image->at<cv::Vec3b>(i - windSize - 1, j + windSize)[1];
		}
	}
	cv::Mat mImage(image->rows, image->cols, 1, meanImage);
	mImage /= std::pow(windSize, 2);
	double min, max;
	cv::minMaxLoc(mImage, &min, &max);
	mImage = mImage == max;
	/* TODO:
	 [X,Y] = find(meanIm);

	 ind = 1;
	 if (size(X,1)>1)
	 x_seged = abs(X - (height/2));
	 [c ind]=min(x_seged);
	 end

	 x = X(ind);
	 y = Y(ind);
	 */
	position pos;
	return pos;
}

#endif
