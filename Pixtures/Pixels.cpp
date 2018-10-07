#include<io.h>
#include "Pixels.hpp"

#define PIXEL_WIDTH 100
#define PIXEL_HEIGHT 100
#define MAX_RES 1000

Pixels::Pixels(string pixelDir) {
	string filePattern = pixelDir + "\\*.*";
	_finddata_t data;
	int ff = _findfirst(filePattern.c_str(), &data);
	if (ff != -1)
	{
		int res = 0;
		while (res != -1)
		{
			string filePath = pixelDir + "\\" + data.name;
			if (((string)data.name).compare(".") != 0 && ((string)data.name).compare("..") != 0)
				filePaths.push_back(filePath);
			res = _findnext(ff, &data);
		}
		_findclose(ff);
	}
}


void makeImgSquare(cv::Mat &img, cv::Scalar mean){
	cv::Size newSize(std::max(img.cols, img.rows), std::max(img.cols, img.rows));
	cv::Mat newImage = cv::Mat(newSize, CV_8UC3).setTo(mean);

	img.copyTo(newImage(cv::Rect(newImage.cols / 2 - img.cols / 2, newImage.rows / 2 - img.rows / 2, img.cols, img.rows)));
	newImage.copyTo(img);
}

void Pixels::generatePixelFileIntensities() {
	for (int i = 0; i < filePaths.size(); i++) {
		string filePath = filePaths[i];
		cv::Mat pixelImage = cv::imread(filePath);
		
		cv::Rect roi(0, 0, pixelImage.cols, pixelImage.rows);

		//copies input image in roi
		cv::Mat image_roi = pixelImage(roi);

		//computes mean over roi
		Intensity fileIntensity;
		cv::Scalar stdDev;
		cv::Scalar mean;
		cv::meanStdDev(image_roi, mean, stdDev);	
		fileIntensity.meanIntensity = mean;
		fileIntensity.stdDev = stdDev;
		pixelFileIntensities.push_back(fileIntensity);

		grayScalePixelFileIntensities.push_back(pixelFileIntensities[i].getGrayScaleIntensity());

		//make image square
		//makeImgSquare(pixelImage, mean);

		double multiplier = pixelImage.cols > pixelImage.rows ? double(MAX_RES) / pixelImage.cols : double(MAX_RES) / pixelImage.rows;
		cv::resize(pixelImage, pixelImage, cv::Size(), multiplier, multiplier);
		pixelImages.push_back(pixelImage);

		cout << endl << endl << endl;
		//prints out only .val[0] since image was grayscale
		cout << "Pixel intensity over ROI = " << grayScalePixelFileIntensities[i] << endl;
	}
}

vector<Intensity> Pixels::getPixelFileIntensities() {
	return pixelFileIntensities;
}

vector<string> Pixels::getFilePaths() {
	return filePaths;
}

vector<cv::Mat> Pixels::getPixelImages() {
	return pixelImages;
}