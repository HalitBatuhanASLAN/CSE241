#ifndef INTVALUE_H
#define INTVALUE_H

#include"ValueCell.h"

class IntValue : public ValueCell
{
    public:
        void setCell(const string& in);
        const string getCell();
    private:
        int int_value;
};

#endif