/*
 * ChannelSelection.h
 *
 *  Created on: 2015 máj. 7
 *      Author: mecseid
 */
#ifndef CHANNELSELECTION_H_
#define CHANNELSELECTION_H_

#include "includes.h"

#define BLUE 0
#define GREEN 1
#define RED 2

/**
 * Get one channel from image
 * @param image where we want the channel
 * @param channelNumber
 * 		0 - Blue
 * 		1 - Green
 * 		2 - Red
 * @return Needed channel
 */
cv::Mat getChannel(const cv::Mat *image, unsigned char channelNumber);

#endif /* CHANNELSELECTION_H_ */
