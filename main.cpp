//make sure to compile with -pthread (g++ -pthread example.cpp)
#include "lib/stdc++.h"
#include "HttpServer/HttpServer.h"

using namespace std;

int main() 
{
	//create a handler instance
	//create a server instance
	HTTPServer server(1104);
	//start the server
	server.Start();
	cout << "Press enter at any time to stop" << endl;
	//wait untill the user presses enter and quits
	string str;
	getline(cin, str);
	//stop the server
	server.Stop();
	return 0;
}
