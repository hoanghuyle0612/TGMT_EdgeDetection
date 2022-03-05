#pragma once
#include"opencv2/opencv.hpp"
using namespace std;
class Convolution
{
private:
	vector<int> _kernel;
public:
	Convolution();
	void setKernel(vector<int> value);
	
	vector<int> getKernel();
	int size();
	void initSobelXKernel();
	
	void initSobelYKernel();

	void initPrewitXKernel();

	void initPrewitYKernel();
	
	
	float computeConvolution(vector<uchar> data);

};

