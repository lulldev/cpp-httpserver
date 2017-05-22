class HTTPRequest
{
public:
    std::string path;
    std::string method;
    std::string body;
};

class HTTPResponse
{
public:
    int code;
    std::string body;
    std::string contentType;
};

class HTTPRequestHandler
{
public:
    virtual HTTPResponse HandleRequest(HTTPRequest request) = 0;
};