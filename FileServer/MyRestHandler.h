#include "FileHelper/FileHelper.h"

#include <set>
#include <string>
#include "../lib/json.hpp"

using json = nlohmann::json;
using namespace std;

static const std::string JSON_CONTENT_TYPE = "application/json";
static const size_t HTTP_SUCCESS_CODE = 200;
static const size_t HTTP_NOT_FOUND_CODE = 404;
static const size_t HTTP_CRASH_CODE = 500;

class MyRestHandler : public HTTPRequestRESTHandler
{
public:

    HTTPResponse GET(HTTPRequest request)
    {
        response.code = HTTP_SUCCESS_CODE;
        response.contentType = JSON_CONTENT_TYPE;

        string targetRootDir;

        if (request.path == "/")
        {
            targetRootDir = m_serverRootDir;
        }
        else
        {
            targetRootDir = m_serverRootDir + request.path;
        }

        try
        {
            FileHelper fileHelper(targetRootDir);
            set<string> contentSet = fileHelper.GetDirectoryContent(targetRootDir);
            std::set<string>::iterator it;
            json resultDirectoryContentArr;

            size_t i = 0;
            for (it = contentSet.begin(); it != contentSet.end(); ++it, i++)
            {
                resultDirectoryContentArr["directory_content"][i] = *it;
            }

            response.body = resultDirectoryContentArr.dump();
        }
        catch (const std::exception &e)
        {
            response.code = HTTP_NOT_FOUND_CODE;
            response.body = "{'Directory is not found!'}";
            return response;
        }

        return response;
    }

    HTTPResponse POST(HTTPRequest request)
    {
        response.code = HTTP_NOT_FOUND_CODE;
        response.contentType = JSON_CONTENT_TYPE;
        response.body = "{\"Undefined\"}";
        return response;
    }

    HTTPResponse PUT(HTTPRequest request)
    {
        response.code = HTTP_NOT_FOUND_CODE;
        response.contentType = JSON_CONTENT_TYPE;
        response.body = "{\"Undefined\"}";
        return response;
    }

    HTTPResponse DELETE(HTTPRequest request)
    {
        response.code = HTTP_SUCCESS_CODE;
        response.contentType = JSON_CONTENT_TYPE;

        string targetFile = m_serverRootDir + request.path;
        try
        {
            FileHelper fileHelper(m_serverRootDir);
            if (fileHelper.DeleteFile(targetFile))
            {
                response.body = "{\"OK\"}";
            }
            else
            {
                response.body = "{\"Fail\"}";
            }
        }
        catch (const std::exception &e)
        {
            response.code = HTTP_NOT_FOUND_CODE;
            response.body = "{\"File not found\"}";
            return response;
        }

        return response;
    }

    HTTPResponse OPTIONS(HTTPRequest request)
    {
        response.code = HTTP_SUCCESS_CODE;
        response.contentType = JSON_CONTENT_TYPE;
        response.body = "";
        return response;
    }

    void SetServerRootDir(const std::string &rootDir)
    {
        m_serverRootDir = rootDir;
    }

private:
    HTTPResponse response;
    std::string m_serverRootDir;
};