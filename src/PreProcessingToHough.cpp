#include "PreProcessingToHough.h"
#include "ChannelSelection.h"

cv::Mat preProcessingToHough(const cv::Mat *image)
{
	double zoom = 576.0 / image->rows;
	cv::Mat res;
	cv::resize(*image, res, cv::Size(static_cast<unsigned int>(image->cols * zoom), 576), 0, 0, cv::INTER_LANCZOS4);
	return getChannel(&res, GREEN);
}
