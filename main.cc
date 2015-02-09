#include <raspicam/raspicam_cv.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <iostream>
#include <ctime>

#include "pi2core/rpicamera.h"
#include "pi2core/pi2serialenums.h"

#include <wiringPi.h>
#include <wiringSerial.h>

void getContours(cv::Mat const &src, cv::Mat &dest, std::vector<std::vector<cv::Point> > & contours);
bool separateR1(int R, int G, int B);
void separateRegion(cv::Mat const &src, cv::Mat &dest);

int main(){
	std::cout << "Beginning test" << std::endl;

	RPiCamera camera;

        int fd = 0;

        if ((fd = serialOpen("/dev/ttyAMA0", 9600)) < 0)
        {
                std::cout << "Unable to open serial device" << std::endl;
                return 1 ;
        }

        if (wiringPiSetup() == -1 )
        {
                std::cout << "Unable to start wiringPi" << std::endl;
        }


	while(true){
		//get image from stream
		cv::Mat cameraFrame,bwFrame,finalFrame;
		camera.getFrame(cameraFrame);

		//do a basic blur
	    	cv::medianBlur(cameraFrame, finalFrame, 5);

	    	//threshold region based on rule separateR1
	    	separateRegion(finalFrame, finalFrame);

	    	//close frame
	    	cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7), cv::Point(3,3));
	    	cv::morphologyEx(finalFrame, finalFrame, cv::MORPH_CLOSE, element);

	    	//get contours
	    	cv::cvtColor(finalFrame, finalFrame, CV_RGB2GRAY);
	    	std::vector<std::vector<cv::Point> > contours;
	    	getContours(finalFrame, cameraFrame, contours);

	    	//get bounding box and COM
	    	int com_x, com_y, bbox_y, bbox_len;
	    	if(contours.size() > 0){
			cv::Rect bBox;
			cv::Moments moment;
	    		bBox = cv::boundingRect(contours[0]);
	    		moment = cv::moments(contours[0]);
			com_x = moment.m10 / moment.m00;
			com_y = moment.m01 / moment.m00;
			bbox_y = bBox.y;
			bbox_len = bBox.height;
	    	
			cv::rectangle(cameraFrame,bBox,cv::Scalar(0, 255, 0));
	    		cv::circle(cameraFrame, cv::Point(com_x, com_y), 30, cv::Scalar(255, 0, 0), 2);
	    	}
	    	cv::Size s = cameraFrame.size();
	    	int desired_x = s.width/2;
	    	int desired_len = 200;
	    	int deadspot = 10;
	    	int l_motor = 0, r_motor = 0;
		if (bbox_len < (desired_len - deadspot)){
			if (com_x < (desired_len - deadspot)){
				l_motor = 15;
				r_motor = 40;
			}
			else if (com_x > (desired_len + deadspot)){
				l_motor = 40;
				r_motor = 15;
			}
			else {
				l_motor = 30;
				r_motor = 30;
			}
		}
		else if (bbox_len > (desired_len + deadspot)){
                        if (com_x < (desired_len - deadspot)){
                                l_motor = -40;
                                r_motor = -15;
                        }
                        else if (com_x > (desired_len + deadspot)){
                                l_motor = -15;
                                r_motor = -40;
                        }
                        else {
                                l_motor = -30;
                                r_motor = -30;
                        }
		}
		else {
                        if (com_x < (desired_len - deadspot)){
                                l_motor = -15;
                                r_motor = 15;
                        }
                        else if (com_x > (desired_len + deadspot)){
                                l_motor = 15;
                                r_motor = -15;
                        }
                        else {
                                l_motor = 0;
                                r_motor = 0;
                        }
		}



		serialPutchar(fd, pi2::SETM1SPEED);
        serialPutchar(fd, (char)l_motor);

        serialPutchar(fd, pi2::SETM2SPEED);
        serialPutchar(fd, (char)r_motor);


		//show image
		cv::imshow("cam", cameraFrame);
		if (cv::waitKey(30) >= 0) break;
	}
}

void getContours(cv::Mat const &src, cv::Mat &dest, std::vector<std::vector<cv::Point> > & contours){
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(src,contours,hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	cv::drawContours(dest,contours,-1,cv::Scalar(0, 0, 255), 3, 8, hierarchy);
}

bool separateR1(int R, int G, int B){
	double rgRatio = (double)R/(double)G;
	bool isSkin = false;
	if ( rgRatio > 1.05 && rgRatio < 4.0){
		isSkin = true;
	}
	return isSkin;
}

void separateRegion(cv::Mat const &src, cv::Mat &dest){
	dest = src.clone();

	    cv::Vec3b cwhite = cv::Vec3b::all(255);
	    cv::Vec3b cblack = cv::Vec3b::all(0);
	    for(int i = 0; i < src.rows; i++) {
	        for(int j = 0; j < src.cols; j++) {
	        	cv::Vec3b pix_bgr = src.ptr<cv::Vec3b>(i)[j];
	            int B = pix_bgr.val[0];
	            int G = pix_bgr.val[1];
	            int R = pix_bgr.val[2];
	            // apply rgb rule
	            bool a = separateR1(R,G,B);

	            //fill based on rule
	            if(a)
	            	dest.ptr<cv::Vec3b>(i)[j] = cwhite;
	            else
	            	dest.ptr<cv::Vec3b>(i)[j] = cblack;
	        }
	    }
}

