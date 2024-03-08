#include <iostream>
#include <string>
#include <chrono>
#include <exception>
#include "html_decode.h"

int main()
{
	std::string str;
	while (std::getline(std::cin, str))
	{
		auto timeBegin = std::chrono::high_resolution_clock::now();

		try
		{
			std::cout << HtmlDecode(str) << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return 1;
		}
		
		auto timeEnd = std::chrono::high_resolution_clock::now();
		auto us = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeBegin);
		std::cout << "Time = " << us.count() << " us" << std::endl;
	}
	return 0;
}