#pragma once
#include <string>
#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
    explicit CUrlParsingError(const std::string& urlString)
        : std::invalid_argument("URL '" + urlString + "' is not valid") {}
};