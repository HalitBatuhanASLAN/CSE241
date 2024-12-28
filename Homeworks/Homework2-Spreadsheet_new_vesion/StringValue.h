#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include"ValueCell.h"

class StringValue : public ValueCell
{
    public:
        void setCell(const string& in);
        const string& getCell();
    private:
        string str_value;
};

#endif