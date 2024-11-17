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
        bool contain_func(string tmp);
        double get_operand_value(string expression,Spreadsheet& tmp);
        double Sum(string expression,Spreadsheet& tmp);
        double Aver(string expression,Spreadsheet& tmp);
        double Stddev(string expression,Spreadsheet& tmp);
        double Max(string expression,Spreadsheet& tmp);
        double Min(string expression,Spreadsheet& tmp);
        double func_value(Spreadsheet& tmp,int i,int j,string main_expression);
    private:
};

#endif