#pragma once
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
#include <iostream>

class BallSearch {
public:
	BallSearch(cv::Mat image) { frame = image; search(); };
	cv::Point getBall() { return ball; };
	void search();
private:
	cv::Mat frame;
	cv::Point ball;
};