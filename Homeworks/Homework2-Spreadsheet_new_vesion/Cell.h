#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
using namespace std;

template<class T>
class Cell
{
    public:
        virtual void setCell(const T& in);
        virtual const T& getCell();
    private:
        T input;
};

#endif
