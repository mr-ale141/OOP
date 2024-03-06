#include <fstream>
#include <cstdint>
#include <string>
#include <exception>
#include "crypt.h"

static const uint8_t keyMin = 0;
static const uint8_t keyMax = 255;
static const uint8_t indexesMix[8] = { 2, 3, 4, 6, 7, 0, 1, 5 };

// кричащий стиль
enum class Mode
{
	CRYPT,
	DECRYPT,
};

struct CryptData
{
	Mode mode;
	std::ifstream inputFile;
	std::ofstream outputFile;
	uint8_t key;
};

CryptData GetCryptData(
	const std::string& mode,
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& key
)
{
	// не убирать фигурные скобки
	CryptData cryptData;

	if (mode == "crypt")
	{
		cryptData.mode = Mode::CRYPT;
	}
	else if (mode == "decrypt")
	{
		cryptData.mode = Mode::DECRYPT;
	}
	else
	{
		throw std::invalid_argument("ERROR! Parameter 'mode' is not <crypt | decrypt>");
	}

	cryptData.inputFile.open(inputFileName, std::ios::binary);
	if (!cryptData.inputFile.is_open())
	{
		throw std::ios_base::failure("ERROR! Can't open " + inputFileName);
	}

	cryptData.outputFile.open(outputFileName, std::ios::binary | std::fstream::trunc);
	if (!cryptData.outputFile.is_open())
	{
		throw std::ios_base::failure("ERROR! Can't open " + outputFileName);
	}

	int keyInt = std::stoi(key);

	if (keyInt < keyMin || keyInt > keyMax)
	{
		throw std::invalid_argument("ERROR! Parameter 'key' is not between 0 .. 255");
	}

	cryptData.key = (uint8_t)keyInt;

	return cryptData;
}

void Crypt(std::istream& inStream, std::ostream& outStream, char key)
{
	// использовать для лучшей читабельности while
	char byte = 0;
	while (inStream.get(byte))
	{
		char mixByte{};
		byte ^= key;
		for (char i = 0; i < sizeof(indexesMix); i++)
		{
			uint8_t bit = (byte >> i) & 1;
			bit = bit << indexesMix[i];
			mixByte |= bit;
		}
		outStream.put(mixByte);
	}
}

void Decrypt(std::istream& inStream, std::ostream& outStream, char key)
{
	// использовать для лучшей читабельности while
	char mixByte = 0;
	while (inStream.get(mixByte))
	{
		char byte{};
		for (char i = 0; i < sizeof(indexesMix); i++)
		{
			uint8_t bit = (mixByte >> indexesMix[i]) & 1;
			bit = bit << i;
			byte |= bit;
		}
		byte ^= key;
		outStream.put(byte);
	}
}

void Сryptographer(
	const std::string& mode,
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& key)
{
	CryptData cryptData = GetCryptData(mode, inputFileName, outputFileName, key);

	switch (cryptData.mode)
	{
	case Mode::CRYPT:
		Crypt(cryptData.inputFile, cryptData.outputFile, cryptData.key);
		break;
	case Mode::DECRYPT:
		Decrypt(cryptData.inputFile, cryptData.outputFile, cryptData.key);
		break;
	}

	if (!cryptData.outputFile.flush())
	{
		throw std::ios_base::failure("ERROR! Can't write in output file");
	}

	cryptData.inputFile.close();
	cryptData.outputFile.close();
}