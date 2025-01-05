#include"StringValue.h"

namespace spread
{
    /*overrites of metods*/
    /*get and set metods of private attributes*/
    void StringValue::setCell(const string& in)
    {
        str_value = in;
    }
    const string StringValue::getCell()
    {
        return str_value;
    }
}