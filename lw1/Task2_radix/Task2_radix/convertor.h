#pragma once
#include <iostream>
#include <string>
#include <limits>

int StringToInt(const std::string& str, int radix, bool& wasError);

std::string IntToString(int n, int radix, bool & wasError);

std::string Convert(int sourceRadix, int targetRadix, std::string numberString);
