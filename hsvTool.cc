/*
* hsvTrack.cpp
* ---Detect the specific HSV value using the this GUI.
* Created on: Jul 2, 2014
* Author: Yan Liu
* Colten Noremore
* Refs: "docs.opencv.org"
*
*/

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/video/background_segm.hpp>

#include "pi2core/rpicamera.h"

using namespace std;
using namespace cv;

//initial min and max HSV filter values. These value will be changed using HSV track GUI
//This GUI will detect the HSG value that using the "Color Ball Tracking" Application
int Hue_Min = 0;
int Hue_Max = 256;
int Sat_Min = 0;
int Sat_Max = 256;
int Val_Min = 0;
int Val_Max = 256;

const int Frame_Width = 640;
const int Frame_Height = 480;
//const int Max_Dectect = 20; //set up the maximum object can be detected

const string trackingHSVApplication = "Tracking HSV Value";

void createHSVApp() {
	namedWindow(trackingHSVApplication, 0);
	char trackingHSV[50];
	sprintf(trackingHSV, "Hue_Min", Hue_Min);
	sprintf(trackingHSV, "Hue_Max", Hue_Max);
	sprintf(trackingHSV, "Sat_Min", Sat_Min);
	sprintf(trackingHSV, "Sat_Max", Sat_Max);
	sprintf(trackingHSV, "Val_Min", Val_Min);
	sprintf(trackingHSV, "Val_Max", Val_Max);

	cv::createTrackbar("Hue_Min", trackingHSVApplication, &Hue_Min, Hue_Max);
	cv::createTrackbar("Hue_Max", trackingHSVApplication, &Hue_Max, Hue_Max);
	cv::createTrackbar("Sat_Min", trackingHSVApplication, &Sat_Min, Sat_Max);
	cv::createTrackbar("Sat_MAX", trackingHSVApplication, &Sat_Max, Sat_Max);
	cv::createTrackbar("Val_MIN", trackingHSVApplication, &Val_Min, Val_Max);
	cv::createTrackbar("Val_MAX", trackingHSVApplication, &Val_Max, Val_Max);
}

void morphologicalImgProc(Mat &frame) {
	Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, Size(9, 9), Point(5, 5));
	cv::morphologyEx(frame, frame, MORPH_OPEN, element);
}

int main(int argc, char* argv[]) {
	//initialize the variables
	Mat frame;
	
	RPiCamera camera;
	
	createHSVApp();

	while (1) {
		camera.getFrame(frame);
		//change the color to HSV space
		cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);
		//get the threshold frame using the minimum and maximum HSV values
		cv::inRange(frame, Scalar(Hue_Min, Sat_Min, Val_Min), Scalar(Hue_Max, Sat_Max, Val_Max), frame);
		//using the Morphological Image processing to process the image, remove noise
		morphologicalImgProc(frame);
		//show the different kinds of frames
		cv::imshow("Camera Threshold Module", frame);

		if (cv::waitKey(30) >= 0) break;
	}
	return 0;
}
