#include <iostream>
template<typename T, size_t N>
size_t size(const T (&data)[N]) { return N; }
int main()
{
    int arr[3] = {20, 30, 40};
    std::cout << sizeof(arr) / sizeof(arr[0]) << std::endl;
    std::cout << size(arr) << std::endl;
    return 0;
}
