#include "EdgeDection.h"
#include"Convolution.h"
int EdgeDection::detectBySobel(const Mat& src, Mat& dst, string direction)
{
	if (direction=="x"||direction=="X")
	{
		if (!src.data)
		{
			return 0;
		}
		Convolution con;
		con.initSobelXKernel();
		int width = src.cols;
		int height = src.rows;
		int widthStep = src.step[0];
		int nChannel = src.step[1];
		dst = Mat(height, width, CV_8UC1);
		
		uchar* pData = (uchar*)src.data;
		uchar* dstData = (uchar*)dst.data;
		for (int y = 1; y < height-1; y++)
		{
			for (int x = 1; x < width-1; x++)
			{
				vector<uchar>data = createEmptyVector(con.size(), 0);
				uchar value;
				data[0]=(uchar)pData[(y - 1) * widthStep + (x - 1) * nChannel];
				data[1] = (uchar)pData[(y - 1) * widthStep + x * nChannel];
				data[2] = (uchar)pData[(y - 1) * widthStep + (x + 1) * nChannel];

				data[3] = (uchar)pData[y * widthStep + (x - 1) * nChannel];
				data[4] = (uchar)pData[y * widthStep + x * nChannel];
				data[5] = (uchar)pData[y * widthStep + (x + 1) * nChannel];

				data[6] = (uchar)pData[(y + 1) * widthStep + (x - 1) * nChannel];
				data[7] = (uchar)pData[(y + 1) * widthStep + x * nChannel];
				data[8] = (uchar)pData[(y + 1) * widthStep + (x + 1) * nChannel];

				value=con.computeConvolution(data);
				dstData[y * widthStep + x * nChannel] = value;
			}
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
