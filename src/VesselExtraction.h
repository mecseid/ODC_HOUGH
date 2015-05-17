#ifndef VESSELEXTRACTION_H_
#define VESSELEXTRACTION_H_

#include "includes.h"

cv::Mat vesselExtraction(const cv::Mat *image, int structOne, int structTwo, double percentage);

#endif /* VESSELEXTRACTION_H_ */
