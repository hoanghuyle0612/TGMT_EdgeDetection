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
    Mat source1 = imread("download.png", IMREAD_GRAYSCALE);
   
    //imshow("src", source);
    Mat dst,cvSobel, absCvSobel;
    EdgeDection detector;
    detector.detectByCanny(source, dst);
    
    

    imshow("dst", dst);
    //Sobel(source, cvSobel, CV_16S,1,1);
    //Laplacian(source1, cvSobel, CV_16S, 1, 0);
    //convertScaleAbs(cvSobel, absCvSobel);
    //imshow("cvSobel", absCvSobel);
    //GaussianBlur(source1, cvSobel,Size(5,5),0,0);
    
    Canny(source1, cvSobel, 100, 200);
    imshow("CVGauss", cvSobel);
    waitKey(0);
}

