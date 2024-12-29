#ifndef DOUBLEVALUE_H
#define DOUBLEVALUE_H

#include"ValueCell.h"

class DoubleValue : public ValueCell
{
    public:
        void setCell(const string& in);
        const string getCell();
    private:
        double double_value;
};

#endif