//make sure to compile with -pthread (g++ -pthread example.cpp)
#include "lib/stdc++.h"
//#include "HttpServer/HttpServer.h"
#include "HttpServer/RestServer.h"

using namespace std;

int main() 
{
	HTTPServer server(1105);
    RestServer rest(server);
    rest.HandleRequests();

	cout << "Press enter at any time to stop" << endl;
	string str;
	getline(cin, str);

	rest.Stop();
	return 0;
}
