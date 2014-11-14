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

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main( int argc, char** argv )
{
	if ( argc != 2 )
	{
		std::cout << "usage: testExec <Image Path>" << std::endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], 1);
	
	if ( !image.data )
	{
		std::cout << "No Image Data" << std::endl;
		return -1;
	}
	namedWindow("MyWindow", WINDOW_AUTOSIZE);
	imshow("MyWindow", image);

	waitKey(0);

	return 0;
}
