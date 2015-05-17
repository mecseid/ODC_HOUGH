#include "ChannelSelection.h"

cv::Mat getChannel(const cv::Mat *image, unsigned char channelNumber)
{
	cv::Mat channel[3];
	cv::split(*image, channel);
	return channel[channelNumber];
}
