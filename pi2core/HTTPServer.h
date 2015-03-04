#ifndef HELLO_H_
#define HELLO_H_

#include <cppcms/application.h>
#include <cppcms/service.h>

class FrameQueue;
class CommandQueue;

class HTTPServer : public cppcms::application {
public:
    HTTPServer(cppcms::service &srv, FrameQueue* fq, CommandQueue* cq);
    // void index();
    void stream();
    void placecom(std::string msg);
private:
    FrameQueue* srv_fq;
    CommandQueue* srv_cq;
};

#endif
