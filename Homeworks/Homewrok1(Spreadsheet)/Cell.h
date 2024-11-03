#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
using namespace std;

class Cell
{
    public:
        string getStr();

        void setStr(string entered);

        ~Cell();
    private:
        string str = "";
};

ostream& operator<<(ostream& out,Cell &tmp);

#endif