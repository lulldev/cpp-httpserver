#include "HttpServer.h"


static void *invokeAccept(void *server)
{
    ((HTTPServer *) server)->Accept();
}

HTTPServer::HTTPServer(HTTPRequestHandler *hndl, int port)
    : handler(hndl)
    , m_port(port)
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

    int rc = pthread_create(&m_acceptThreadId, NULL, invokeAccept, (void *) this);
    if (rc)
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


void HTTPServer::Accept()
{
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newm_sockfd = accept(m_sockfd, (struct sockaddr *) &cli_addr, &clilen);
    int rc = pthread_create(&m_acceptThreadId, NULL, invokeAccept, (void *) this);
    if (rc)
        error("ERROR on starting new thread");

    char buffer[HTTP_SERVER_BUFFER_SIZE];
    int n;

    if (newm_sockfd < 0)
        error("ERROR on accept");
    n = read(newm_sockfd, buffer, HTTP_SERVER_BUFFER_SIZE);
    if (n < 0) error("ERROR reading from socket");
    HTTPRequest request;
    request.method = "";
    int ind = 0;
    while (buffer[ind] != ' ')
        request.method += buffer[ind++];
    ind++;
    request.path = "";
    while (buffer[ind] != ' ')
    {
        if (buffer[ind] == '%')
        {
            char *endPtr = buffer + ind + 3;
            request.path += (char) strtol(buffer + ind + 1, &endPtr, 16);
            ind += 3;
        } else
        {
            request.path += buffer[ind++];
        }
    }
    if (request.method == "POST")
    {
        bool foundStart = false;
        int numSlNs = 0;
        while (!foundStart)
        {
            if (buffer[ind] == '\n')
            {
                numSlNs++;
                if (numSlNs >= 2)
                    foundStart = true;
            } else if ((buffer[ind] != '\r') && (buffer[ind] != ' '))
                numSlNs = 0;
            ind++;
        }
        request.body = "";
        for (; ind < n; ind++)
        {
            request.body += buffer[ind];
        }
        while (n == HTTP_SERVER_BUFFER_SIZE)
        {
            ind = 0;
            n = read(newm_sockfd, buffer, HTTP_SERVER_BUFFER_SIZE);
            for (; ind < n; ind++)
            {
                request.body += buffer[ind];
            }
        }
    }
    HTTPResponse response = handler->handleRequest(request);
    std::stringstream respStr;
    respStr << "HTTP/1.1 " << response.code << " OK\r\n" << "Content-Type: " << response.contentType
            << "; charset=utf-8\r\n" << "Content-Length: " << response.body.size() << "\r\n\r\n" << response.body;
    n = write(newm_sockfd, respStr.str().c_str(), respStr.str().size());
    if (n < 0) error("ERROR writing to socket");
    close(newm_sockfd);
    pthread_exit(NULL);
}

void HTTPServer::error(const char *msg)
{
    perror(msg);
    exit(1);
}
