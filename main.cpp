#include "lib/stdc++.h"

#include "HttpServer/HttpServer.h"
#include "FileServer/MyRestHandler.h"
#include "FileServer/FileHelper/FileHelper.h"

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

        FileHelper fileHelper(targetRootDir);
        fileHelper.GetDirectoryContent(targetRootDir);
        fileHelper.DeleteFile("/Users/lull/Documents/capital-building-2.jpg");
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }

    return 11;

    MyRestHandler restHandler;
	HTTPServer server(&restHandler, port);

	server.Start();
	cout << "[+] Server start at " << port << " port!\n"
		 << "Input some for stopping server" << endl;

	string inputStr;
	getline(cin, inputStr);
	server.Stop();

	return 0;
}
