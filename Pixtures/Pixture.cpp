#include "Pixture.hpp"

Pixture::Pixture(string pixtureFile, int PIXELS_X, int PIXELS_Y) {
	bIsValid = false;
	pixtureImage = cv::imread(pixtureFile);
	WIDTH = pixtureImage.cols;
	HEIGHT = pixtureImage.rows;
	if (pixtureImage.cols == 0 || pixtureImage.cols == 0)
		return;

	this->PIXELS_X = PIXELS_X;
	this->PIXELS_Y = PIXELS_Y;
	PIXEL_WIDTH = double(WIDTH) / PIXELS_X;
	PIXEL_HEIGHT = double(HEIGHT) / PIXELS_Y;
	cv::resize(pixtureImage, pixtureImage, cv::Size(WIDTH, HEIGHT));

	pixelIntensities = new Intensity*[PIXELS_X];
	grayScalePixelIntensities = new double*[PIXELS_X];
	for (int x = 0; x < PIXELS_X; x++) {
		pixelIntensities[x] = new Intensity[PIXELS_Y];
		grayScalePixelIntensities[x] = new double[PIXELS_Y];
	}
	bIsValid = true;
}

void Pixture::generatePixelIntensities() {
	for (int x = 0; x < PIXELS_X; x++) {
		for (int y = 0; y < PIXELS_Y; y++) {
			//defines roi
			cv::Rect roi(x*PIXEL_WIDTH, y*PIXEL_HEIGHT, PIXEL_WIDTH, PIXEL_HEIGHT);

			//copies input image in roi
			cv::Mat image_roi = pixtureImage(roi);

			//computes mean over roi
			cv::Scalar stdDev;
			cv::Scalar mean;
			cv::meanStdDev(image_roi, mean, stdDev);
			pixelIntensities[x][y].meanIntensity = mean;
			pixelIntensities[x][y].stdDev = stdDev;
			grayScalePixelIntensities[x][y] = pixelIntensities[x][y].getGrayScaleIntensity();

			//prints out only .val[0] since image was grayscale
			cout << "Pixel intensity over ROI = " << grayScalePixelIntensities[x][y] << endl;
		}
	}
	cout << "Pixture::generatePixelIntensities completed" << endl;
}

Pixture::~Pixture() {
	if (!isValid())
		return;
	for (int x = 0; x < PIXELS_X; x++) {
		delete[] pixelIntensities[x];
		delete[] grayScalePixelIntensities[x];
	}
	delete[] pixelIntensities;
	delete[] grayScalePixelIntensities;
}

Intensity** Pixture::getPixelIntensities() {
	return pixelIntensities;
}

cv::Mat Pixture::getPixtureImage() {
	return pixtureImage;
}

bool Pixture::isValid() {
	return bIsValid;
}