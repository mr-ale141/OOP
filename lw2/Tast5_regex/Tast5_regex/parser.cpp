#include <regex>
#include <algorithm>
#include <cctype>
#include "parser.h"

std::string GetProtocolStr(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return std::string("http");
	case Protocol::HTTPS:
		return std::string("https");
	case Protocol::FTP:
		return std::string("ftp");
	default:
		return std::string("");
	}
}

std::string GetLowwer(const std::string& str)
{
	std::string lowwer;
	std::transform(lowwer.begin(), lowwer.end(), lowwer.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return lowwer;
}

Protocol GetProtocol(const std::string& str)
{
	if (str == "http")
	{
		return Protocol::HTTP;
	}
	else if (str == "https")
	{
		return Protocol::HTTPS;
	}
	else if (str == "ftp")
	{
		return Protocol::FTP;
	}
	else
	{
		return Protocol::UNKNOWN;
	}
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	auto lowwerUrl = GetLowwer(url);
	const std::regex protocolR(R"(^(http[s]{0,1}|ftp))");
	const std::regex hostWithPortR(R"((\:\/\/([a-z0-9]+\.)+([a-z0-9]+)(\:[0-9]+)?\/))");
	const std::regex hostR(R"((([a-z0-9]+\.)+([a-z0-9]+)))");
	const std::regex portR(R"(\:[0-9]+\/$)");

	std::string protocolStr;
	std::string hostWithPort;

	std::smatch match;
	if (std::regex_search(url, match, protocolR))
	{
		protocolStr = match.str(1);
		protocol = GetProtocol(protocolStr);
	}
	else
	{
		return false;
	}
	
	if (std::regex_search(url, match, hostWithPortR))
	{
		hostWithPort = match.str(1);
		std::smatch result;

		if (std::regex_search(hostWithPort, result, hostR))
		{
			host = result[0].str();
		}
		else
		{
			return false;
		}

		if (std::regex_search(hostWithPort, result, portR))
		{
			std::string portStr = result[0].str();
			portStr.erase(
				std::remove_if(portStr.begin(), portStr.end(), 
					[](char ch) { return ch == ':' || ch == '/'; }), 
				portStr.end()
			);
			port = std::stoi(portStr);
		}
		else
		{
			port = 80;
		}
	}
	else
	{
		return false;
	}

	size_t pos = protocolStr.length() + hostWithPort.length();

	document.clear();
	document.append(url, pos, std::string::npos);

	return true;
}