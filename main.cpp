//this example will serve a standart html page on port 1122
//make sure to compile with -pthread (g++ -pthread example.cpp)
#include "lib/stdc++.h"
#include "HttpServer/HttpServer.h"
using namespace std;

class MyHandler : public HTTPRequestHandler
{
public:
    //method that will handle the requests
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


int main() 
{
	//create a handler instance
	MyHandler hnd;
	//create a server instance
	HTTPServer server(1103);
	//start the server
    server.SetHandler(&hnd);
	server.Start();
	cout << "Press enter at any time to stop" << endl;
	//wait untill the user presses enter and quits
	string str;
	getline(cin, str);
	//stop the server
	server.Stop();
	return 0;
}
