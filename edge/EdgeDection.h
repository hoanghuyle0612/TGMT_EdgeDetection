#pragma once
#include"opencv2/opencv.hpp"
#include"Convolution.h"
#define PI 3.14159265
#define minThrehold 100
#define maxThreshold 200
using namespace cv;
using namespace std;
class EdgeDection
{
public:
	int detectBySobel(const Mat& src, Mat& dst, string direction = "both");

	int detectByPrewit(const Mat& src, Mat& dst, string direction = "both");

	int detectByLaplace(const Mat& src, Mat& dst);

	int findGradientAndAngle(const Mat& src, Mat& gradient, Mat& angle);

	int detectByCany(const Mat& src, Mat& dst);
};

vector<uchar> createEmptyVector(int size, int value);
int gaussianBlur(const Mat& src, Mat& dst);

