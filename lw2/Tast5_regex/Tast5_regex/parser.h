#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
	UNKNOWN
};

std::string GetProtocolStr(Protocol protocol);

bool ParseURL(std::string const& url, Protocol&  protocol, int& port, std::string& host, std::string& document);