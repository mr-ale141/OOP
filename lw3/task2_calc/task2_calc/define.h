#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <vector>

const int notValid = -1;
const int isNotFunc = -1;

enum class Operation
{
    SUM,
    SUB,
    MUL,
    DIV,
    UNKNOWN
};

enum class TypeCmd
{
    DECLARATION,
    INIT_VAR,
    INIT_FUNC,
    COPY,
    PRINT,
    PRINTVARS,
    PRINTFNS,
    UNKNOWN
};

struct Cmd
{
    TypeCmd type = TypeCmd::UNKNOWN;
    std::string firstName;
    std::string midleName;
    std::string lastName;
    Operation operation = Operation::UNKNOWN;
    double value = std::numeric_limits<double>::quiet_NaN();
};

struct Var
{
    double value = std::numeric_limits<double>::quiet_NaN();
    std::string name;
    int function = isNotFunc;
    std::vector<int> childFuncs;
};

struct Func
{
    std::string name;
    int operandLeft = notValid;
    int operandRight = notValid;
    Operation operation = Operation::UNKNOWN;
    int childVar = notValid;
};
