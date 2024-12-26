#ifndef VALUECELL_H
#define VALUECELL_H

#include"Cell.h"
#include<iostream>
#include<string>
using namespace std;

template<class T>
class ValueCell: public Cell
{
    public:
        void setCell(const T& in);
        const T& getCell();
    private:
        int intValue;
        double doubleValue;
        string stringValue;
};


#endif