#include "stdafx.h"
#include "goalsearch.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

GoalSearch::GoalSearch(Mat image) {
	frame = image;
	angles = { Point(1,1), Point(1,2), Point(1,3), Point(2,1) };
}