#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include"Spreadsheet.h"
#include"Cell.h"
#include<iostream>
#include<string>

using namespace std;
class Spreadsheet;

class FormulaParser
{
    public:
        FormulaParser(){}
        Spreadsheet& parsing(Spreadsheet& tmp,int i, int j);
        double get_operand_value(string expression,Spreadsheet& tmp);

    private:
};



#endif