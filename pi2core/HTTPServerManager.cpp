#include "HTTPServerManager.h"

#include <cppcms/applications_pool.h>
#include <cppcms/service.h>

#include "HTTPServer.h"

void HTTPServerManager::run(int argc, char ** argv, FrameQueue* fq, CommandQueue* cq){
	try {
		cppcms::service srv(argc,argv);
		srv.applications_pool().mount(cppcms::applications_factory<HTTPServer>(fq, cq));
		srv.run();
	}
		catch(std::exception const &e) {
		std::cerr<<e.what()<<std::endl;
	}
}