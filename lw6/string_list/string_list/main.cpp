#include <iostream>
#include "CStringList.h"

int main()
{
    CStringList list;
	std::string str1("a");
	std::string str2("b");
	std::string str3("c");
	list.PushBack(str1);
	list.PushBack(str2);
	list.PushBack(str3);
	auto it1 = list.begin();
	auto it2 = list.begin() + 2;
	std::cout << it2 - it1 << std::endl;;
}