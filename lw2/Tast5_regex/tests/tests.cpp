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

TEST_CASE("Correct URL without PORT")
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

TEST_CASE("Correct URL with PORT")
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