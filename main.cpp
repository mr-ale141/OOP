#include <iostream>
template<typename T, size_t N>
size_t size(const T (&data)[N]) { return N; }
int main()
{
    char str[] = {'A','B','C','D','E','F',32,'H','E','L','L','O'};
    char arr[] = {70,71,72};
    char str2[] = {'#','B','C','D','E','F',32,'H','E','L','L','!'};
    std::cout << sizeof(str) / sizeof(str[0]) << std::endl;
    std::cout << size(arr) << std::endl;
    std::cout << *arr << ' ' << arr << std::endl;
    std::cout << str << std::endl;
    std::cout << int(str[12]) << std::endl;
    std::cout << int(str[13]) << std::endl;
    std::cout << int(str[14]) << std::endl;
    std::cout << str2 << std::endl;
    return 0;
}
