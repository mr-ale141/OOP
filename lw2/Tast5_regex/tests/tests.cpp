#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Tast5_regex/parser.h"


TEST_CASE("Empty URL")
{
	const std::string url;

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(!isOk);
}

TEST_CASE("URL without PORT")
{
	const std::string url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("URL with PORT")
{
	const std::string url("http://www.mysite.com:569/docs/document1.html?page=30&lang=en#title");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 569);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("URL without protocol")
{
	const std::string url("www.mysite.com/docs/document1.html?page=30&lang=en#title");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(!isOk);
}

TEST_CASE("URL without host")
{
	const std::string url("http://mysite/docs/document1.html?page=30&lang=en#title");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(!isOk);
}

TEST_CASE("URL with //host.ru:/")
{
	const std::string url("http://www.mysite.com:/docs/document1.html?page=30&lang=en#title");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("URL with number in host")
{
	const std::string url("http://www.mysite.com123/docs/document1.html?page=30&lang=en#title");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com123");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("URL caMMelCase")
{
	const std::string url("HTTP://wWw.mySIte.coM/docs/document1.html?page=30&lang=en#title");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("URL without DOC")
{
	const std::string url("HTTP://wWw.mySIte.coM");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "");
}

TEST_CASE("URL HTTPS default")
{
	const std::string url("HTTPs://wWw.mySIte.coM");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::HTTPS);
	REQUIRE(port == 443);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "");
}

TEST_CASE("URL FTP default")
{
	const std::string url("ftp://wWw.mySIte.coM");

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	auto isOk = ParseURL(url, protocol, port, host, document);

	REQUIRE(isOk);
	REQUIRE(protocol == Protocol::FTP);
	REQUIRE(port == 21);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "");
}