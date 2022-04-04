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
		Mat src1 = imread(path, IMREAD_ANYCOLOR);
		Mat dst;

		imshow("Source", src);
		EdgeDection detector;
		if (detector.detectBySobel(src, dst, direction))
		{
			imshow("My Sobel", dst);
			
			// opencv 
			Mat img, img_gray, grad;
			//GaussianBlur(src1, img, Size(3, 3), 0, 0, BORDER_DEFAULT);
			// Convert the image to grayscale
			//cvtColor(img, img_gray, COLOR_BGR2GRAY);
			Mat grad_x, grad_y, grad_xy;
			Mat abs_grad_x, abs_grad_y, abs_grad_xy;
			//Sobel(src1, grad_x, CV_16S, 1, 0);
			//Sobel(src1, grad_y, CV_16S, 0, 1);
			Sobel(src1, grad_xy, CV_16S, 1, 1);
			// converting back to CV_8U
			//convertScaleAbs(grad_x, abs_grad_x);
			//convertScaleAbs(grad_y, abs_grad_y);
			convertScaleAbs(grad_xy, abs_grad_xy);
			
			//imshow("opencv", abs_grad_x);
			//imshow("opencv", abs_grad_y);
			imshow("opencv", abs_grad_xy);
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
	   Mat src1 = imread(path, IMREAD_ANYCOLOR);
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
		Mat src1 = imread(path, IMREAD_ANYCOLOR);
		Mat dst;

		imshow("Source", src);
		EdgeDection detector;
		if (detector.detectByLaplace(src, dst))
		{
			imshow("My Laplace", dst);
			
			// opencv 
			Mat abs_dst, dst_cv;
			Laplacian(src1, dst_cv, CV_16S);
			// converting back to CV_8U
			convertScaleAbs(dst, abs_dst);
			imshow("opencv", abs_dst);
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

