#include "stdafx.h"
#include "goalsearch.h"
#include "ballsearch.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("Image.jpg", 1);
	GoalSearch Goal(src);
	vector<Point> angles = Goal.getAngles();
	cout << angles << endl;
	BallSearch Ball(src);
	Point Ball_point = Ball.getBall();
	cout << Ball_point << endl;
	
    return 0;
}

