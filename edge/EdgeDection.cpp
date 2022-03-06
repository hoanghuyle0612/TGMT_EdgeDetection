#include "EdgeDection.h"
#include"Convolution.h"
int EdgeDection::detectBySobel(const Mat& src, Mat& dst, string direction)
{

	if (!src.data)
	{
		return 0;
	}
	
	int width = src.cols;
	int height = src.rows;
	int widthStep = src.step[0];
	int nChannel = src.step[1];
	
	dst = Mat(height, width, src.type());

	uchar* pData = (uchar*)src.data;
	uchar* dstData = (uchar*)dst.data;
	if (direction == "x" || direction == "X" || direction == "y" || direction == "Y")
	{

		Convolution con;
		if (direction == "x" || direction == "X") {
			con.initSobelXKernel();
		}
		else if (direction == "y" || direction == "Y") {
			con.initSobelYKernel();
			
		}
		
		for (int y = 1; y < height - 1; y++)
		{
			for (int x = 1; x < width - 1; x++)
			{

				if (nChannel == 1) {
					vector<uchar>data = createEmptyVector(con.size(), 0);
					float value;
					data[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					data[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					data[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];

					data[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					data[4] = (uchar)pData[y * widthStep + x * nChannel];
					data[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];

					data[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					data[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					data[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];

					value = con.computeConvolution(data);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(value);
					
				}
				else if (nChannel == 3)
				{
					vector<uchar> B = createEmptyVector(con.size(), 0);

					float valueB;

					B[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					B[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					B[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];
					B[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					B[4] = (uchar)pData[y * widthStep + x * nChannel];
					B[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];
					B[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					B[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					B[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];



					vector<uchar> G = createEmptyVector(con.size(), 0);

					float valueG;
					G[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 1];
					G[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 1];
					G[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 1];

					G[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 1];
					G[4] = (uchar)pData[y * widthStep + x * nChannel + 1];
					G[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 1];

					G[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 1];
					G[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 1];
					G[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 1];



					vector<uchar> R = createEmptyVector(con.size(), 0);

					float valueR;
					R[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 2];
					R[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 2];
					R[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 2];

					R[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 2];
					R[4] = (uchar)pData[y * widthStep + x * nChannel + 2];
					R[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 2];

					R[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 2];
					R[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 2];
					R[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 2];


					valueB = con.computeConvolution(B);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(valueB);

					valueG = con.computeConvolution(G);
					dstData[y * widthStep + x * nChannel + 1] = saturate_cast<uchar>(valueG);

					valueR = con.computeConvolution(R);
					dstData[y * widthStep + x * nChannel + 2] = saturate_cast<uchar>(valueR);

					
				}
				else return 0;
			}
		}
		return 1;
	}
		
	else if(direction=="both") {
		Convolution conX;
		conX.initSobelXKernel();
		Convolution conY;
		conY.initSobelYKernel();

		for (int y = 1; y < height - 1; y++)
		{
			for (int x = 1; x < width - 1; x++)
			{
				if (nChannel == 1) {
					vector<uchar>data = createEmptyVector(conX.size(), 0);
					float valueX, valueY;
					data[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					data[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					data[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];

					data[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					data[4] = (uchar)pData[y * widthStep + x * nChannel];
					data[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];

					data[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					data[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					data[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];

					valueX = conX.computeConvolution(data);
					valueY = conY.computeConvolution(data);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(sqrt(valueX * valueX + valueY * valueY));
					
				}
				else if (nChannel == 3)
				{
					vector<uchar> B = createEmptyVector(conX.size(), 0);

					float valueBX, valueBY;

					B[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					B[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					B[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];
					B[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					B[4] = (uchar)pData[y * widthStep + x * nChannel];
					B[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];
					B[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					B[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					B[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];



					vector<uchar> G = createEmptyVector(conX.size(), 0);

					float valueGX, valueGY;
					G[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 1];
					G[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 1];
					G[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 1];

					G[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 1];
					G[4] = (uchar)pData[y * widthStep + x * nChannel + 1];
					G[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 1];

					G[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 1];
					G[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 1];
					G[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 1];



					vector<uchar> R = createEmptyVector(conX.size(), 0);

					float valueRX, valueRY;
					R[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 2];
					R[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 2];
					R[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 2];

					R[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 2];
					R[4] = (uchar)pData[y * widthStep + x * nChannel + 2];
					R[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 2];

					R[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 2];
					R[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 2];
					R[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 2];


					valueBX = conX.computeConvolution(B);
					valueBY = conY.computeConvolution(B);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(sqrt(valueBX * valueBX + valueBY * valueBY));


					valueGX = conX.computeConvolution(G);
					valueGY = conY.computeConvolution(G);
					dstData[y * widthStep + x * nChannel + 1] = saturate_cast<uchar>(sqrt(valueGX * valueGX + valueGY * valueGY));

					valueRX = conX.computeConvolution(R);
					valueRY = conY.computeConvolution(R);
					dstData[y * widthStep + x * nChannel + 2] = saturate_cast<uchar>(sqrt(valueRX * valueRX + valueRY * valueRY));
					return 1;
				}
				else return 0;
			}
		}
		return 1;
	}
	else return 0;
	
}

int EdgeDection::detectByPrewit(const Mat& src, Mat& dst, string direction)
{
	if (!src.data)
	{
		return 0;
	}

	int width = src.cols;
	int height = src.rows;
	int widthStep = src.step[0];
	int nChannel = src.step[1];
	dst = Mat(height, width, src.type());

	uchar* pData = (uchar*)src.data;
	uchar* dstData = (uchar*)dst.data;
	if (direction == "x" || direction == "X" || direction == "y" || direction == "Y")
	{

		Convolution con;
		if (direction == "x" || direction == "X") {
			con.initPrewitXKernel();
		}
		else if (direction == "y" || direction == "Y") {
			con.initPrewitYKernel();
		}
		for (int y = 1; y < height - 1; y++)
		{
			for (int x = 1; x < width - 1; x++)
			{

				if (nChannel == 1) {
					vector<uchar>data = createEmptyVector(con.size(), 0);
					float value;
					data[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					data[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					data[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];

					data[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					data[4] = (uchar)pData[y * widthStep + x * nChannel];
					data[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];

					data[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					data[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					data[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];

					value = con.computeConvolution(data);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(value);
					
				}
				else if (nChannel == 3)
				{
					vector<uchar> B = createEmptyVector(con.size(), 0);

					float valueB;

					B[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					B[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					B[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];
					B[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					B[4] = (uchar)pData[y * widthStep + x * nChannel];
					B[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];
					B[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					B[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					B[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];



					vector<uchar> G = createEmptyVector(con.size(), 0);

					float valueG;
					G[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 1];
					G[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 1];
					G[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 1];

					G[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 1];
					G[4] = (uchar)pData[y * widthStep + x * nChannel + 1];
					G[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 1];

					G[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 1];
					G[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 1];
					G[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 1];



					vector<uchar> R = createEmptyVector(con.size(), 0);

					float valueR;
					R[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 2];
					R[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 2];
					R[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 2];

					R[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 2];
					R[4] = (uchar)pData[y * widthStep + x * nChannel + 2];
					R[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 2];

					R[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 2];
					R[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 2];
					R[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 2];


					valueB = con.computeConvolution(B);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(valueB);

					valueG = con.computeConvolution(G);
					dstData[y * widthStep + x * nChannel + 1] = saturate_cast<uchar>(valueG);

					valueR = con.computeConvolution(R);
					dstData[y * widthStep + x * nChannel + 2] = saturate_cast<uchar>(valueR);

					
				}
				else return 0;
			}
		}
		return 1;
	}

	else if (direction == "both") {
		Convolution conX;
		conX.initPrewitXKernel();
		Convolution conY;
		conY.initPrewitYKernel();

		for (int y = 1; y < height - 1; y++)
		{
			for (int x = 1; x < width - 1; x++)
			{
				if (nChannel == 1) {
					vector<uchar>data = createEmptyVector(conX.size(), 0);
					float valueX, valueY;
					data[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					data[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					data[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];

					data[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					data[4] = (uchar)pData[y * widthStep + x * nChannel];
					data[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];

					data[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					data[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					data[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];

					valueX = conX.computeConvolution(data);
					valueY = conY.computeConvolution(data);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(sqrt(valueX * valueX + valueY * valueY));
					
				}
				else if (nChannel == 3)
				{
					vector<uchar> B = createEmptyVector(conX.size(), 0);

					float valueBX, valueBY;

					B[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
					B[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
					B[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];
					B[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
					B[4] = (uchar)pData[y * widthStep + x * nChannel];
					B[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];
					B[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
					B[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
					B[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];



					vector<uchar> G = createEmptyVector(conX.size(), 0);

					float valueGX, valueGY;
					G[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 1];
					G[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 1];
					G[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 1];

					G[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 1];
					G[4] = (uchar)pData[y * widthStep + x * nChannel + 1];
					G[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 1];

					G[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 1];
					G[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 1];
					G[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 1];



					vector<uchar> R = createEmptyVector(conX.size(), 0);

					float valueRX, valueRY;
					R[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 2];
					R[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 2];
					R[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 2];

					R[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 2];
					R[4] = (uchar)pData[y * widthStep + x * nChannel + 2];
					R[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 2];

					R[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 2];
					R[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 2];
					R[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 2];


					valueBX = conX.computeConvolution(B);
					valueBY = conY.computeConvolution(B);
					dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(sqrt(valueBX * valueBX + valueBY * valueBY));


					valueGX = conX.computeConvolution(G);
					valueGY = conY.computeConvolution(G);
					dstData[y * widthStep + x * nChannel + 1] = saturate_cast<uchar>(sqrt(valueGX * valueGX + valueGY * valueGY));

					valueRX = conX.computeConvolution(R);
					valueRY = conY.computeConvolution(R);
					dstData[y * widthStep + x * nChannel + 2] = saturate_cast<uchar>(sqrt(valueRX * valueRX + valueRY * valueRY));
					
				}
				else return 0;
			}
		}
		return 1;
	}
	else return 0;
}

int EdgeDection::detectByLaplace(const Mat& src, Mat& dst)
{
	if (!src.data)
	{
		return 0;
	}

	int width = src.cols;
	int height = src.rows;
	int widthStep = src.step[0];
	int nChannel = src.step[1];
	dst = Mat(height, width, src.type());

	uchar* pData = (uchar*)src.data;
	uchar* dstData = (uchar*)dst.data;

	Convolution con;
	con.initLaplaceKernel();
	for (int y = 1; y < height - 1; y++)
	{
		for (int x = 1; x < width - 1; x++)
		{

			if (nChannel == 1) {
				vector<uchar>data = createEmptyVector(con.size(), 0);
				float value;
				data[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
				data[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
				data[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];

				data[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
				data[4] = (uchar)pData[y * widthStep + x * nChannel];
				data[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];

				data[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
				data[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
				data[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];

				value = con.computeConvolution(data);
				dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(value);

			}
			else if (nChannel == 3)
			{
				vector<uchar> B = createEmptyVector(con.size(), 0);

				float valueB;

				B[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
				B[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
				B[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];
				B[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
				B[4] = (uchar)pData[y * widthStep + x * nChannel];
				B[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];
				B[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
				B[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
				B[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];



				vector<uchar> G = createEmptyVector(con.size(), 0);

				float valueG;
				G[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 1];
				G[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 1];
				G[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 1];

				G[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 1];
				G[4] = (uchar)pData[y * widthStep + x * nChannel + 1];
				G[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 1];

				G[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 1];
				G[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 1];
				G[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 1];



				vector<uchar> R = createEmptyVector(con.size(), 0);

				float valueR;
				R[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 2];
				R[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel + 2];
				R[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 2];

				R[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel + 2];
				R[4] = (uchar)pData[y * widthStep + x * nChannel + 2];
				R[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel + 2];

				R[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 2];
				R[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel + 2];
				R[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 2];


				valueB = con.computeConvolution(B);
				dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(valueB);

				valueG = con.computeConvolution(G);
				dstData[y * widthStep + x * nChannel + 1] = saturate_cast<uchar>(valueG);

				valueR = con.computeConvolution(R);
				dstData[y * widthStep + x * nChannel + 2] = saturate_cast<uchar>(valueR);


			}
			else return 0;
		}
	}
	return 1;

}

int EdgeDection::findGradientAndAngle(const Mat& src, Mat& gradient, Mat& angle)
{
	if (!src.data)
	{		
		return 0;
	}

	int width = src.cols;
	int height = src.rows;
	int widthStep = src.step[0];
	int nChannel = src.step[1];
	
	gradient = Mat(height, width, src.type());
	angle = Mat(height, width, src.type());
	

	uchar* pData = (uchar*)src.data;
	uchar* gradientData = (uchar*)gradient.data;
	uchar* angleData = (uchar*)angle.data;
	Convolution conX;
	conX.initSobelXKernel();
	Convolution conY;
	conY.initSobelYKernel();

	for (int y = 1; y < height - 1; y++)
	{
		for (int x = 1; x < width - 1; x++)
		{
			if (nChannel == 1) {
				vector<uchar>data = createEmptyVector(conX.size(), 0);
				float Gx, Gy,angle;
				data[0] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
				data[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
				data[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];

				data[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
				data[4] = (uchar)pData[y * widthStep + x * nChannel];
				data[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];

				data[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
				data[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
				data[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];

				Gx = conX.computeConvolution(data);
				Gy = conY.computeConvolution(data);

				/*Compute gradient of image*/
				gradientData[y * widthStep + x * nChannel] = saturate_cast<uchar>(sqrt(Gx * Gx + Gy * Gy));
				/*Compute angle gradient of image*/
				angle=atan(Gx / Gy) * 180 / PI;
				 /*Round angel to 4 directions*/
				if (angle <=22.5 )
				{
					angleData[y * widthStep + x * nChannel] = 0;
				}
				if (angle >= 157.5)
				{
					angleData[y * widthStep + x * nChannel] = 0;
				}
				else if (angle>22.5&&angle<67.5) {
					angleData[y * widthStep + x * nChannel] = 45;
				}
				else if (angle >= 67.5 &&angle <= 112.5)
				{
					angleData[y * widthStep + x * nChannel] = 90;
				}
				else if (angle > 112.5 && angle < 157.5)
				{
					angleData[y * widthStep + x * nChannel] = 135;
				}
				/*End round*/
			}

		}
	}
}

int EdgeDection::detectByCany(const Mat& src, Mat& dst)
{
	if (!src.data)
	{
		return 0;
	}

	int width = src.cols;
	int height = src.rows;
	int widthStep = src.step[0];
	int nChannel = src.step[1];

	dst = Mat(height, width, src.type());

	uchar* pData = (uchar*)src.data;	

	Mat smoothImage;
	gaussianBlur(src, smoothImage);

	//imshow("Blur", smoothImage);
	Mat gradient, angle;
	findGradientAndAngle(smoothImage, gradient, angle);

	//imshow("gradient", gradient);
	//imshow("angle", angle);
	//waitKey(0);
	/*Create mask 3x3 to store value of 3x3 griadian and angle*/
	vector<uchar> maskGradientIntensity;
	vector<uchar> maskAngle;
	for (int i = 0; i < 9; i++)
	{
		maskGradientIntensity.push_back(0);
		maskAngle.push_back(0);
	}

	uchar* gradientData= (uchar*)gradient.data;
	uchar* angleData = (uchar*)angle.data;

	/*Non-maximum Suppresion*/
	Mat nonMaxImage = Mat::zeros(Size(height, width), src.type());
	uchar* nonMaxData = (uchar*)nonMaxImage.data;
	for (int y = 1; y < height - 1; y++)
	{
		for (int x = 1; x < width - 1; x++)
		{
			/*Store each value to each mask*/
			maskGradientIntensity[0] = gradientData[(y - 1) * widthStep + (x-1) * nChannel];
			maskAngle[0] = angleData[(y - 1) * widthStep + (x-1) * nChannel];

			maskGradientIntensity[1] = gradientData[(y - 1) * widthStep + x * nChannel];
			maskAngle[1] = angleData[(y - 1) * widthStep + x * nChannel];

			maskGradientIntensity[2] = gradientData[(y - 1) * widthStep + (x+1) * nChannel];
			maskAngle[2] = angleData[(y - 1) * widthStep + (x+1) * nChannel];

			maskGradientIntensity[3] = gradientData[(y) * widthStep + (x-1) * nChannel];
			maskAngle[3] = angleData[(y) * widthStep + (x-1) * nChannel];

			maskGradientIntensity[4] = gradientData[(y ) * widthStep + x * nChannel];
			maskAngle[4] = angleData[(y ) * widthStep + x * nChannel];

			maskGradientIntensity[5] = gradientData[(y ) * widthStep + (x+1) * nChannel];
			maskAngle[5] = angleData[(y ) * widthStep + (x+1) * nChannel];

			maskGradientIntensity[6] = gradientData[(y + 1) * widthStep + (x-1) * nChannel];
			maskAngle[6] = angleData[(y + 1) * widthStep + (x-1) * nChannel];

			maskGradientIntensity[7] = gradientData[(y + 1) * widthStep + x * nChannel];
			maskAngle[7] = angleData[(y + 1) * widthStep + x * nChannel];

			maskGradientIntensity[8] = gradientData[(y + 1) * widthStep + (x+1) * nChannel];
			maskAngle[8] = angleData[(y + 1) * widthStep + (x+1) * nChannel];
			/*End store*/

			float currentGradian = maskGradientIntensity[4];
			float currentAngle = maskAngle[4];

			/* Non-maximum process*/
			if (currentAngle == 0)
			{
				if (currentGradian > max(maskGradientIntensity[3], maskGradientIntensity[5]))
				{
					nonMaxData[y * widthStep + x * nChannel] = 255;
				}
				else {
					gradientData[y * widthStep + x * nChannel] = 0;
				}
			}else if (currentAngle == 45)
			{
				if (currentGradian > max(maskGradientIntensity[6], maskGradientIntensity[2]))
				{
					nonMaxData[y * widthStep + x * nChannel] = 255;
				}
				else {
					gradientData[y * widthStep + x * nChannel] = 0;
				}
			}else if (currentAngle == 90)
			{
				if (currentGradian > max(maskGradientIntensity[1], maskGradientIntensity[7]))
				{
					nonMaxData[y * widthStep + x * nChannel] = 255;
				}
				else {
					gradientData[y * widthStep + x * nChannel] = 0;
				}
			}else if (currentAngle == 135)
			{
				if (currentGradian > max(maskGradientIntensity[0], maskGradientIntensity[8]))
				{
					nonMaxData[y * widthStep + x * nChannel] = 255;
				}
				else {
					gradientData[y * widthStep + x * nChannel] = 0;
				}
			}
		}
	}
	
	imshow("nonmax", nonMaxImage);

	gradientData = (uchar*)gradient.data;
	nonMaxData = (uchar*)nonMaxImage.data;
	Mat cannyMask = Mat::zeros(Size(height, width), src.type());
	uchar* cannyMaskData = (uchar*)cannyMask.data;

	uchar minVal = 256; // variable to determine the min of canny mask
	uchar maxVal = 0; // variable to determine the max of canny mask

	for (int y = 1; y < height - 1; y++)
	{
		for (int x = 1; x < width - 1; x++)
		{
			float currentNonMax, currentGradient;
			currentNonMax = nonMaxData[y * widthStep + x * nChannel];
			currentGradient = gradientData[y * widthStep + x * nChannel];

			if (currentNonMax > 0 && currentGradient > minThrehold) {
				cannyMaskData[y * widthStep + x * nChannel] = 255;
			}

			uchar currentCannyData = cannyMaskData[y * widthStep + x * nChannel];
			if (currentCannyData < minVal)
			{
				minVal = currentCannyData;
			}
			if (currentCannyData > maxVal)
			{
				maxVal = currentCannyData;
			}
		}
	}
	cannyMaskData = (uchar*)cannyMask.data;
	uchar* dstData = (uchar*)dst.data;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>((cannyMaskData[y * widthStep + x * nChannel] - minVal / (maxVal - minVal))*255);
		}
	}
	
}

vector<uchar> createEmptyVector(int size, int value)
{
	vector<uchar> data;
	for (int i = 0; i < size; i++)
	{
		data.push_back(value);
	}
	return data;
}

int gaussianBlur(const Mat& src, Mat& dst)
{
	if (!src.data)
	{
		return 0;
	}

	int width = src.cols;
	int height = src.rows;
	int widthStep = src.step[0];
	int nChannel = src.step[1];

	dst = Mat(height, width, src.type());

	uchar* pData = (uchar*)src.data;
	uchar* dstData = (uchar*)dst.data;

	Convolution blur = Convolution(5);
	blur.initGaussKernel();

	for (int y = 2; y < height-2; y++)
	{
		for (int x = 2; x < width - 2; x++)
		{
			if (nChannel == 1) {
				vector<uchar>data = createEmptyVector(blur.size(), 0);
				float value;
				
				data[0] = (uchar)pData[(y - 2) * widthStep + (x - 2) * nChannel];
				data[1] = (uchar)pData[(y - 2) * widthStep + (x - 1) * nChannel];
				data[2] = (uchar)pData[(y - 2) * widthStep + (x ) * nChannel];
				data[3] = (uchar)pData[(y - 2) * widthStep + (x + 1) * nChannel];
				data[4] = (uchar)pData[(y - 2) * widthStep + (x + 2) * nChannel];

				data[5] = (uchar)pData[(y - 1) * widthStep + (x - 2) * nChannel];
				data[6] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
				data[7] = (uchar)pData[(y - 1) * widthStep + (x)*nChannel];
				data[8] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];
				data[9] = (uchar)pData[(y - 1) * widthStep + (x + 2) * nChannel];

				data[10] = (uchar)pData[(y) * widthStep + (x - 2) * nChannel];
				data[11] = (uchar)pData[(y) * widthStep + (x - 1) * nChannel];
				data[12] = (uchar)pData[(y) * widthStep + (x)*nChannel];
				data[13] = (uchar)pData[(y) * widthStep + (x + 1) * nChannel];
				data[14] = (uchar)pData[(y) * widthStep + (x + 2) * nChannel];

				data[15] = (uchar)pData[(y +1) * widthStep + (x - 2) * nChannel];
				data[16] = (uchar)pData[(y +1) * widthStep + (x - 1) * nChannel];
				data[17] = (uchar)pData[(y +1) * widthStep + (x)*nChannel];
				data[18] = (uchar)pData[(y +1) * widthStep + (x + 1) * nChannel];
				data[19] = (uchar)pData[(y +1 ) * widthStep + (x + 2) * nChannel];

				data[20] = (uchar)pData[(y + 2) * widthStep + (x - 2) * nChannel];
				data[21] = (uchar)pData[(y + 2) * widthStep + (x - 1) * nChannel];
				data[22] = (uchar)pData[(y + 2) * widthStep + (x)*nChannel];
				data[23] = (uchar)pData[(y + 2) * widthStep + (x + 1) * nChannel];
				data[24] = (uchar)pData[(y + 2) * widthStep + (x + 2) * nChannel];

				
				value = blur.computeConvolution(data);
				dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(value);

			}
			else if (nChannel == 3)
			{
				vector<uchar> B = createEmptyVector(blur.size(), 0);

				float valueB;

				B[0] = (uchar)pData[(y - 2) * widthStep + (x - 2) * nChannel];
				B[1] = (uchar)pData[(y - 2) * widthStep + (x - 1) * nChannel];
				B[2] = (uchar)pData[(y - 2) * widthStep + (x)*nChannel];
				B[3] = (uchar)pData[(y - 2) * widthStep + (x + 1) * nChannel];
				B[4] = (uchar)pData[(y - 2) * widthStep + (x + 2) * nChannel];

				B[5] = (uchar)pData[(y - 1) * widthStep + (x - 2) * nChannel];
				B[6] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
				B[7] = (uchar)pData[(y - 1) * widthStep + (x)*nChannel];
				B[8] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];
				B[9] = (uchar)pData[(y - 1) * widthStep + (x + 2) * nChannel];

				B[10] = (uchar)pData[(y)*widthStep + (x - 2) * nChannel];
				B[11] = (uchar)pData[(y)*widthStep + (x - 1) * nChannel];
				B[12] = (uchar)pData[(y)*widthStep + (x)*nChannel];
				B[13] = (uchar)pData[(y)*widthStep + (x + 1) * nChannel];
				B[14] = (uchar)pData[(y)*widthStep + (x + 2) * nChannel];

				B[15] = (uchar)pData[(y + 1) * widthStep + (x - 2) * nChannel];
				B[16] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
				B[17] = (uchar)pData[(y + 1) * widthStep + (x)*nChannel];
				B[18] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];
				B[19] = (uchar)pData[(y + 1) * widthStep + (x + 2) * nChannel];

				B[20] = (uchar)pData[(y + 2) * widthStep + (x - 2) * nChannel];
				B[21] = (uchar)pData[(y + 2) * widthStep + (x - 1) * nChannel];
				B[22] = (uchar)pData[(y + 2) * widthStep + (x)*nChannel];
				B[23] = (uchar)pData[(y + 2) * widthStep + (x + 1) * nChannel];
				B[24] = (uchar)pData[(y + 2) * widthStep + (x + 2) * nChannel];



				vector<uchar> G = createEmptyVector(blur.size(), 0);

				float valueG;
				G[0] = (uchar)pData[(y - 2) * widthStep + (x - 2) * nChannel+1];
				G[1] = (uchar)pData[(y - 2) * widthStep + (x - 1) * nChannel+1];
				G[2] = (uchar)pData[(y - 2) * widthStep + (x)*nChannel + 1];
				G[3] = (uchar)pData[(y - 2) * widthStep + (x + 1) * nChannel + 1];
				G[4] = (uchar)pData[(y - 2) * widthStep + (x + 2) * nChannel + 1];

				G[5] = (uchar)pData[(y - 1) * widthStep + (x - 2) * nChannel + 1];
				G[6] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 1];
				G[7] = (uchar)pData[(y - 1) * widthStep + (x)*nChannel + 1];
				G[8] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 1];
				G[9] = (uchar)pData[(y - 1) * widthStep + (x + 2) * nChannel + 1];

				G[10] = (uchar)pData[(y)*widthStep + (x - 2) * nChannel + 1];
				G[11] = (uchar)pData[(y)*widthStep + (x - 1) * nChannel + 1];
				G[12] = (uchar)pData[(y)*widthStep + (x)*nChannel + 1];
				G[13] = (uchar)pData[(y)*widthStep + (x + 1) * nChannel + 1];
				G[14] = (uchar)pData[(y)*widthStep + (x + 2) * nChannel + 1];

				G[15] = (uchar)pData[(y + 1) * widthStep + (x - 2) * nChannel + 1];
				G[16] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 1];
				G[17] = (uchar)pData[(y + 1) * widthStep + (x)*nChannel + 1];
				G[18] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 1];
				G[19] = (uchar)pData[(y + 1) * widthStep + (x + 2) * nChannel + 1];

				G[20] = (uchar)pData[(y + 2) * widthStep + (x - 2) * nChannel + 1];
				G[21] = (uchar)pData[(y + 2) * widthStep + (x - 1) * nChannel + 1];
				G[22] = (uchar)pData[(y + 2) * widthStep + (x)*nChannel];
				G[23] = (uchar)pData[(y + 2) * widthStep + (x + 1) * nChannel + 1];
				G[24] = (uchar)pData[(y + 2) * widthStep + (x + 2) * nChannel + 1];



				vector<uchar> R = createEmptyVector(blur.size(), 0);

				float valueR;
				R[0] = (uchar)pData[(y - 2) * widthStep + (x - 2) * nChannel+2];
				R[1] = (uchar)pData[(y - 2) * widthStep + (x - 1) * nChannel + 2];
				R[2] = (uchar)pData[(y - 2) * widthStep + (x)*nChannel + 2];
				R[3] = (uchar)pData[(y - 2) * widthStep + (x + 1) * nChannel + 2];
				R[4] = (uchar)pData[(y - 2) * widthStep + (x + 2) * nChannel + 2];

				R[5] = (uchar)pData[(y - 1) * widthStep + (x - 2) * nChannel + 2];
				R[6] = (uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel + 2];
				R[7] = (uchar)pData[(y - 1) * widthStep + (x)*nChannel + 2];
				R[8] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel + 2];
				R[9] = (uchar)pData[(y - 1) * widthStep + (x + 2) * nChannel + 2];

				R[10] = (uchar)pData[(y)*widthStep + (x - 2) * nChannel + 2];
				R[11] = (uchar)pData[(y)*widthStep + (x - 1) * nChannel + 2];
				R[12] = (uchar)pData[(y)*widthStep + (x)*nChannel + 2];
				R[13] = (uchar)pData[(y)*widthStep + (x + 1) * nChannel + 2];
				R[14] = (uchar)pData[(y)*widthStep + (x + 2) * nChannel + 2];

				R[15] = (uchar)pData[(y + 1) * widthStep + (x - 2) * nChannel + 2];
				R[16] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel + 2];
				R[17] = (uchar)pData[(y + 1) * widthStep + (x)*nChannel + 2];
				R[18] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel + 2];
				R[19] = (uchar)pData[(y + 1) * widthStep + (x + 2) * nChannel + 2];

				R[20] = (uchar)pData[(y + 2) * widthStep + (x - 2) * nChannel + 2];
				R[21] = (uchar)pData[(y + 2) * widthStep + (x - 1) * nChannel + 2];
				R[22] = (uchar)pData[(y + 2) * widthStep + (x)*nChannel];
				R[23] = (uchar)pData[(y + 2) * widthStep + (x + 1) * nChannel + 2];
				R[24] = (uchar)pData[(y + 2) * widthStep + (x + 2) * nChannel + 2];


				valueB = blur.computeConvolution(B);
				dstData[y * widthStep + x * nChannel] = saturate_cast<uchar>(valueB);

				valueG = blur.computeConvolution(G);
				dstData[y * widthStep + x * nChannel + 1] = saturate_cast<uchar>(valueG);

				valueR = blur.computeConvolution(R);
				dstData[y * widthStep + x * nChannel + 2] = saturate_cast<uchar>(valueR);


			}
		}
	}
	
}
