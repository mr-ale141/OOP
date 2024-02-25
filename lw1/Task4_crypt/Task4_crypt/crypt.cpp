#include "crypt.h"

const uint8_t keyMin = 0;
const uint8_t keyMax = 255;

static const int indexesMix[8] = { 2, 3, 4, 6, 7, 0, 1, 5 };

enum Mode
{
	crypt,
	decrypt,
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
	CryptData cryptData;

	if (mode == "crypt")
		cryptData.mode = crypt;
	else if (mode == "decrypt")
		cryptData.mode = decrypt;
	else
		throw std::invalid_argument("Error! Parameter 'mode' is not <crypt | decrypt>");

	cryptData.inputFile.open(inputFileName, std::ios::binary);
	if (!cryptData.inputFile)
		throw std::ios_base::failure("Can't open " + inputFileName);

	cryptData.outputFile.open(outputFileName, std::ios::binary | std::fstream::trunc);
	if (!cryptData.outputFile)
		throw std::ios_base::failure("Can't open " + outputFileName);

	int keyInt = std::stoi(key);

	if (keyInt < keyMin || keyInt > keyMax)
		throw std::invalid_argument("Error! Parameter 'key' is not between 0 .. 255");

	return cryptData;
}

void Crypt(std::ifstream& fileIn, std::ofstream& fileOut, uint8_t key)
{
	fileIn.seekg(0, std::ios_base::beg);
	uint8_t mixByte = 0;
	for (uint8_t byte = 0; fileIn >> byte;)
	{
		byte ^= key;
		for (size_t i = 0; i < sizeof(indexesMix); i++)
		{
			//mixByte[indexesMix[i]] = byte[i];

		}
	}
}

void Decrypt(std::ifstream& fileIn, std::ofstream& fileOut, uint8_t key)
{
	fileIn.seekg(0, std::ios_base::beg);

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
	case crypt:
		Crypt(cryptData.inputFile, cryptData.outputFile, cryptData.key);
		break;
	case decrypt:
		Decrypt(cryptData.inputFile, cryptData.outputFile, cryptData.key);
		break;
	}
}