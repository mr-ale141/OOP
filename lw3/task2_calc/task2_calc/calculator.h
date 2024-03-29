#pragma once
#include "alu.h"
#include "printer.h"
#include "scanner.h"
#include "define.h"

class Calculator
{
public:
    Calculator(std::ostream&);
    bool Exec(const std::string&);
private:
    Alu _alu;
    Printer _printer;
    Scanner _scanner;
};