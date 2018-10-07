#ifndef INTENSITY_HPP
#define INTENSITY_HPP

#include <opencv2\opencv.hpp>

class Intensity {
public:
	cv::Scalar meanIntensity;
	cv::Scalar stdDev;

	double meanDistance(Intensity);
	double stdDevDistance(Intensity);
	double getGrayScaleIntensity();
};

#endif	// INTENSITY_HPP