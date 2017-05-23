#include "lib/stdc++.h"

#include "HttpServer/HttpServer.h"
#include "FileServer/MyRestHandler.h"

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc != 3)
	{
		cout << "Simple REST fileserver\n"
			 << "Usage: program <port> <root_dir>\n";
		return 1;
	}

    size_t port;

    try
    {
        // todo validate port
        port = stoi(argv[1]);
        // todo validate target root
        string targetRootDir = argv[2];

        MyRestHandler restHandler;
        restHandler.SetServerRootDir(targetRootDir);

        HTTPServer server(&restHandler, port);

        server.Start();
        cout << "[+] Server start at " << port << " port!\n"
             << "Input some for stopping server" << endl;

        string inputStr;
        getline(cin, inputStr);
        server.Stop();
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }

	return 0;
}
