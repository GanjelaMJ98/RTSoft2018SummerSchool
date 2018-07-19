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

//TODO:
class BallTrack;		//������������ ���� � �������� ������
class DrawGoal;			//��������� ����� �� ������
class BallAtGoal;		//�������� ��������� ���� � ����� �����