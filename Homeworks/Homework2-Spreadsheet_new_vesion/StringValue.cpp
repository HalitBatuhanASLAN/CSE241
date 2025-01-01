#include"StringValue.h"

namespace spread
{
    void StringValue::setCell(const string& in)
    {
        str_value = in;
    }
    const string StringValue::getCell()
    {
        return str_value;
    }
}