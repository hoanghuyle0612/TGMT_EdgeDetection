#pragma once
#include"opencv2/opencv.hpp"
using namespace std;
class Convolution
{
private:
	vector<int> _kernel;
public:
	void setKernel(vector<int> value);
	
	vector<int> getKernel();
	int size();
	void initSobelXKernel();
	
	void initSobelYKernel();
	
	uchar computeConvolution(vector<uchar> data);

};

