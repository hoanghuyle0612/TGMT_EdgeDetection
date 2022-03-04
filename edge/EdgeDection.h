#pragma once
#include"opencv2/opencv.hpp"
using namespace cv;
using namespace std;
class EdgeDection
{
public:
	int detectBySobel(const Mat& src, Mat& dst, string direction = "both");
};

vector<uchar> createEmptyVector(int size, int value);


