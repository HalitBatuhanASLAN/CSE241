#include"FormulaCell.h"

void FormulaCell::setCell(const string& in)
{
    formulas = in;
}
const string& FormulaCell::getCell()
{
    return formulas;
}