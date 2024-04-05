#pragma once
#include "alu.h"
#include "printer.h"
#include "scanner.h"
#include "define.h"

class Calculator
{
public:
    Calculator(std::ostream& output);
    bool Exec(const std::string& str);
private:
    Alu m_alu;
    Printer m_printer;
    Scanner m_scanner;
};