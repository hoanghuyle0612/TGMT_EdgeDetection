#include "Convolution.h"

Convolution::Convolution()
{
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
	_kernel.push_back(0);
}

Convolution::Convolution(int size)
{
	for (int i = 0; i < size * size; i++)
	{
		_kernel.push_back(0);
	}
}

void Convolution::setKernel(vector<float> value)
{
	_kernel = value;
}

vector<float> Convolution::getKernel()
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
	* Function to create kernel 3x3 of Sobel with X direction
	*/
	_kernel[0]=-1;
	_kernel[1]=0;
	_kernel[2]=1;
	_kernel[3]=-2;
	_kernel[4]=0;
	_kernel[5]=2;
	_kernel[6]=-1;
	_kernel[7]=0;
	_kernel[8]=1;
}

void Convolution::initSobelYKernel()
{
	/*
	* Function to creat kernel 3x3 of Sobel with Y direction
	*/
	_kernel[0] = 1;
	_kernel[1] = 2;
	_kernel[2] = 1;
	_kernel[3] = 0;
	_kernel[4] = 0;
	_kernel[5] = 0;
	_kernel[6] = -1;
	_kernel[7] = -2;
	_kernel[8] = -1;

}

void Convolution::initPrewitXKernel()
{
	/*
	* Function to creat kernel 3x3 of Prewit with X direction
	*/
	_kernel[0] = 1;
	_kernel[1] = 0;
	_kernel[2] = -1;
	_kernel[3] = 1;
	_kernel[4] = 0;
	_kernel[5] = -1;
	_kernel[6] = 1;
	_kernel[7] = 0;
	_kernel[8] = -1;
}

void Convolution::initPrewitYKernel()
{
	/*
	* Function to creat kernel 3x3 of Prewit with Y direction
	*/
	_kernel[0] = 1;
	_kernel[1] = 1;
	_kernel[2] = 1;
	_kernel[3] = 0;
	_kernel[4] = 0;
	_kernel[5] = 0;
	_kernel[6] = -1;
	_kernel[7] = -1;
	_kernel[8] = -1;
}

void Convolution::initLaplaceKernel()
{
	_kernel[0] = -1;
	_kernel[1] = -1;
	_kernel[2] = -1;
	_kernel[3] = -1;
	_kernel[4] = 8;
	_kernel[5] = -1;
	_kernel[6] = -1;
	_kernel[7] = -1;
	_kernel[8] = -1;
}

void Convolution::initGaussKernel()
{
	float gaussCoefficient = 1 / 159.0;
	_kernel[0] = gaussCoefficient * 2;
	_kernel[1] = gaussCoefficient * 4;
	_kernel[2] = gaussCoefficient * 5;
	_kernel[3] = gaussCoefficient * 4;
	_kernel[4] = gaussCoefficient * 2;
	_kernel[5] = gaussCoefficient * 4;
	_kernel[6] = gaussCoefficient * 9;
	_kernel[7] = gaussCoefficient * 12;
	_kernel[8] = gaussCoefficient * 9;
	_kernel[9] = gaussCoefficient * 4;
	_kernel[10] = gaussCoefficient * 5;
	_kernel[11] = gaussCoefficient * 12;
	_kernel[12] = gaussCoefficient * 15;
	_kernel[13] = gaussCoefficient * 12;
	_kernel[14] = gaussCoefficient * 5;
	_kernel[15] = gaussCoefficient * 4;
	_kernel[16] = gaussCoefficient * 9;
	_kernel[17] = gaussCoefficient * 12;
	_kernel[18] = gaussCoefficient * 9;
	_kernel[19] = gaussCoefficient * 4;
	_kernel[20] = gaussCoefficient * 2;
	_kernel[21] = gaussCoefficient * 4;
	_kernel[22] = gaussCoefficient * 5;
	_kernel[23] = gaussCoefficient * 4;
	_kernel[24] = gaussCoefficient * 2;
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
