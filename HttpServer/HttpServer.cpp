#include "HttpServer.h"

HTTPServer::HTTPServer(HTTPRequestHandler *hndl, int port)
    : m_handler(hndl)
    , m_port(port)
    , m_isStarted(false)
{
    ValidatePort(m_port);
}

void HTTPServer::ValidatePort(size_t port)
{
    if ((port < 0 && port > 65536))
    {
        throw std::invalid_argument("Port must be [1-65536]");
    }
}

static void *InvokeAsyncAccept(void *server)
{
    ((HTTPServer *) server)->AsyncAccept();
}

void HTTPServer::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void HTTPServer::Start()
{
    if (m_isStarted)
    {
        return;
    }

    m_isStarted = true;
    struct sockaddr_in serv_addr;
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockfd < 0)
    {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(m_port);

    if (bind(m_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }

    listen(m_sockfd, HTTP_MAX_CONNECTIONS);

    int rc = pthread_create(&m_acceptThreadId, NULL, InvokeAsyncAccept, (void *) this);
    if (rc)
    {
        error("ERROR on starting new thread");
    }
}

void HTTPServer::Stop()
{
    if (!m_isStarted)
    {
        return;
    }

    m_isStarted = false;
    close(m_sockfd);
    pthread_detach(m_acceptThreadId);
}

void HTTPServer::AsyncAccept()
{
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(m_sockfd, (struct sockaddr *) &cli_addr, &clilen);
    int rc = pthread_create(&m_acceptThreadId, NULL, InvokeAsyncAccept, (void *) this);

    if (rc)
    {
        error("ERROR on starting new thread");
    }

    char buffer[HTTP_SERVER_BUFFER_SIZE];

    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }

    ssize_t n;
    n = read(newsockfd, buffer, HTTP_SERVER_BUFFER_SIZE);
    if (n < 0)
    {
        error("ERROR reading from socket");
    }

    HTTPRequest request;
    request.method = "";
    int ind = 0;
    while (buffer[ind] != ' ')
    {
        request.method += buffer[ind++];
    }
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

    request.body = "";

    HTTPResponse response = m_handler->HandleRequest(request);
    std::stringstream respStr;
    respStr << "HTTP/1.1 " << response.code << " OK\r\n" << "Content-Type: " << response.contentType
            << "; charset=utf-8\r\n" << "Content-Length: " << response.body.size() << "\r\n\r\n" << response.body
            << "\r\n\r\n" << "Access-Control-Allow-Origin: *;";
    n = write(newsockfd, respStr.str().c_str(), respStr.str().size());
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    pthread_exit(NULL);
}
