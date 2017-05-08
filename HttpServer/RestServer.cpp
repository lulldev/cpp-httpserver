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

void RestServer::HandleRequests()
{
    while (m_httpServer.IsWork())
    {
        m_httpServer.Accept();
        std::cout << "handle" << std::endl;
    }
}

