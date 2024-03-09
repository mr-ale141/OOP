#include "wordbook.h"

void PrintUi(const std::string& exitString)
{
	std::cout << "Enter word to translate or '" + exitString + "' to exit:" << std::endl;
	std::cout << ">";
}

bool ThrowQuestion(const std::string& question)
{
	std::cout << question <<  " [Press 'Y' or 'y' to yes]:" << std::endl;
	std::string answer;
	std::getline(std::cin, answer);
	if (answer == "Y" || answer == "y")
	{
		return true;
	}
	return false;
}

std::string GetTranslate(const std::string& newWord)
{
	std::string answer;
	std::cout << "The unknown word is '" + newWord + "'. ";
	std::cout << "Enter a translation or an empty line to reject." << std::endl;
	std::cout << ">";
	std::getline(std::cin, answer);
	while (IsAsciiString(newWord) == IsAsciiString(answer))
	{
		std::cout << "ERROR! Is not translate! Try again:" << std::endl << ">";
		std::getline(std::cin, answer);
	}
	return answer;
}
