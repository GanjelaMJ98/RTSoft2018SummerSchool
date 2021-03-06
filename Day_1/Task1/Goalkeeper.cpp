#include "stdafx.h"
#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
using namespace cv;

int XX = NULL;
int YY = NULL;
Mat FRAME;
int thresh = 100;
int max_thresh = 255;

void drawTarget(Mat img, int x, int y, int radius)
{
	drawMarker(img, Point(x, y), CV_RGB(250, 0, 0), MARKER_DIAMOND, 10, 10);
	//cvLine(img, cvPoint(x - radius / 2, y - radius / 2), cvPoint(x + radius / 2, y + radius / 2), CV_RGB(250, 0, 0), 1, 8);
	//cvLine(img, cvPoint(x - radius / 2, y + radius / 2), cvPoint(x + radius / 2, y - radius / 2), CV_RGB(250, 0, 0), 1, 8);
}


void myMouseCallback(int event, int x, int y, int, void*)
{
	//IplImage* img = (IplImage *) param;

	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		break;

	case CV_EVENT_LBUTTONDOWN:
		XX = x;
		YY = y;
		printf("%d x %d\n", x, y);
		drawTarget(FRAME, x, y, 10);
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
		Mat frame,frame_gray;
		bool bSuccess = cap.read(frame); 
		if (!bSuccess) {
			std::cout << "Cannot read the frame from video file" << std::endl;
			break;
		}
		/*cvtColor(frame, frame_gray, CV_BGR2GRAY);
		int scale = 1;
		int delta = 0;
		int ddepth = CV_16S;
		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y, grad;
		//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
		Sobel(frame_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
		Sobel(frame_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
		Mat canny_output;
		Canny(grad, canny_output, thresh, thresh * 2, 3);
		imshow("Goalkeeper", grad);*/
		imshow("Goalkeeper", frame);

		//IplImage* img = new IplImage(frame);
		//cvSetMouseCallback("Goalkeeper", myMouseCallback);

		setMouseCallback("Goalkeeper", myMouseCallback);
		FRAME = frame;
		if (XX != NULL && YY != NULL) {
			drawTarget(FRAME, XX, YY, 10);
			//cvShowImage("Goalkeeper", FRAME);
			imshow("Goalkeeper", FRAME);
		}


		if (waitKey(30) == 27) {
			break;
		}
	}
}
