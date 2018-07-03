#include "stdafx.h"
#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
using namespace cv;

int XX = NULL;
int YY = NULL;


void drawTarget(IplImage* img, int x, int y, int radius)
{
	cvCircle(img, cvPoint(x, y), radius, CV_RGB(250, 0, 0), 1, 8);
	cvLine(img, cvPoint(x - radius / 2, y - radius / 2), cvPoint(x + radius / 2, y + radius / 2), CV_RGB(250, 0, 0), 1, 8);
	cvLine(img, cvPoint(x - radius / 2, y + radius / 2), cvPoint(x + radius / 2, y - radius / 2), CV_RGB(250, 0, 0), 1, 8);
}


void myMouseCallback(int event, int x, int y, int flags, void* param)
{
	IplImage* img = (IplImage *) param;

	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		break;

	case CV_EVENT_LBUTTONDOWN:
		XX = x;
		YY = y;
		printf("%d x %d\n", x, y);
		drawTarget(img, x, y, 10);
		break;

	case CV_EVENT_LBUTTONUP:
		break;
	}
}

int main()
{
	VideoCapture cap("EspRus.MP4"); 
	if (!cap.isOpened()) return -1;

	double fps = cap.get(CV_CAP_PROP_FPS);
	std::cout << "Frame per seconds : " << fps << std::endl;
	namedWindow("Goalkeeper", CV_WINDOW_AUTOSIZE);
	
	Mat frame;

	while (1) {
		Mat frame;
		bool bSuccess = cap.read(frame); 
		if (!bSuccess) {
			std::cout << "Cannot read the frame from video file" << std::endl;
			break;
		}

		imshow("Goalkeeper", frame);

		IplImage* img = new IplImage(frame);
		cvSetMouseCallback("Goalkeeper", myMouseCallback, img);
		if (XX != NULL && YY != NULL) {
			drawTarget(img, XX, YY, 10);
			cvShowImage("Goalkeeper", img);
		}


		if (waitKey(30) == 27) {
			break;
		}
	}
}
