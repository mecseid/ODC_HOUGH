#include "PreProcessingToHough.h"
#include "VesselExtraction.h"
#include "ExudateCandidates.h"

position mainHough(cv::Mat *image)
{
	cv::Mat res = preProcessingToHough(image);
	res = vesselExtraction(&res, 3, 6, 0.1);
	res = exudateCandidates(&res, 6, 9, 0.2);
	//TODO: NINCS KÉSZ
	position resPos;

	double zoom = 576 / image->rows;
	resPos.x /= zoom;
	resPos.y /= zoom;
	if (resPos.x == 0 || resPos.y == 0)
	{
		resPos.x = -1;
		resPos.y = -1;
	}
	return resPos;
}
