#include "SocketServerManager.h"
#include "tcpstream.h"
#include "tcpacceptor.h"
#include <iostream>

int SocketServerManager::run(){
    TCPStream* stream = NULL;
    TCPAcceptor* acceptor = NULL;
    acceptor = new TCPAcceptor(8081);
    if (acceptor->start() == 0) {
        while (1) {
            stream = acceptor->accept();
            if (stream != NULL) {
                ssize_t len;
                char line[256];
                while ((len = stream->receive(line, sizeof(line))) > 0) {
                    line[len] = 0;
                    std::cout << line << std::endl;
                    stream->send(line, len);
                }
                delete stream;
            }
        }
    }
}