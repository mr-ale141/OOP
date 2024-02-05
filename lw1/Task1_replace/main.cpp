#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>

int main(int argc, char *argv[]) {
    if (argc < 5)
    {
        std::cout << "Error! There are no required parameters!" << std::endl;
        std::cout << "Example:" << std::endl;
        std::cout << "-> replace.exe [file_in] [file_out] ";
        std::cout << "[search_string] [replacement_string]" << std::endl;
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
    size_t strLength = strlen(argv[3]);
    if (strLength)
    {
        auto ringBuffer = std::make_unique<char[]>(strLength);
        size_t begin{};
        size_t end{};
        char ch{};
        bool find{};
        while (inputFile.get(ch)) {
            /*if (ch == '\n')
            {
                for (size_t i = 0; i < strLength; i++)
                {
                    char c = ringBuffer[(begin + i) % strLength];
                    if (c == '\0') break;
                    ringBuffer[(begin + i) % strLength] = '\0';
                    outputFile.put(c);
                }
                begin = end = size_t(0);
                ringBuffer[begin] = '\n';
            }*/
            if (ringBuffer[begin] == '\0')
            {
                ringBuffer[begin] = ch;
                end = ++end % strLength;
            }
            else if (begin != end)
            {
                ringBuffer[end] = ch;
                end = ++end % strLength;
            }
            else
            {
                outputFile.put(ringBuffer[begin]);
                begin = ++begin % strLength;
                ringBuffer[end] = ch;
                end = ++end % strLength;
            }
            find = true;
            for (size_t i = 0; i < strLength; i++)
            {
                if (argv[3][i] != ringBuffer[(begin + i) % strLength])
                {
                    find = false;
                    break;
                }
            }
            if (find)
            {
                outputFile << argv[4];
                for (size_t i = 0; i < strLength; i++)
                    ringBuffer[i] = '\0';
                begin = end = size_t(0);
                find = false;
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
    inputFile.close();
    outputFile.close();
    return 0;
}
