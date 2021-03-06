#ifndef VESSELSCELETON_H_
#define VESSELSCELETON_H_

#include "includes.h"

cv::Mat getSkeleton(const cv::Mat *image);

cv::Mat vesselSceleton(const cv::Mat *vessel);

#endif /* VESSELSCELETON_H_ */
