#pragma once
#include <string>

static const size_t defaultCap = 15;

class CMyString
{
public:
    // конструктор по умолчанию
    CMyString();

    // конструктор, инициализирующий строку данными строки
    // с завершающим нулевым символом
    CMyString(const char* pString);

    // конструктор, инициализирующий строку данными из 
    // символьного массива заданной длины
    CMyString(const char* pString, size_t length);

    // конструктор копирования
    CMyString(CMyString const& other);

    // перемещающий конструктор
    // реализуется совместно с перемещающим оператором присваивания 
    CMyString(CMyString&& other) noexcept;

    // конструктор, инициализирующий строку данными из 
    // строки стандартной библиотеки C++
    CMyString(std::string const& stlString);

    // деструктор класса - освобождает память, занимаемую символами строки
    ~CMyString();

    // возвращает длину строки (без учета завершающего нулевого символа)
    size_t GetLength()const;

    // возвращает указатель на массив символов строки.
    // В конце массива обязательно должен быть завершающий нулевой символ
    // даже если строка пустая 
    const char* GetStringData()const;

    // возвращает подстроку с заданной позиции длиной не больше length символов
    CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

    // очистка строки (строка становится снова нулевой длины)
    void Clear();

    // Возвращает вместимость строки
    size_t GetCapacity();

private:
    size_t m_capacity = defaultCap;
    char* m_string = nullptr;
    size_t m_length = 0;
};