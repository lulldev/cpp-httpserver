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

#include "Handlers/HttpHandler.h"
#include "Handlers/RestHandler.h"

#define HTTP_SERVER_BUFFER_SIZE 1024
#define HTTP_MAX_CONNECTIONS 10

class HTTPServer
{
public:
    HTTPServer(HTTPRequestHandler *hndl, int port);
    void Start();
    void Stop();
    void AsyncAccept();
private:
    HTTPRequestHandler *m_handler;
    int m_port;
    bool m_isStarted;
    pthread_t m_acceptThreadId;
    int m_sockfd;
    void ValidatePort(size_t port);

    void error(const char *msg);
};
