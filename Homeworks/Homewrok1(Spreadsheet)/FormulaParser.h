#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include"Spreadsheet.h"
#include"Cell.h"
#include<iostream>
#include<string>

using namespace std;

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
        void set_type(int i,int j);
        formula_type get_type(int i,int j);
        void Sum();
        void other_calc(int i,int j);

    private:
        Spreadsheet& tmp;
        formula_type type;
};


#endif