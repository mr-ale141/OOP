#include <iostream>
#include "CHttpUrl.h"

int main()
{
    std::string str;
	size_t count = 1;
    while (std::getline(std::cin, str))
    {
		std::cout << "-------------- " << count << " --------------" << std::endl;
		std::cout << "InputURL: " << str << std::endl;
		try
		{
			CHttpUrl url(str);
			std::cout << "URL     : " << url.GetURL() << std::endl;
			std::cout << "Protocol: " << url.GetProtocolString() << std::endl;
			std::cout << "Domain  : " << url.GetDomain() << std::endl;
			std::cout << "Port    : " << url.GetPort() << std::endl;
			std::cout << "Document: " << url.GetDocument() << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		++count;
    }
}