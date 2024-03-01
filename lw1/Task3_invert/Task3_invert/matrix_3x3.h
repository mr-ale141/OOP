#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

//array גלוסעמ vector
using Matrix = std::vector<std::vector<double>>;

Matrix GetInverse3x3(const Matrix& m);

void PrintMatrix(const Matrix& m);

Matrix GetMatrix(const std::string& inputFileName, const size_t matrixSize);