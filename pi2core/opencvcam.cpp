/*
 * OpenCVCam.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: Colten
 */

#include "opencvcam.h"

OpenCVCam::OpenCVCam() {
	this->vCapture = new cv::VideoCapture(0);
}

OpenCVCam::~OpenCVCam() {
	// TODO Auto-generated destructor stub
}

cv::Mat OpenCVCam::getFrame(){
	cv::Mat img;
	vCapture->read(img);
	return img;
}
