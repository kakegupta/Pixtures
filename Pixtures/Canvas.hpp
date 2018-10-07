#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <opencv2/opencv.hpp>
#include "defines.hpp"
#include "Intensity.hpp"
#include "Pixture.hpp"
#include "Pixels.hpp"

class Canvas {

	struct Point {
		Point() {
			x = -100;
			y = -100;
		}
		int x;
		int y;
	};

	Pixture* pixture;
	string** canvasPixelFiles;
	cv::Mat** canvasPixelImages;
	cv::Mat pixtureImage;
	Intensity** pixelIntensities;
	vector<string> filePaths;
	vector<Intensity> pixelFileIntensities;
	vector<cv::Mat> pixelImages;
	Point* lastPixel;


public:
	Canvas(Pixture*, Pixels);
	~Canvas();
	void calculateCanvasPixels();
	void renderCanvas(string, int);
};

#endif	// CANVAS_HPP