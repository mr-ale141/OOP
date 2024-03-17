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

TEST_CASE("Correct URL")
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