#include <iostream>

struct HTTPRequest
{
    std::string path;
    std::string method;
    std::string data = "";
};

struct HTTPResponse
{
    int code;
    std::string body;
    std::string contentType;
};

class HTTPRequestHandler
{
public:
    virtual HTTPResponse GET (HTTPRequest request);
    virtual HTTPResponse DELETE (HTTPRequest request);
//    virtual HTTPResponse POST (HTTPRequest request);
//    virtual HTTPResponse PUT (HTTPRequest request);
};