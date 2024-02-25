#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <exception>

void Сryptographer(
	const std::string& mode, 
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& key
);