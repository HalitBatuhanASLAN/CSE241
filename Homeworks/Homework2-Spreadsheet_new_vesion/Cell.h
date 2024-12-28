#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
using namespace std;

class Cell
{
    public:
        virtual void setCell(const string& in);
        virtual const string& getCell();
};

#endif