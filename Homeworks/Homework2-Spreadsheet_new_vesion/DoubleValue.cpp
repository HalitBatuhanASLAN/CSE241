#include"DoubleValue.h"
namespace spread
{
    void DoubleValue::setCell(const string& in)
    {
        double_value = stod(in);
    }
    const string DoubleValue::getCell()
    {
        return to_string(double_value);
    }
}