#ifndef HTTPSERVERMANAGER_H_
#define HTTPSERVERMANAGER_H_

class FrameQueue;
class CommandQueue;

class HTTPServerManager
{
public:
	HTTPServerManager(){};
	~HTTPServerManager(){};

	void run(int argc, char ** argv, FrameQueue* fq, CommandQueue* cq);
};

#endif

