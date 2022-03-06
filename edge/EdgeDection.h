#pragma once
#include"opencv2/opencv.hpp"
#include"Convolution.h"
#define PI 3.14159265
#define minThrehold 50 //Threshold use for canny
#define maxThreshold 200
using namespace cv;
using namespace std;
class EdgeDection
{
public:

	/*
	* Function detect edge using Sobel
	* src is the source image
	* dst is the result image
	* direction is we detect edge by X or Y direction. direction have three value: x,y or both
	*/
	int detectBySobel(const Mat& src, Mat& dst, string direction = "both");

	/*
	* Function detect edge using Prewit
	* src is the source image
	* dst is the result image
	* direction is we detect edge by X or Y direction. direction have three value: x,y or both
	*/
	int detectByPrewit(const Mat& src, Mat& dst, string direction = "both");

	/*
	* Function detect edge using Sobel
	* src is the source image
	* dst is the result image
	*/
	int detectByLaplace(const Mat& src, Mat& dst);

	/*This function cumpute the gradient and angle of image src.
	*It use for canny edge detetion
	*/
	int findGradientAndAngle(const Mat& src, Mat& gradient, Mat& angle);

	/*
	* Function detect edge using Sobel
	* src is the source image
	* dst is the result image
	* * The idea of ​​this function is https://minhng.info/tutorials/xu-ly-anh-opencv-hien-thuc-canny-edge.html
	* Thank to Minh Nguyen
	*/
	int detectByCanny(const Mat& src, Mat& dst);
};

/*
* This function create an empty array of size with value of 0
*/
vector<uchar> createEmptyVector(int size, int value);

/*
* Gaussian Blur function, use for canny edge detection
* src is the source image
* dst is the result image
*/
int gaussianBlur(const Mat& src, Mat& dst);

