#include "CMyString.h"
#include <cstring>

static char emptyString[] = "";

CMyString::CMyString() : m_string(emptyString)
{}

// конструктор, инициализирующий строку данными строки
// с завершающим нулевым символом
CMyString::CMyString(const char* pString)
{
	m_length = strlen(pString);
	if (m_length >= m_capacity - 1)
		m_capacity = m_length * 2;
	m_string = new char[m_capacity];
	strncpy_s(m_string, m_capacity, pString, m_length + 1);
}

// конструктор, инициализирующий строку данными из 
// символьного массива заданной длины
CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	if (m_length >= m_capacity - 1)
		m_capacity = m_length * 2;
	m_string = new char[m_capacity];
	memcpy(m_string, pString, m_length);
	m_string[m_length] = '\0';
}

// конструктор копирования
CMyString::CMyString(CMyString const& other)
{
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	m_string = new char[m_capacity];
	memcpy(m_string, other.m_string, m_length + 1);
}

// перемещающий конструктор
// реализуется совместно с перемещающим оператором присваивания 
CMyString::CMyString(CMyString&& other) noexcept
{
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	m_string = other.m_string;
	other.m_string = emptyString;
}

// конструктор, инициализирующий строку данными из 
// строки стандартной библиотеки C++
CMyString::CMyString(std::string const& stlString) : CMyString(stlString.c_str())
{}

// деструктор класса - освобождает память, занимаемую символами строки
CMyString::~CMyString()
{
	if (m_string != emptyString)
		delete[] m_string;
}

// возвращает длину строки (без учета завершающего нулевого символа)
size_t CMyString::GetLength()const
{
	return m_length;
}

// возвращает указатель на массив символов строки.
// В конце массива обязательно должен быть завершающий нулевой символ
// даже если строка пустая 
const char* CMyString::GetStringData()const
{
	return m_string;
}

// возвращает подстроку с заданной позиции длиной не больше length символов
CMyString CMyString::SubString(size_t start, size_t length)const
{
	return CMyString(&m_string[start - 1], length);
}

// очистка строки (строка становится снова нулевой длины)
void CMyString::Clear()
{
	m_capacity = defaultCap;
	m_length = 0;
	this->~CMyString();
	m_string = emptyString;
}

// Возвращает вместимость строки
size_t CMyString::GetCapacity()
{
	return m_capacity;
}
