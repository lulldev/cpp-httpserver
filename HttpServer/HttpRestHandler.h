class HTTPRestRequestHandler: public HTTPRequestHandler
{
public:
    HTTPResponse GET (HTTPRequest request);
    HTTPResponse DELETE (HTTPRequest request);
};