#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>


//std::string <- char*
void ReplaceInFile(std::ifstream& inputFile, std::ofstream& outputFile, char* search, char* replace)
{
    size_t strLength = strlen(search);
    if (strLength)
    {
        auto ringBuffer = std::make_unique<char[]>(strLength);
        size_t begin{};
        size_t end{};
        char ch{};
        while (inputFile.get(ch)) {
            bool isBufferFilled = ringBuffer[begin] != '\0';
            isBufferFilled &= begin == end;
            if (isBufferFilled)
            {
                outputFile.put(ringBuffer[begin]);
                begin = ++begin % strLength;
                ringBuffer[end] = ch;
                end = ++end % strLength;
            }
            else
            {
                ringBuffer[end] = ch;
                end = ++end % strLength;
            }
            bool find = true;
            for (size_t i = 0; i < strLength; i++)
            {
                size_t indexBuffer = (begin + i) % strLength;
                if (search[i] != ringBuffer[indexBuffer])
                {
                    find = false;
                    break;
                }
            }
            if (find)
            {
                outputFile << replace;
                for (size_t i = 0; i < strLength; i++)
                    ringBuffer[i] = '\0';
                begin = end = size_t(0);
            }
        }
        for (size_t i = 0; i < strLength; i++)
        {
            char c = ringBuffer[(begin + i) % strLength];
            if (c == '\0') break;
            outputFile.put(c);
        }
    }
    else
        for (char ch; inputFile.get(ch);) outputFile.put(ch);
}

int main(int argc, char *argv[]) {
    if (argc != 5)
    {
        std::cout << "Error! There are no required parameters!" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "-> replace.exe file_in file_out ";
        std::cout << "search_string replacement_string" << std::endl;
        // return 1
        exit(1);
    }
    std::ifstream inputFile(argv[1]);
    if (!inputFile)
    {
        std::cout << "Error! Input file '" << argv[1] << "' cannot be open!" << std::endl;
        exit(1);
    }
    std::ofstream outputFile(argv[2], std::fstream::trunc);
    if (!outputFile)
    {
        std::cout << "Error! Output file '" << argv[2] << "' cannot be open!" << std::endl;
        inputFile.close();
        exit(1);
    }
    ReplaceInFile(inputFile, outputFile, argv[3], argv[4]);
    return 0;
}
