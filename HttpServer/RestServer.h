#include "HttpServer.h"

class RestServer
{
public:
    RestServer(HTTPServer& server);
    void Start();
    void Stop();
    void HandleRequests();
private:
    HTTPServer m_httpServer;
    void HandleGet(HTTPRequest& acceptHTTP);
    //    void HandleDelete();
};
