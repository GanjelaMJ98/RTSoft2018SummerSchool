// Vorota.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace cv;
using namespace std;


vector<vector<Point> > contours;
vector<vector<Point> > contours0;
vector<Vec4i> hierarchy;
const int w = 500;
int levels = 3;


int main(int argc, char** argv)
{
	Mat src, src_gray;
	Mat grad;

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	src = imread("ball.jpg", IMREAD_COLOR); // Load an image
	if (src.empty())
	{
		return -1;
	}
	GaussianBlur(src, src, Size(15, 15), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);


	Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
	std::vector<Vec4f> lines_std;

	Mat closed;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(grad, closed, MORPH_CLOSE, kernel);


	Mat LSD_im(600, 800, CV_8UC3, Scalar(255, 255, 255));
	ls->detect(grad, lines_std); // Detect the lines
	ls->drawSegments(LSD_im, lines_std);


	findContours(grad, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//contours.resize(contours0.size());
	//for (size_t k = 0; k < contours0.size(); k++)
		//approxPolyDP(Mat(contours0[k]), contours[k], 3, true);
	RNG rng(12345);
	Mat drawing = Mat::zeros(grad.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}
	imshow("Contours", drawing);
	//Mat closed;
	//Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3));
	//morphologyEx(grad, closed, MORPH_CLOSE, kernel);

	//imwrite("closed.jpg", closed);
	//cv::resize(src, src, cv::Size(800, 600));
	namedWindow("LSD", CV_WINDOW_AUTOSIZE);
	imshow("LSD", LSD_im); //show the frame in "MyVideo" window
	imshow("ker", closed);

	imshow("air", grad);
	waitKey(0);
	return 0;
}
