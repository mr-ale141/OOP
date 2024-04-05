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

enum class TypeCmd // commandType
{
    DECLARATION,
    INIT_VAR,
    INIT_FUNC,
    COPY_VAR,
    COPY_FUNC,
    PRINT,
    PRINTVARS,
    PRINTFNS,
    UNKNOWN
};

// cmd name
struct Cmd // command
{
    TypeCmd type = TypeCmd::UNKNOWN; //commandType
    std::string firstName; // entityName
    std::string midleName;// middle, operationLeft
    std::string lastName; // operationRight
    Operation operation = Operation::UNKNOWN;
    double value = std::numeric_limits<double>::quiet_NaN();
};

struct Var
{
    double value = std::numeric_limits<double>::quiet_NaN();
    std::string name;
    int function = isNotFunc; //funcIndex optional
    std::vector<int> childFuncs;
};

struct Func
{
    std::string name;
    int operandLeft = notValid; // optional
    int operandRight = notValid; // optional
    Operation operation = Operation::UNKNOWN;
    int childVar = notValid; // varIndex
};
