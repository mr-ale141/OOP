#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#define WITH_RING_BUFFER 0

#if WITH_RING_BUFFER
#include <memory>
void ReplaceInFile(const std::string& inputFileName,
                   const std::string& outputFileName,
                   const std::string& search,
                   const std::string& replace)
{
    std::ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        throw std::ios_base::failure("Can't open " + inputFileName);
    }
    std::ofstream outputFile(outputFileName, std::fstream::trunc);
    if (!outputFile)
    {
        throw std::ios_base::failure("Can't open " + outputFileName);
    }
    size_t strLength = search.length();
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

    if (!outputFile.flush())
    {
        throw std::ios_base::failure("Can't write in " + outputFileName);
    }
}
#else
// кмп алгоритм, std::search
std::string ReplaceString(const std::string& subject,
                          const std::string& searchString,
                          const std::string& replacementString)
{
    if (searchString.empty())
        return subject;
    size_t pos = 0;
    std::string result;
    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
        result.append(subject, pos, foundPos - pos);
        if (foundPos == std::string::npos)
            break;
        result.append(replacementString);
        pos = foundPos + searchString.length();
    }
    return result;
}

void ReplaceInFile(std::string& inputFileName, std::string& outputFileName,
                  std::string& search, std::string& replace)
{
    std::string line;
    std::ifstream inputFile(inputFileName);
    if (!inputFile)
    {
        throw std::ios_base::failure("Can't open " + inputFileName);
    }
    std::ofstream outputFile(outputFileName, std::fstream::trunc);
    if (!outputFile)
    {
        throw std::ios_base::failure("Can't open " + outputFileName);
    }
    while (std::getline(inputFile, line))
    {
        outputFile << ReplaceString(line,
                                    search,
                                    replace
                                    ) << "\n";
    }

    if (!outputFile.flush())
    {
        throw std::ios_base::failure("Can't write in " + outputFileName);
    }
}
#endif

int main(int argc, char* argv[])
{
    auto timeBegin = std::chrono::high_resolution_clock::now();
    if (argc != 5)
    {
        std::cout << "Error! There are no required parameters!" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "-> replace.exe file_in file_out ";
        std::cout << "search_string replacement_string" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
    std::string search = argv[3];
    std::string replace = argv[4];

    try
    {
        ReplaceInFile(inputFileName, outputFileName, search, replace);
    }
    catch (std::ios_base::failure& e)
    {
        std::cout << e.what() << std::endl;
		return 1;
    }

    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin);
    std::cout << "Delta Time = " << us.count() << " us" << std::endl;

    return 0;
}
