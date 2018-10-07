#include "Canvas.hpp"

Canvas::Canvas(Pixture* pixture, Pixels pixels) {
	this->pixture = pixture;
	this->pixtureImage = pixture->getPixtureImage();
	this->pixelIntensities = pixture->getPixelIntensities();
	this->filePaths = pixels.getFilePaths();
	this->pixelFileIntensities = pixels.getPixelFileIntensities();
	this->pixelImages = pixels.getPixelImages();
	this->lastPixel = new Point[pixelImages.size()];

	canvasPixelFiles = new string*[pixture->PIXELS_X];
	canvasPixelImages = new cv::Mat*[pixture->PIXELS_X];
	for (int i = 0; i < pixture->PIXELS_X; i++) {
		canvasPixelFiles[i] = new string[pixture->PIXELS_Y];
		canvasPixelImages[i] = new cv::Mat[pixture->PIXELS_Y];
	}
}

Canvas::~Canvas() {
	for (int x = 0; x < pixture->PIXELS_X; x++) {
		delete[] canvasPixelFiles[x];
		delete[] canvasPixelImages[x];
	}
	delete[] canvasPixelFiles;
	delete[] canvasPixelImages;
}

void Canvas::calculateCanvasPixels() {
	for (int x = 0; x < pixture->PIXELS_X; x++) {
		for (int y = 0; y < pixture->PIXELS_Y; y++) {
			Intensity pixelIntensity = pixelIntensities[x][y];
			double minMeanDistance = 1000000;
			double minStdDevDistance = 1000000;
			for (int i = 0; i < pixelFileIntensities.size(); i++) {
				Intensity pixelFileIntensity = pixelFileIntensities[i];
				double meanDistance;
				double stdDevDistance;
				stdDevDistance = pixelIntensity.stdDevDistance(pixelFileIntensity);
				meanDistance = pixelIntensity.meanDistance(pixelFileIntensity);
				
				for (int a = x < 5 ? 0 : x - 5; a < x + 6 && a < pixture->PIXELS_X; a++) {
					for (int b = y < 5 ? 0 : y - 5; b < y + 6 && b < pixture->PIXELS_Y; b++) {
						if (filePaths[i].compare(canvasPixelFiles[a][b]) == 0)
							meanDistance = 1000000;
					}
				}
				

				if (meanDistance < minMeanDistance) {
					if (minMeanDistance > 30) {
						minMeanDistance = meanDistance;
						minStdDevDistance = stdDevDistance;
						canvasPixelFiles[x][y] = filePaths[i];
						canvasPixelImages[x][y] = pixelImages[i];
						lastPixel[i].x = x;
						lastPixel[i].y = y;
					}
					else {
						if (stdDevDistance < minStdDevDistance) {
							minMeanDistance = meanDistance;
							minStdDevDistance = stdDevDistance;
							canvasPixelFiles[x][y] = filePaths[i];
							canvasPixelImages[x][y] = pixelImages[i];
							lastPixel[i].x = x;
							lastPixel[i].y = y;
						}
					}
				}
			}
		}
	}
	cout << "Canvas::calculateCanvasPixles completed" << endl;
}

void Canvas::renderCanvas(string imageNo, int pixelBorder) {
	cv::Mat canvas(pixture->HEIGHT, pixture->WIDTH, CV_8UC3);
	canvas.setTo(cv::Scalar::all(255));
	pixtureImage.copyTo(canvas(cv::Rect(0, 0, pixture->WIDTH, pixture->HEIGHT)));
	for (int x = 0; x < pixture->PIXELS_X; x++) {
		for (int y = 0; y < pixture->PIXELS_Y; y++) {
			cv::Mat pixelImage = canvasPixelImages[x][y];
			double multiplier = double(pixelImage.cols) / (pixture->PIXEL_WIDTH - pixelBorder) > double(pixelImage.rows) / (pixture->PIXEL_HEIGHT - pixelBorder)
								? (double)((pixture->PIXEL_WIDTH - pixelBorder)) / pixelImage.cols
								: (double)((pixture->PIXEL_HEIGHT - pixelBorder)) / pixelImage.rows;
			if (int(pixelImage.cols * multiplier) == 0 || int(pixelImage.rows * multiplier) == 0) {
				return;
			}
			cv::resize(pixelImage, pixelImage, cv::Size(), multiplier, multiplier);

			int xOffset, yOffset;
			xOffset = (pixture->PIXEL_WIDTH - pixelBorder) / 2 - pixelImage.cols / 2;
			yOffset = (pixture->PIXEL_HEIGHT - pixelBorder) / 2 - pixelImage.rows / 2;
			pixelImage.copyTo(canvas(cv::Rect((x * pixture->PIXEL_WIDTH) + (pixelBorder / 2) + xOffset, (y * pixture->PIXEL_HEIGHT) + (pixelBorder/2) + yOffset, pixelImage.cols, pixelImage.rows)));
		}
	}
	cv::imwrite(string(".\\generatedPics3\\image") + imageNo + string(".jpg"), canvas);
	cout << "Canvas::renderCanvas completed" << endl;
}