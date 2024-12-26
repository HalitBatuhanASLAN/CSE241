#include"FormulaCell.h"
#include<iostream>
#include<string>
using namespace std;

template<class T>
void FormulaCell<T>::setCell(const T& in)
{
    try
    {
        double num = stod(in);
        if constexpr(is_integral<T> tmp)
            intValue = in;
        else
            doubleValue = in;
    }
    catch(const std::exception& e)
    {
        stringValue = in;
    }
}

template<class T>
const T& FormulaCell<T>::getCell()
{
    return input;
}