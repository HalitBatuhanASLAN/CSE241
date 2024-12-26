#ifndef FORMULACELL_H
#define FORMULACELL_H

#include"Cell.h"
#include<iostream>
#include<string>
using namespace std;

template<class T>
class FormulaCell:public Cell
{
    public:
        void setCell(const T& in);
        const T& getCell();
    private:
        string formulas;
};

#endif