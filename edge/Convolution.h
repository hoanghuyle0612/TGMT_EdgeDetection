#pragma once
#include"opencv2/opencv.hpp"
using namespace std;
class Convolution
{
private:
	vector<float> _kernel;
public:
	Convolution();
	Convolution(int size);
	void setKernel(vector<float> value);
	
	vector<float> getKernel();
	int size();
	void initSobelXKernel();
	
	void initSobelYKernel();

	void initPrewitXKernel();

	void initPrewitYKernel();

	void initLaplaceKernel();
	
	void initGaussKernel();
	
	float computeConvolution(vector<uchar> data);

};

