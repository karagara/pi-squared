#include <iostream>
#include <thread>

#include "pi2core/ColorBallAlgorithm.h"
#include "pi2core/AlgorithmInterface.h"
#include "pi2core/TestAlg.h"
#include "pi2core/RemoteAlg.h"

#include <cppcms/applications_pool.h>
#include <cppcms/service.h>

#include "pi2core/HTTPServer.h"
#include "pi2core/SocketServerManager.h"
#include "pi2core/CommandQueue.h"
#include "pi2core/FrameQueue.h"
#include "pi2core/pi2serialenums.h"
#include "pi2core/HTTPServerManager.h"


int main(int argc,char ** argv){
	//Setup Shared Vars
	FrameQueue* fq = new FrameQueue();
	CommandQueue* cq = new CommandQueue(); 
	
	//Create current algorithm
	std::cout << "Creating Algorithm Context" << std::endl;
	RemoteAlg alg(fq, cq);

	//Create and run threads
	std::cout << "Running Algorithm" << std::endl;
	std::thread algThread(&RemoteAlg::pi2Main, &alg);

	std::cout << "Running HTTP Server" << std::endl;
	HTTPServerManager httpSrv;
	std::thread httpThread(&HTTPServerManager::run, &httpSrv, argc, argv, fq, cq);

	std::cout << "Running Socket Server" << std::endl;
	SocketServerManager socSrv;
	std::thread socThread(&SocketServerManager::run, &socSrv);
	
	//Wait for execution to finish
	algThread.join();
	httpThread.join();
	socThread.join();
    
	return 0;
}
