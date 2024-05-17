#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../http_url/CHttpUrl.h"
#include <iostream>

using namespace std::string_literals;

TEST_CASE("Empty URL")
{
	try
	{
		CHttpUrl url(""s);
	}
	catch (const std::exception&)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL without PORT")
{
	std::string urlStr("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
	std::string domainStr("www.mysite.com");
	unsigned short port = 80;
	std::string docStr("/docs/document1.html?page=30&lang=en#title");
	Protocol protocol = Protocol::HTTP;

	try
	{
		CHttpUrl url(urlStr);
		REQUIRE(url.GetURL() == urlStr);
		REQUIRE(url.GetDomain() == domainStr);
		REQUIRE(url.GetPort() == port);
		REQUIRE(url.GetDocument() == docStr);
		REQUIRE(url.GetProtocol() == protocol);

		CHttpUrl url2(domainStr, docStr, protocol);

		REQUIRE(url2.GetURL() == urlStr);
		REQUIRE(url2.GetDomain() == domainStr);
		REQUIRE(url2.GetPort() == port);
		REQUIRE(url2.GetDocument() == docStr);
		REQUIRE(url2.GetProtocol() == protocol);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		REQUIRE(false);
	}
}

TEST_CASE("URL with PORT")
{
	std::string urlStr("http://www.mysite.com:569/docs/document1.html?page=30&lang=en#title");
	std::string domainStr("www.mysite.com");
	unsigned short port = 569;
	std::string docStr("/docs/document1.html?page=30&lang=en#title");
	Protocol protocol = Protocol::HTTP;

	try
	{
		CHttpUrl url(urlStr);
		REQUIRE(url.GetURL() == urlStr);
		REQUIRE(url.GetDomain() == domainStr);
		REQUIRE(url.GetPort() == port);
		REQUIRE(url.GetDocument() == docStr);
		REQUIRE(url.GetProtocol() == protocol);

		CHttpUrl url2(domainStr, docStr, protocol, port);

		REQUIRE(url2.GetURL() == urlStr);
		REQUIRE(url2.GetDomain() == domainStr);
		REQUIRE(url2.GetPort() == port);
		REQUIRE(url2.GetDocument() == docStr);
		REQUIRE(url2.GetProtocol() == protocol);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		REQUIRE(false);
	}
}

TEST_CASE("URL with negative PORT")
{
	std::string urlStr("http://www.mysite.com:-1/docs/document1.html?page=30&lang=en#title");

	try
	{
		CHttpUrl url(urlStr);
	}
	catch (...)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL with oferflow PORT")
{
	std::string urlStr("http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title");

	try
	{
		CHttpUrl url(urlStr);
	}
	catch (...)
	{
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL without Protocol")
{
	std::string urlStr("www.mysite.com:569/docs/document1.html?page=30&lang=en#title");

	try
	{
		CHttpUrl url(urlStr);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		REQUIRE(true);
		return;
	}
	REQUIRE(false);
}

TEST_CASE("URL without doamain")
{
	std::string urlStr("http://mysite/docs/document1.html?page=30&lang=en#title");
	// обрабатывать исключение в тестах так
	REQUIRE_THROWS_AS(CHttpUrl(urlStr), std::invalid_argument);

}

TEST_CASE("URL with //host.ru:/")
{
	std::string urlStr("http://www.mysite.com:/docs/document1.html?page=30&lang=en#title");
	std::string domainStr("www.mysite.com");
	unsigned short port = 80;
	std::string docStr("/docs/document1.html?page=30&lang=en#title");
	Protocol protocol = Protocol::HTTP;

	try
	{
		CHttpUrl url(urlStr);
		REQUIRE(url.GetURL() == "http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetDomain() == domainStr);
		REQUIRE(url.GetPort() == port);
		REQUIRE(url.GetDocument() == docStr);
		REQUIRE(url.GetProtocol() == protocol);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		REQUIRE(false);
	}
}

TEST_CASE("URL with number in host")
{
	std::string urlStr("http://www.mysite.com123/docs/document1.html?page=30&lang=en#title");
	std::string domainStr("www.mysite.com123");
	unsigned short port = 80;
	std::string docStr("/docs/document1.html?page=30&lang=en#title");
	Protocol protocol = Protocol::HTTP;

	try
	{
		CHttpUrl url(urlStr);
		REQUIRE(url.GetURL() == urlStr);
		REQUIRE(url.GetDomain() == domainStr);
		REQUIRE(url.GetPort() == port);
		REQUIRE(url.GetDocument() == docStr);
		REQUIRE(url.GetProtocol() == protocol);

		CHttpUrl url2(domainStr, docStr, protocol);

		REQUIRE(url2.GetURL() == urlStr);
		REQUIRE(url2.GetDomain() == domainStr);
		REQUIRE(url2.GetPort() == port);
		REQUIRE(url2.GetDocument() == docStr);
		REQUIRE(url2.GetProtocol() == protocol);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		REQUIRE(false);
	}
}

TEST_CASE("URL caMMelCase")
{
	std::string urlStr("HTTP://wWw.mySIte.coM/docs/document1.html?page=30&lang=en#title");
	std::string domainStr("wWw.mySIte.coM");
	unsigned short port = 80;
	std::string docStr("/docs/document1.html?page=30&lang=en#title");
	Protocol protocol = Protocol::HTTP;

	try
	{
		CHttpUrl url(urlStr);
		REQUIRE(url.GetURL() == "http://wWw.mySIte.coM/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url.GetDomain() == domainStr);
		REQUIRE(url.GetPort() == port);
		REQUIRE(url.GetDocument() == docStr);
		REQUIRE(url.GetProtocol() == protocol);

		CHttpUrl url2(std::string("wWw.mySIte.coM"), docStr, protocol);

		REQUIRE(url2.GetURL() == "http://wWw.mySIte.coM/docs/document1.html?page=30&lang=en#title");
		REQUIRE(url2.GetDomain() == domainStr);
		REQUIRE(url2.GetPort() == port);
		REQUIRE(url2.GetDocument() == docStr);
		REQUIRE(url2.GetProtocol() == protocol);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		REQUIRE(false);
	}
}

TEST_CASE("URL without doc")
{
	std::string urlStr("HTTPs://wWw.mySIte.coM");
	std::string domainStr("wWw.mySIte.coM");
	unsigned short port = 443;
	std::string docStr("/");
	Protocol protocol = Protocol::HTTPS;

	try
	{
		CHttpUrl url(urlStr);
		REQUIRE(url.GetURL() == "https://wWw.mySIte.coM");
		REQUIRE(url.GetDomain() == domainStr);
		REQUIRE(url.GetPort() == port);
		REQUIRE(url.GetDocument() == docStr);
		REQUIRE(url.GetProtocol() == protocol);

		CHttpUrl url2(domainStr, std::string(""), protocol);

		REQUIRE(url2.GetURL() == "https://wWw.mySIte.coM");
		REQUIRE(url2.GetDomain() == domainStr);
		REQUIRE(url2.GetPort() == port);
		REQUIRE(url2.GetDocument() == docStr);
		REQUIRE(url2.GetProtocol() == protocol);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		REQUIRE(false);
	}
}
