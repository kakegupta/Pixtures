#include "Intensity.hpp"

double Intensity::meanDistance(Intensity inputIntensity) {
	return ((this->meanIntensity.val[0] - inputIntensity.meanIntensity.val[0])*(this->meanIntensity.val[0] - inputIntensity.meanIntensity.val[0]))
		+ ((this->meanIntensity.val[1] - inputIntensity.meanIntensity.val[1])*(this->meanIntensity.val[1] - inputIntensity.meanIntensity.val[1]))
		+ ((this->meanIntensity.val[2] - inputIntensity.meanIntensity.val[2])*(this->meanIntensity.val[2] - inputIntensity.meanIntensity.val[2]));
}

double Intensity::stdDevDistance(Intensity inputIntensity) {
	return ((this->stdDev.val[0] - inputIntensity.stdDev.val[0])*(this->stdDev.val[0] - inputIntensity.stdDev.val[0]))
		+ ((this->stdDev.val[1] - inputIntensity.stdDev.val[1])*(this->stdDev.val[1] - inputIntensity.stdDev.val[1]))
		+ ((this->stdDev.val[2] - inputIntensity.stdDev.val[2])*(this->stdDev.val[2] - inputIntensity.stdDev.val[2]));
}

double Intensity::getGrayScaleIntensity() {
	return (this->meanIntensity.val[0] + this->meanIntensity.val[1] + this->meanIntensity.val[2]) / 3;
}
