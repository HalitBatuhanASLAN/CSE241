#ifndef FORMULACELL_H
#define FORMULACELL_H

#include"Cell.h"
#include<iostream>
#include<string>
using namespace std;

class FormulaCell:public Cell
{
    public:
        void setCell(const string& in);
        const string getCell();
    private:
        string formulas;
};

#endif