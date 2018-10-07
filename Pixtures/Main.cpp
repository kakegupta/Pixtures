#include "Pixels.hpp"
#include "Pixture.hpp"
#include "Canvas.hpp"
#include <io.h>


void dataCollector(){
	cv::VideoCapture movie("TheDarkKnight.mkv");
	cv::Mat frame;

	if (!movie.isOpened()){
		std::cout << "Could not open movie\n";
	}

	while (1){
		movie >> frame;

		cv::imshow("frame", frame);
		cv::waitKey(1);
	}
}


void sizeTester(const cv::Mat &img){
	cv::Mat temp;
	int size = 20;

	while (1){
		cv::resize(img, temp, cv::Size(size, size));
		cv::resize(temp, temp, img.size());


		std::cout << "Size is " << size << '\n';
		cv::imshow("Temp", temp);
		char key = cv::waitKey(0);

		if (key == 'u')
			size += 2;
		if (key == 'd')
			size -= 2;
	}


}

vector<string> getFilePaths(string pixtureFileDir) {
	vector<string> filePaths;

	string filePattern = pixtureFileDir + "\\*.*";
	_finddata_t data;
	int ff = _findfirst(filePattern.c_str(), &data);
	if (ff != -1)
	{
		int res = 0;
		while (res != -1)
		{
			string filePath = pixtureFileDir + "\\" + data.name;
			if (((string)data.name).compare(".") != 0 && ((string)data.name).compare("..") != 0)
				filePaths.push_back(filePath);
			res = _findnext(ff, &data);
		}
		_findclose(ff);
	}
	return filePaths;
}


int main(int argc, char* argv[]) {

	cv::Mat im = cv::imread("joker7.jpg");
	cv::resize(im, im, cv::Size(), 10, 10);
	cv::imwrite("jokerLarge.jpg", im);


	string renderFileDir;
	cout << "enter render Dir"<<endl;
	getline(cin, renderFileDir);
	Pixels pixels(renderFileDir);
	pixels.generatePixelFileIntensities();	

	string pixFilePath;
	while (1) {
		cout << "Enter pix" << endl;
		getline(cin, pixFilePath);
		int PIXELS_X, PIXELS_Y;
		int pixelBorder;
		cout << "Enter X pixels" << endl;
		cin >> PIXELS_X;
		cout << "Enter Y pixels" << endl;
		cin >> PIXELS_Y;
		cout << "Enter Pixel Border Width" << endl;
		cin >> pixelBorder;
		if (pixFilePath.compare("") == 0)
			continue;
		Pixture pixture(pixFilePath, PIXELS_X, PIXELS_Y);
		if (!pixture.isValid())
			continue;
		pixture.generatePixelIntensities();
		Canvas canvas(&pixture, pixels);
		canvas.calculateCanvasPixels();
		canvas.renderCanvas("0", pixelBorder);
		cin.clear();
		cin.ignore();
	}
	return 0;
}