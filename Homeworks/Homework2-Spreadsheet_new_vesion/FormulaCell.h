#ifndef FORMULACELL_H
#define FORMULACELL_H

#include"Cell.h"
#include<iostream>
#include<string>
using namespace std;
namespace spread
{
    template<class T>
    class FormulaCell:public Cell
    {
        public:
            void setCell(const string& in);
            const string getCell();
            void setValue(const T& val);
            const T& getValue();
        private:
            string formulas;
            T value;
    };

    template<class T>
    void FormulaCell<T>::setCell(const string& in)
    {
        formulas = in;
    }
    template<class T>
    const string FormulaCell<T>::getCell()
    {
        return formulas;
    }
    template<class T>
    const T& FormulaCell<T>::getValue(){return value;}
    template<class T>
    void FormulaCell<T>::setValue(const T& val){value = val;}
}

#endif