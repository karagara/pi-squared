/*
 * RPiCamera.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: Colten
 */

#include "rpicamera.h"
#include <raspicam/raspicam_cv.h>
#include <opencv/cv.h>
#include <iostream>

RPiCamera::RPiCamera() {
	this->vCapture = new raspicam::RaspiCam_Cv();
	this->vCapture->set( CV_CAP_PROP_FRAME_WIDTH, 320 );
	this->vCapture->set( CV_CAP_PROP_FRAME_HEIGHT, 240 ); 
	this->vCapture->open();
}

RPiCamera::~RPiCamera() {
	// TODO Auto-generated destructor stub
}

void RPiCamera::getFrame(cv::Mat & image){
	this->vCapture->grab();
	this->vCapture->retrieve(image);
}
