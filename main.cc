#include <iostream>
#include <thread>

#include "pi2core/ColorBallAlgorithm.h"
#include "pi2core/AlgorithmInterface.h"
#include "pi2core/TestAlg.h"

#include "pi2core/SocketServerManager.h"
#include "pi2core/CommandQueue.h"
#include "pi2core/FrameQueue.h"
#include "pi2core/pi2serialenums.h"

int main(int argc,char ** argv){

	SocketServerManager socSrv;
	std::thread socThread(&SocketServerManager::run, &socSrv);	

	socThread.join();

	return 0;
}
