#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

//array גלוסעמ vector
using Matrix3x3 = std::vector<std::vector<double>>;
using Matrix2x2 = std::vector<std::vector<double>>;

Matrix3x3 GetInverse3x3(const Matrix3x3& m);

void PrintMatrix3x3(const Matrix3x3& m);

Matrix3x3 GetMatrix3x3(const std::string& inputFileName);