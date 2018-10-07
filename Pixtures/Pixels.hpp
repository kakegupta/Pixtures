#include <iostream>
#ifndef PIXELS_HPP
#define PIXELS_HPP

#include <opencv2/opencv.hpp>
#include "defines.hpp"
#include "Intensity.hpp"

class Pixels {

	vector<string> filePaths;
	vector<Intensity> pixelFileIntensities;
	vector<double> grayScalePixelFileIntensities;
	vector<cv::Mat> pixelImages;

public:
	Pixels(string);
	void generatePixelFileIntensities();
	vector<Intensity> getPixelFileIntensities();
	vector<string> getFilePaths();
	vector<cv::Mat> getPixelImages();
};

#endif	// PIXELS_HPP