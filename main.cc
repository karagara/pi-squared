#include <iostream>
#include <thread>

#include "pi2core/ColorBallAlgorithm.h"
#include "pi2core/AlgorithmInterface.h"
#include "pi2core/TestAlg.h"

// #include <cppcms/applications_pool.h>
// #include <cppcms/service.h>

#include "pi2core/HTTPServer.h"
#include "pi2core/SocketServerManager.h"
#include "pi2core/CommandQueue.h"
#include "pi2core/FrameQueue.h"
#include "pi2core/pi2serialenums.h"


class HTTPServerManager
{
public:
	HTTPServerManager(){};
	~HTTPServerManager(){};

	void run(int argc,char ** argv, FrameQueue* fq){
		try {
			cppcms::service srv(argc,argv);
			srv.applications_pool().mount(cppcms::applications_factory<HTTPServer>(fq));
			srv.run();
		}
			catch(std::exception const &e) {
			std::cerr<<e.what()<<std::endl;
		}
	}
	
};

int main(int argc,char ** argv){
	// try {
	// 	cppcms::service srv(argc,argv);
	// 	srv.applications_pool().mount(cppcms::applications_factory<HTTPServer>(10));
	// 	srv.run();
	// }
	// 	catch(std::exception const &e) {
	// 	std::cerr<<e.what()<<std::endl;
	// }



	// FrameQueue* fq = new FrameQueue();
	// CommandQueue* cq = new CommandQueue(); 

	// std::cout << "Creating Algorithm Context" << std::endl;
	// // AlgorithmInterface* alg = new ColorBallAlgorithm();
	// ColorBallAlgorithm alg;

	// std::cout << "Running Algorithm" << std::endl;
	// std::thread algThread(&ColorBallAlgorithm::testMain, &alg, fq, cq);

	// HTTPServerManager httpSrv;
	// std::thread httpThread(&HTTPServerManager::run, &httpSrv, argc, argv, fq);
	SocketServerManager socSrv;
	std::thread socThread(&SocketServerManager::run, &socSrv);	
	// algThread.join();
	// httpThread.join();
	socThread.join();

	return 0;
}
