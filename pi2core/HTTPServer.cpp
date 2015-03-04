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
#include "pi2serialenums.h"

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
    Command c;
    if (msg == "up") {
        c.type = pi2::FORWARD;
        c.m1speed = 40;
        c.m2speed = 40;
    } else if (msg == "back") {
        c.type = pi2::BACK;
        c.m1speed = -40;
        c.m2speed = -40;
    } else if (msg == "right") {
        c.type = pi2::RIGHT;
        c.m1speed = 40;
        c.m2speed = 0;        
    } else if (msg == "left") {
        c.type = pi2::LEFT;
        c.m1speed = 0;
        c.m2speed = 40;        
    } else {
        c.type = pi2::NOCOMMAND;
        c.m1speed = 0;
        c.m2speed = 0;        
    }
    this->srv_cq->putCommand(c);
}


// Content-Type: multipart/x-mixed-replace; boundary=frame