#include "FrameQueue.h"
#include <opencv/cv.h>

FrameQueue::FrameQueue(){
}

void FrameQueue::putFrame(std::vector<uchar> frame){
	this->fq_mutex.lock();
	this->fq_frame = frame;
	this->fq_mutex.unlock();
}

std::vector<uchar> FrameQueue::getFrame(){
	this->fq_mutex.lock();
	std::vector<uchar> f = this->fq_frame;
	this->fq_mutex.unlock();

	return f;
}