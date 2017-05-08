#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <pthread.h>
#include <sstream>
#include <iostream>

#include "HttpHandler.h"
#include "HttpRestHandler.h"

#define HTTP_SERVER_BUFFER_SIZE 1024
#define HTTP_MAX_CONNECTIONS 10

class HTTPServer
{
public:
    HTTPServer(int port);
    void Start();
    void Stop();
    bool IsWork()const;
    HTTPRequest Accept();
    int GetSocket()const;
    int GetAcceptSocket()const;

private:
    int m_port;
    bool m_started;
    pthread_t m_acceptThreadId;
    int m_sockfd;
    int m_acceptSocket;

    void error(const char *msg);
};