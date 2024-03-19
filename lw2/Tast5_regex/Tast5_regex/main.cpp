#include "parser.h"

int main()
{
	std::string url;
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	bool isOk;

	while (std::getline(std::cin, url))
	{
		isOk = ParseURL(url, protocol, port, host, document);
		if (isOk)
		{
			std::cout << "PROTOCOL: <" << GetProtocolStr(protocol) << '>' << std::endl;
			std::cout << "HOST    : <" << host << '>' << std::endl;
			std::cout << "PORT    : <" << port << '>' << std::endl;
			std::cout << "DOC     : <" << document << '>' << std::endl;
		}
		else
		{
			std::cout << "URL is incorrect" << std::endl;
		}
	}
}
