#ifndef FRAMEQUEUE_H_
#define FRAMEQUEUE_H_ 

#include <mutex>
#include <vector>
#include <opencv/cv.h>

class FrameQueue
{
public:
	FrameQueue();
	~FrameQueue(){};

	std::vector<uchar> getFrame();
	void putFrame(std::vector<uchar> f);
	
private:
	std::vector <uchar> fq_frame;
	std::mutex fq_mutex;
};
#endif