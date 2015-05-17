#include "WeightedImage.h"

/*
 * @param image A zöld kép
 * @param M		Mask
 */
cv::Mat weightedImage(const cv::Mat *image, const cv::Mat M)
{
	int N0 = 4300;

	int w;
	/* A magas intenzitású pixelek száma az eredeti zöld képen */
	int N = cv::countNonZero(*image > 200);
	if (N <= N0)
	{
		w = 1;
	}
	else
	{
		w = std::pow(N / N0, 2);
	}
	cv::Mat mask = M > 0;
	cv::Mat weightedImage = *image * w;
	cv::Mat res = M + weightedImage;
	res &= mask;

	return res;
}
