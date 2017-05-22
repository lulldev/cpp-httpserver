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