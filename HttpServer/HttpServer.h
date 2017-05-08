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

#define HTTP_SERVER_BUFFER_SIZE 1024
#define HTTP_MAX_CONNECTIONS 10

struct HTTPRequest
{
    std::string path;
    std::string method;
    std::string body;
};

struct HTTPResponse
{
    int code;
    std::string body;
    std::string contentType;
};

// todo: this is rest class
class HTTPRequestHandler
{
public:
    virtual HTTPResponse handleRequest(HTTPRequest request) = 0;
};

class HTTPServer
{
public:
    HTTPServer(HTTPRequestHandler *hndl, int port);
    void Start();
    void Stop();
    void Accept();

private:
    HTTPRequestHandler * handler;
    int m_port;
    bool m_started;
    pthread_t m_acceptThreadId;
    int m_sockfd;

    void error(const char *msg);
};