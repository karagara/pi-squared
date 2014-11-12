/*
 * visionTest.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: Colten
 *
 *  Moved the old test methods out from the main file to here. Nice
 *  place to start and see if all the opencv libraries are linked
 *  properly
 */

/*
 * Module one, testing without a webcam
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{

	Mat img = imread("../lib/test/lenna.png", CV_LOAD_IMAGE_COLOR);

	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	imshow("MyWindow", img);

	waitKey(0);
	return 0;
}
