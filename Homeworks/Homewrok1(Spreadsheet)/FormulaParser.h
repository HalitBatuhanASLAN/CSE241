#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include"Spreadsheet.h"
#include"Cell.h"
#include<iostream>
#include<string>

using namespace std;
class Spreadsheet;
enum formula_type
{
    SUM,
    AVER,
    STDDEV,
    MAX,
    MIN,
    OTHER
};

class FormulaParser
{
    public:
        FormulaParser(Spreadsheet& sheet) : tmp(sheet) {}
        void set_type(int i,int j);
        formula_type get_type(int i,int j);
        void relevant_func(int i,int j);
        
        
        void Sum();
        void other_calc(int i,int j);
        double get_operand_value(const string operand);
    private:
        formula_type type;
        Spreadsheet& tmp;
};


#endif