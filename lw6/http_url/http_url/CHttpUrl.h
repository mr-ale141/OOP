#pragma once
#include <string>

enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    // выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. Порт, являющийся стандартным для
    // выбранного протокола (80 для http и 443 для https) в эту строку
    // не должен включаться
    std::string GetURL() const;

    // возвращает доменное имя
    std::string GetDomain() const;

    /*
        Возвращает имя документа. Примеры:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument() const;

    // возвращает тип протокола
    Protocol GetProtocol() const;
    std::string GetProtocolString();

    // возвращает номер порта
    unsigned short GetPort() const;

private:
    static std::string PullDomain(const std::string& domainWithPort);
    static std::string PullDocument(const std::string& url);

    Protocol m_protocol;
    std::string m_domain;
    unsigned short m_port;
    std::string m_document;
};