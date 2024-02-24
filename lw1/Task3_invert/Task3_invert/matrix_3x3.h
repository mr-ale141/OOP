#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

std::vector<std::vector<double>> GetInverse3x3(const std::vector<std::vector<double>>& m);

void PrintMatrix(const std::vector<std::vector<double>>& m);

std::vector<std::vector<double>> GetMatrix(const std::string& inputFileName, const size_t matrixSize);