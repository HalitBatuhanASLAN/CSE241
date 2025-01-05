#include"FormulaCell.h"
//I deleted impleention of formula cell in makefile because it gives problem when I try to use it with templates
/*keeping inplementation in header is better*/
namespace spread
{
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