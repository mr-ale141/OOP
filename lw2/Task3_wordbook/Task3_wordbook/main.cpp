#include "wordbook.h"
#include "ui.h"

int main(const int argc, const char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error! There are no required parameters!" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "-> bookword.exe <file_name>" << std::endl;
		return 1;
	}

	std::string fileName(argv[1]);

	auto book = GetWordBook(fileName);
	if (!book.isValid)
	{
		std::cout << book.msg << std::endl;
		return 1;
	}

	std::string exitString = "...";
	PrintUi(exitString);
	std::string answer;
	while (std::getline(std::cin, answer))
	{
		if (answer == exitString)
		{
			break;
		}
		if (!PrintWords(book, answer))
		{
			std::string value = GetTranslate(answer);
			if (value != "")
			{
				AddNewWord(book, answer, value);
				if (!book.isValid)
				{
					std::cout << book.msg << std::endl;
					PrintUi(exitString);
					continue;
				}
				std::cout << "Word '" << answer << "' ";
				std::cout << "saved as '" << value << "'." << std::endl;
			}
		}
		PrintUi(exitString);
	}

	if (book.newEnKeys.size() != 0)
	{
		if (ThrowQuestion("Save new words?"))
		{
			SaveWordBook(book);
			if (!book.isValid)
			{
				std::cout << book.msg << std::endl;
				return 1;
			}
			std::cout << "Book saved. ";
		}
	}

	std::cout << "Bye!" << std::endl;
	return 0;
}