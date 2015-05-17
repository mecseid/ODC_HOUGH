#include "MainHough.h"
#include "includes.h"

#include "PreProcessingToHough.h"
#include "VesselExtraction.h"
#include "ExudateCandidates.h"

#include <iostream>

int main(int argc, char* argv[])
{
	cv::Mat image;
	//image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
	image = cv::imread("/home/mecseid/workspace/ODC/img/input.png");
	cv::Mat greenImage = preProcessingToHough(&image);
	cv::imwrite("/home/mecseid/workspace/ODC/output/PreProcessingToHoughC++.png", greenImage);
	cv::Mat vessel = vesselExtraction(&greenImage, 3, 6, 0.1);
	cv::imwrite("/home/mecseid/workspace/ODC/output/VesselExtractionC++.png", vessel);
	cv::Mat exudates = exudateCandidates(&greenImage, 6, 9, 0.2);
	cv::imwrite("/home/mecseid/workspace/ODC/output/ExudateCandidatesC++.png", exudates);
	std::cout << "Complete..." << std::endl;
	//position res = mainHough(&image);
	//std::cout << res.x << " " << res.y;
}
