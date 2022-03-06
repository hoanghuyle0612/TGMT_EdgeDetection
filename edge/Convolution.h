#pragma once
#include"opencv2/opencv.hpp"
using namespace std;
class Convolution
{
private:
	vector<float> _kernel;
public:
	/*
	* Default constructor will create an 3x3 kernel with value 0
	*/
	Convolution();

	/*
	* This constructor will create an mxm kernel depends on m
	*/
	Convolution(int size);

	/*Get set Function of kernel
	*/
	void setKernel(vector<float> value);
	vector<float> getKernel();

	/*
	* Return total elements of kernel
	*/
	int size();

	/*
	* This function create an 3x3 kernel of Sobel by X direction
	*/
	void initSobelXKernel();
	
	/*
	* This function create an 3x3 kernel of Sobel by Y direction
	*/
	void initSobelYKernel();

	/*
	* This function create an 3x3 kernel of Prewit by X direction
	*/
	void initPrewitXKernel();

	/*
	* This function create an 3x3 kernel of Prewit by Y direction
	*/
	void initPrewitYKernel();

	/*
	* This function create an 3x3 kernel of Laplace
	*/
	void initLaplaceKernel();
	
	/*
	* This function create an 5x5 kernel of Gaussian with o= 1.4
	*/
	void initGaussKernel();
	
	/*Compute convoluiton with the given data and inited kernel
	*/
	float computeConvolution(vector<uchar> data);

};

