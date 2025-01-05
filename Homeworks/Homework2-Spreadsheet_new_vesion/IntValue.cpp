#include"IntValue.h"
namespace spread
{
    /*virtual metod overrides*/
    /*converting to int to keep data as integer*/
    void IntValue::setCell(const string& in)
    {
        int_value = stoi(in);
    }
    /*converting to string to get data as string*/
    const string IntValue::getCell()
    {
        return to_string(int_value);
    }
}