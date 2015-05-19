#ifndef FINALEXUDATEDETECTION_H_
#define FINALEXUDATEDETECTION_H_

#include "includes.h"

cv::Mat finalExudateDetection(const cv::Mat *preImage, const cv::Mat *candidateImage, double beta, double gamma);

#endif /* FINALEXUDATEDETECTION_H_ */
