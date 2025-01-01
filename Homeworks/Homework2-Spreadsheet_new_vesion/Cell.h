#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
using namespace std;

namespace spread
{


    class Cell
    {
        public:
            virtual void setCell(const string& in) = 0;  // Make pure virtual
            virtual const string getCell() = 0;          // Make pure virtual
            virtual ~Cell() = 0;                         // Keep pure virtual destructor
            Cell();
    };
}
#endif