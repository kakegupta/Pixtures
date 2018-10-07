#ifndef PIXTURE_HPP
#define PIXTURE_HPP

#include <opencv2/opencv.hpp>
#include "defines.hpp"
#include "Intensity.hpp"

class Pixture {
	bool bIsValid;
	cv::Mat pixtureImage;
	Intensity** pixelIntensities;
	double** grayScalePixelIntensities;

public:
	int PIXELS_X;
	int PIXELS_Y;
	double PIXEL_WIDTH;
	double PIXEL_HEIGHT;
	int WIDTH;
	int HEIGHT;

public:
	Pixture(string , int, int);
	~Pixture();
	void generatePixelIntensities();
	Intensity** getPixelIntensities();
	cv::Mat getPixtureImage();
	bool isValid();
};

#endif	// PIXTURE_HPP