#include "HTTPServer.h"
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/http_response.h>
#include <cppcms/application.h>
#include <iostream>
#include <vector>
#include <opencv/cv.h>

#include "FrameQueue.h"
#include "CommandQueue.h"
#include "JSONService.h"

HTTPServer::HTTPServer(cppcms::service &srv, FrameQueue* fq, CommandQueue* cq): cppcms::application(srv) {
    this->srv_fq = fq;
    this->srv_cq = cq;
    
    attach(new JSONService(srv, cq), 
        "/command", "/command{1}",
        "/command(/(.*))?", 1);

    dispatcher().assign("/stream",&HTTPServer::stream,this);
    mapper().assign("stream","/stream");

    dispatcher().assign("/placecom/((.*))?", &HTTPServer::placecom, this, 1);
    mapper().assign("placecom", "/placecom/{1}");

    mapper().root("/");
}

void HTTPServer::stream(){
        std::vector<uchar> frame = srv_fq->getFrame();
        response().set_content_header("image/jpeg");
        for (int i = 0; i < frame.size(); ++i)
        {
            response().out()<< frame[i];
        }
}

void HTTPServer::placecom(std::string msg){
    // std::cout << msg << std::endl;
    Command c;
    c.value = 0;
    c.type = msg;
    this->srv_cq->putCommand(c);
    // response().out() << msg;
}


// Content-Type: multipart/x-mixed-replace; boundary=frame