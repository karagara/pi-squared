#include "RemoteAlg.h"

#include <opencv/cv.h>
#include <iostream>

#include "pi2core/opencvcam.h"
#include "pi2core/CommandQueue.h"
#include "pi2core/FrameQueue.h"

int RemoteAlg::pi2Main(){
	// raspicam::RaspiCam_Cv camera;
	OpenCVCam camera;

	while(true){
		//Create variables
		cv::Mat frame;

		//Load image
		camera.getFrame(frame);

		//Handle Msg
		Command c = this->commandQueue->getCommand();

		//place img to be read
		std::vector<uchar> buffer;
		cv::imencode(".jpg", frame, buffer);
		this->frameQueue->putFrame(buffer);
	}
	return 0;
}