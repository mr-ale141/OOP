#include <regex>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cassert>
#include "CHttpUrl.h"

namespace
{
    const unsigned short httpPortDefault = 80;
    const unsigned short httpsPortDefault = 443;

    const std::regex urlR(R"(^([hH][tT][tT][pP][sS]?)\://((\w+)+(\.\w+)+)\:?(\d+)?(/.+)*)");
    const size_t indexProtocol = 1;
    const size_t indexDomain = 2;
    const size_t indexPort = 5;
    const size_t indexDocument = 6;

    const std::regex domainR(R"((\w+)+(\.\w+)+)");

    std::string GetLower(std::string const& str)
    {
        std::string lower(str);
        std::transform(lower.cbegin(), lower.cend(), lower.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return lower;
    }

    Protocol GetProtocolEnum(const std::string& str)
    {
        std::string lower = GetLower(str);
        assert(lower == "http" || lower == "https");
        return lower == "http" ? Protocol::HTTP : Protocol::HTTPS;
    }

    std::string GetProtocolString(Protocol protocol)
    {
        return std::string(protocol == Protocol::HTTP ? "http" : "https");
    }
}

CHttpUrl::CHttpUrl(const std::string& url)
    : 
    m_protocol(Protocol::HTTP), 
    m_port(httpPortDefault)
{
    std::smatch m;
    if (std::regex_match(url, m, urlR))
    {
        std::string protocolStr = m[indexProtocol].str();
        std::string portStr = m[indexPort].str();
        std::string domainStr = m[indexDomain].str();
        std::string documentStr = m[indexDocument].str();

        Protocol protocol = GetProtocolEnum(protocolStr);

        //убрать предупреждения до 4 уровня
        if (!portStr.empty())
        {
            int port = std::stoi(portStr);
            // проверять граничные значения
            if (port > std::numeric_limits<unsigned short>::max())
                throw std::invalid_argument("ERROR: Port in URL is out of range!");
            m_port = static_cast<unsigned short>(port);
        }
        else
        {
            if (protocol == Protocol::HTTPS)
            {
                m_port = httpsPortDefault;
                m_protocol = protocol;
            }
        }
        
        m_domain = std::move(domainStr);
        m_document = std::move(documentStr);
    }
    else
    {
        throw std::invalid_argument("ERROR: URL-string is not valid!");
    }    
}
// localhost - is valid
// port 0 - not valid
// перехватывать исключение   stoi
CHttpUrl::CHttpUrl(
    std::string const& domain,
    std::string const& document,
    Protocol protocol
) 
    : CHttpUrl(
        domain, 
        document, 
        protocol, 
        protocol == Protocol::HTTP ? httpPortDefault : httpsPortDefault
    )
{}

CHttpUrl::CHttpUrl(
    std::string const& domain,
    std::string const& document,
    Protocol protocol,
    unsigned short port
) 
{
    std::string domainValidated = PullDomain(domain);
    std::string documentValidated = PullDocument(document);

    m_domain = std::move(domainValidated);
    m_document = std::move(documentValidated);
    m_protocol = protocol;
    m_port = port;
}

std::string CHttpUrl::GetURL() const
{
    std::string url(::GetProtocolString(m_protocol));
    url += "://";
    url += m_domain;
    if (
        m_protocol == Protocol::HTTP && m_port != httpPortDefault ||
        m_protocol == Protocol::HTTPS && m_port != httpsPortDefault
    )
    {
        url += ':';
        url += std::to_string(m_port);
    }
    url += m_document;
    return url;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    if (m_document.empty())
        return "/";
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}

std::string CHttpUrl::PullDomain(const std::string& domain)
{
    std::string str;
    std::smatch m;
    if (std::regex_match(domain, m, domainR))
    {
        str = m[0].str();
    }
    else
    {
        throw std::invalid_argument("ERROR! Domain is not valid!");
    }
    return std::move(str);
}

std::string CHttpUrl::PullDocument(const std::string& url)
{
    std::string str;
    if (!url.empty() && url[0] != '/')
        str += '/';
    str += url;
    return std::move(str);
}

std::string CHttpUrl::GetProtocolString()
{
    return std::string(m_protocol == Protocol::HTTP ? "http" : "https");
}