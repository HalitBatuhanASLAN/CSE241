#include"ValueCell.h"
#include<iostream>
#include<string>
using namespace std;
namespace spread
{
    void ValueCell::setCell(const string& in)
    {
        tmp_value = in;
    }
    const string ValueCell::getCell()
    {
        return tmp_value;
    }
}