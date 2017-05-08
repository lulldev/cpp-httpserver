#include "HttpServer.h"

//using namespace std;

static void* InvokeAccept(void* server)
{
    ((HTTPServer*)server)->Accept();
}

HTTPServer::HTTPServer(int port)
    : m_port(port)
    , m_started(false)
{
}

void HTTPServer::Start()
{
    if (m_started)
    {
        return;
    }
    
    m_started = true;
    struct sockaddr_in servAddr;
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (m_sockfd < 0)
    {
        error("ERROR opening socket");
    }

    bzero((char *) &servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(m_port);

    if (bind(m_sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    {
        error("ERROR on binding");
    }

    listen(m_sockfd, HTTP_MAX_CONNECTIONS);

    int thread = pthread_create(&m_acceptThreadId, NULL, InvokeAccept, (void *) this);
    if (thread)
    {
        error("ERROR on starting new thread");
    }
}

void HTTPServer::Stop()
{
    if (!m_started)
    {
        return;
    }
    m_started = false;
    close(m_sockfd);
    pthread_detach(m_acceptThreadId);
}


HTTPRequest HTTPServer::Accept()
{
    struct sockaddr_in clientAddr;
    socklen_t sockSize = sizeof(clientAddr);
    int acceptSocket = accept(m_sockfd, (struct sockaddr *) &clientAddr, &sockSize);
    m_acceptSocket = acceptSocket;
    int thread = pthread_create(&m_acceptThreadId, NULL, InvokeAccept, (void *) this);
    if (thread)
    {
        error("ERROR on starting new thread");
    }

    char buffer[HTTP_SERVER_BUFFER_SIZE];
    ssize_t readSocket;

    if (acceptSocket < 0)
    {
        error("ERROR on accept");
    }

    readSocket = read(acceptSocket, buffer, HTTP_SERVER_BUFFER_SIZE);
    if (readSocket < 0)
    {
        error("ERROR reading from socket");
    }

    HTTPRequest request;
    request.method = "";
    int responseStrCounter = 0;
    while (buffer[responseStrCounter] != ' ')
    {
        request.method += buffer[responseStrCounter++];
    }

    responseStrCounter++;
    request.path = "";

    while (buffer[responseStrCounter] != ' ')
    {
        if (buffer[responseStrCounter] == '%')
        {
            char *endPtr = buffer + responseStrCounter + 3;
            request.path += (char) strtol(buffer + responseStrCounter + 1, &endPtr, 16);
            responseStrCounter += 3;
        } else
        {
            request.path += buffer[responseStrCounter++];
        }
    }

    close(acceptSocket);
//    pthread_exit(NULL);
    return request;

/*    HTTPResponse response = m_handler->HandleRequest(request);
    std::stringstream respStr;
    respStr << "HTTP/1.1 " << response.code << " OK\r\n" << "Content-Type: " << response.contentType
            << "; charset=utf-8\r\n" << "Content-Length: " << response.body.size() << "\r\n\r\n" << response.body;
    readSocket = write(acceptSocket, respStr.str().c_str(), respStr.str().size());
    if (readSocket < 0) error("ERROR writing to socket");
    close(acceptSocket);
    pthread_exit(NULL);*/
}

int HTTPServer::GetSocket()const
{
    return m_sockfd;
}

int HTTPServer::GetAcceptSocket()const
{
    return m_acceptSocket;
}


bool HTTPServer::IsWork()const
{
    return m_started;
}

void HTTPServer::error(const char *msg)
{
    perror(msg);
    exit(1);
}
