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

vector<uchar> createEmptyVector(int size, int value)
{
	vector<uchar> data;
	for (int i = 0; i < size; i++)
	{
		data.push_back(value);
	}
	return data;
}
