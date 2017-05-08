#include "RestServer.h"

RestServer::RestServer(HTTPServer& server)
    : m_httpServer(server)
{
    Start();
}

void RestServer::Start()
{
    m_httpServer.Start();
}

void RestServer::Stop()
{
    m_httpServer.Stop();
}

void RestServer::HandleGet(HTTPRequest& acceptHTTP)
{
    //HTTPResponse response = m_handler->HandleRequest(request);
    std::stringstream respStr;
    respStr << "HTTP/1.1  200 OK\r\n" << "Content-Type: JSON" << "; charset=utf-8\r\n" << "Content-Length: 100 \r\n\r\n";

    ssize_t readSocket = write(m_httpServer.GetAcceptSocket(), respStr.str().c_str(), respStr.str().size());
    if (readSocket < 0)
    {
        std::cout << "ERROR writing to socket";
    }
    close(m_httpServer.GetSocket());
    pthread_exit(NULL);
}

void RestServer::HandleRequests()
{
    while (m_httpServer.IsWork())
    {
        HTTPRequest acceptHTTP = m_httpServer.Accept();
        if (acceptHTTP.method == "GET")
        {
            HandleGet(acceptHTTP);
        }
        else if (acceptHTTP.method == "DELETE")
        {

        }
    }
}


