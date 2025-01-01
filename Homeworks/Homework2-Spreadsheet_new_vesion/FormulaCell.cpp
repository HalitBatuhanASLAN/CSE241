#include"FormulaCell.h"
namespace spread
{
    void FormulaCell::setCell(const string& in)
    {
        formulas = in;
    }
    const string FormulaCell::getCell()
    {
        return formulas;
    }
}