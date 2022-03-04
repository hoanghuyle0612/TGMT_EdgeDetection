#include "Convolution.h"

void Convolution::setKernel(vector<int> value)
{
	_kernel = value;
}

vector<int> Convolution::getKernel()
{
	return _kernel;
}

int Convolution::size()
{
	return _kernel.size();
}

void Convolution::initSobelXKernel()
{
	/*
	* Function to creat kernel 3x3 of Sobel with X direction
	*/
	_kernel.push_back(-1);
	_kernel.push_back(0);
	_kernel.push_back(1);
	_kernel.push_back(-2);
	_kernel.push_back(0);
	_kernel.push_back(2);
	_kernel.push_back(-1);
	_kernel.push_back(0);
	_kernel.push_back(1);
}

void Convolution::initSobelYKernel()
{
	/*
	* Function to creat kernel 3x3 of Sobel with Y direction
	*/
	_kernel.push_back(1);
	_kernel.push_back(2);
	_kernel.push_back(1);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(-1);
	_kernel.push_back(-2);
	_kernel.push_back(-1);

}

float Convolution::computeConvolution(vector<uchar> data)
{
	/*
	* Function caculate convolution of data matrix with kernel
	* The data was flatted so that we can compute it with just 1 loop
	*/
	float result=0;
	for (int i = 0; i < data.size(); i++)
	{
		result += data[i] * this->_kernel[i];
	}
	return result;
}
