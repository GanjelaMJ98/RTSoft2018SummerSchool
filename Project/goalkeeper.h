#pragma once

#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
#include <iostream>

class GoalSearch {
public:
	GoalSearch(cv::Mat image);
	std::vector<cv::Point> getAngles() { return angles; };
private:
	cv::Mat frame;
	std::vector<cv::Point> angles;
};

class BallSearch {
public:
	BallSearch(cv::Mat image) { frame = image; search(); };
	cv::Point getBall() { return ball; };
	void search();
private:
	cv::Mat frame;
	cv::Point ball;

};


//TODO:
class BallTrack;		//отслеживание мяча в цифровом потоке
class DrawGoal;			//отрисовка ворот по точкам
class BallAtGoal;		//проверка попадания мяча в створ ворот
