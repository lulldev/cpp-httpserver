class HTTPRequestRESTHandler : public HTTPRequestHandler
{
public:
    HTTPResponse HandleRequest(HTTPRequest request)
    {
        HTTPResponse response;
        if (request.method == "GET")
        {
            response = GET(request);
        }
        else if (request.method == "POST")
        {
            response = POST(request);
        }
        else if (request.method == "PUT")
        {
            response = PUT(request);
        }
        if (request.method == "DELETE")
        {
            response = DELETE(request);
        }

        return response;
    }

    virtual HTTPResponse GET(HTTPRequest request) = 0;
    virtual HTTPResponse POST(HTTPRequest request) = 0;
    virtual HTTPResponse PUT(HTTPRequest request) = 0;
    virtual HTTPResponse DELETE(HTTPRequest request) = 0;
};