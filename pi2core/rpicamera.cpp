/*
 * RPiCamera.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: Colten
 */

#include "rpicamera.h"

RPiCamera::RPiCamera() {
	this->vCapture = new raspicam::RaspiCam_Cv;
	this->vCapture->set(cv::CAP_PROP_FORMAT, CV_8UC1 );
}

RPiCamera::~RPiCamera() {
	// TODO Auto-generated destructor stub
}

cv::Mat RPiCamera::getFrame(){
	cv::Mat img;
	return img;
}
