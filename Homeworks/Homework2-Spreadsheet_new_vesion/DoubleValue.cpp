#include"DoubleValue.h"
namespace spread
{
    /*virtual metod overrides*/
    /*converting input to keep as double*/
    void DoubleValue::setCell(const string& in)
    {
        double_value = stod(in);
    }
    /*converting input to get as string*/
    const string DoubleValue::getCell()
    {
        return to_string(double_value);
    }
}