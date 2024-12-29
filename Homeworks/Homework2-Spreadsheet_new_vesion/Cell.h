#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
using namespace std;

class Cell
{
    public:
        void setCell(const string& in);
        const string getCell();
        virtual ~Cell() = 0;
        Cell();
    private:
        string tmp;
};

#endif