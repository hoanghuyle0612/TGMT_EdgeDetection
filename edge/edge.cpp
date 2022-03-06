// edge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include"opencv2/opencv.hpp"
#include <iostream>
#include<vector>
#include"EdgeDection.h"
using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	if (strcmp(argv[2], "sobel")==0)
	{
		cout << "Sobel is processing" << endl;
		String path = argv[1];
		String direction;
		if (argv[3] != NULL)
		{
			direction = argv[3];
		}
		else {
			direction = "both";
		}
		
		Mat src = imread(path, IMREAD_ANYCOLOR);
		Mat dst;

		imshow("Source", src);
		EdgeDection detector;
		if (detector.detectBySobel(src, dst, direction))
		{
			imshow("My Sobel", dst);
		
		}
		else {
			cout << "Error" << endl;
		}
		waitKey(0);
   }else if (strcmp(argv[2], "prewit") == 0)
   {
	   cout << "Prewit is processing" << endl;
	   String path = argv[1];
	   String direction;
	   if (argv[3] != NULL)
	   {
		   direction = argv[3];
	   }
	   else {
		   direction = "both";
	   }

	   Mat src = imread(path, IMREAD_ANYCOLOR);
	   Mat dst;

	   imshow("Source", src);
	   EdgeDection detector;
	   if (detector.detectByPrewit(src, dst, direction))
	   {
		   imshow("My Prewit", dst);
		  

	   }
	   else {
		   cout << "Error" << endl;
	   }
	   waitKey(0);
   }
   else if (strcmp(argv[2], "laplace") == 0)
	{
		cout << "Laplace is processing" << endl;
		String path = argv[1];

		Mat src = imread(path, IMREAD_ANYCOLOR);
		Mat dst;

		imshow("Source", src);
		EdgeDection detector;
		if (detector.detectByLaplace(src, dst))
		{
			imshow("My Laplace", dst);
			
		}
		else {
			cout << "Error" << endl;
		}
		waitKey(0);
	}
   else if (strcmp(argv[2], "canny") == 0)
	{
		cout << "Canny is processing" << endl;
		String path = argv[1];

		//Because the result of color image or gray image is the same so i just read image in grey
		Mat src = imread(path, IMREAD_GRAYSCALE);
		Mat dst;

		imshow("Source", src);
		EdgeDection detector;
		if (detector.detectByCanny(src, dst))
		{
			imshow("My Canny", dst);			
		}
		else {
			cout << "Error" << endl;
		}
		waitKey(0);
	}
}

