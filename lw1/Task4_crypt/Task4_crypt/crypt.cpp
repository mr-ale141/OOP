#include "crypt.h"

static const uint8_t keyMin = 0;
static const uint8_t keyMax = 255;
static const uint8_t indexesMix[8] = { 2, 3, 4, 6, 7, 0, 1, 5 };

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
		throw std::invalid_argument("ERROR! Parameter 'mode' is not <crypt | decrypt>");

	cryptData.inputFile.open(inputFileName, std::ios::binary);
	if (!cryptData.inputFile)
		throw std::ios_base::failure("ERROR! Can't open " + inputFileName);

	cryptData.outputFile.open(outputFileName, std::ios::binary | std::fstream::trunc);
	if (!cryptData.outputFile)
		throw std::ios_base::failure("ERROR! Can't open " + outputFileName);

	int keyInt = std::stoi(key);

	if (keyInt < keyMin || keyInt > keyMax)
		throw std::invalid_argument("ERROR! Parameter 'key' is not between 0 .. 255");

	cryptData.key = (uint8_t)keyInt;

	return cryptData;
}

void Crypt(std::ifstream& fileIn, std::ofstream& fileOut, char key)
{
	for (char byte = 0; fileIn.get(byte);)
	{
		char mixByte{};
		byte ^= key;
		for (char i = 0; i < sizeof(indexesMix); i++)
		{
			uint8_t bit = (byte >> i) & 1;
			bit = bit << indexesMix[i];
			mixByte |= bit;
		}
		fileOut.put(mixByte);
	}
}

void Decrypt(std::ifstream& fileIn, std::ofstream& fileOut, char key)
{
	for (char mixByte = 0; fileIn.get(mixByte);)
	{
		char byte{};
		for (char i = 0; i < sizeof(indexesMix); i++)
		{
			uint8_t bit = (mixByte >> indexesMix[i]) & 1;
			bit = bit << i;
			byte |= bit;
		}
		byte ^= key;
		fileOut.put(byte);
	}
}

void Сryptographer(
	const std::string& mode,
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& key)
{
	CryptData cryptData = GetCryptData(mode, inputFileName, outputFileName, key);

	cryptData.inputFile.seekg(0, std::ios_base::beg);

	switch (cryptData.mode)
	{
	case crypt:
		Crypt(cryptData.inputFile, cryptData.outputFile, cryptData.key);
		break;
	case decrypt:
		Decrypt(cryptData.inputFile, cryptData.outputFile, cryptData.key);
		break;
	}

	if (!cryptData.outputFile.flush())
		throw std::ios_base::failure("ERROR! Can't write in output file");

	cryptData.inputFile.close();
	cryptData.outputFile.close();
}