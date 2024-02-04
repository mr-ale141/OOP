#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>

template<typename T, size_t N>
size_t size(const T (&data)[N]) { return N; }

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
        do {
            inputFile.get(ch);
            ringBuffer[end] = ch;
            end = ++end % strLength;
        } while (ch != '\n' && end != begin && !inputFile.eof());
        for (size_t i = 0; i < strLength; i++)
            std::cout << ringBuffer[i];
        std::cout << std::endl;
    }
    else
        for (char ch; inputFile.get(ch);) outputFile.put(ch);
    inputFile.close();
    outputFile.close();
    return 0;
}
