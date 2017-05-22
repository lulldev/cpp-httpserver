#include "lib/stdc++.h"
#include "HttpServer/HttpServer.h"

using namespace std;

class MyHandler : public HTTPRequestHandler
{
public:
	HTTPResponse HandleRequest(HTTPRequest request)
	{
		//you can get the method and the path with .method and .path
		cout << request.method << " request to " << request.path << endl;
		if (request.method == "POST")
		{
			//you can get the post body with .body
			cout << "post body:" << endl << request.body << endl;
		}
		//these are the required response fields. Make sure they're all filled in
		HTTPResponse response;
		response.code = 200;
		response.contentType = "text/html";
		response.body = "<html><body><form method='post'><input name='sdfsd' value='dsfsdfsdfasd'/><button>go</button></form></body></html>";
		return response;
	}
};

class MyRestHandler: public HTTPRequestRESTHandler
{
public:

	HTTPResponse GET(HTTPRequest request)
	{
		response.code = 200;
		response.contentType = "json";
		response.body = "{'OK'}";
		return response;
	}

	HTTPResponse POST(HTTPRequest request)
	{
		response.code = 404;
		response.contentType = "json";
		response.body = "{'Undefined'}";
		return response;
	}

	HTTPResponse PUT(HTTPRequest request)
	{
		response.code = 404;
		response.contentType = "json";
		response.body = "{'Undefined'}";
		return response;
	}

	HTTPResponse DELETE(HTTPRequest request)
	{
		response.code = 404;
		response.contentType = "json";
		response.body = "{'Undefined'}";
		return response;
	}

private:
	HTTPResponse response;
};

int main()
{
	MyRestHandler restHandler;
	HTTPServer server(&restHandler, 1124);
	server.Start();
	cout << "Serving on port 1122" << endl;
	cout << "Press enter at any time to stop" << endl;
	string str;
	getline(cin, str);
	server.Stop();
	return 0;
}
