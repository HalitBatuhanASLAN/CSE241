#include"IntValue.h"
namespace spread
{
    void IntValue::setCell(const string& in)
    {
        int_value = stoi(in);
    }
    const string IntValue::getCell()
    {
        return to_string(int_value);
    }
}