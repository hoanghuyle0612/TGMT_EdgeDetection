// edge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include"opencv2/opencv.hpp"
#include <iostream>
#include<vector>
#include"EdgeDection.h"
using namespace cv;
using namespace std;


int main()
{
    std::cout << "Hello World!\n";
    Mat source = imread("download.png", IMREAD_GRAYSCALE);
    Mat source1 = imread("download.png", IMREAD_ANYCOLOR);
   
    imshow("src", source);
    Mat dst,cvSobel, absCvSobel;
    EdgeDection detector;
    detector.detectByLaplace(source, dst);
    

    imshow("dst", dst);
    //Sobel(source, cvSobel, CV_16S,1,1);
    //Laplacian(source1, cvSobel, CV_16S, 1, 0);
    //convertScaleAbs(cvSobel, absCvSobel);
    //imshow("cvSobel", absCvSobel);
    waitKey(0);
}

