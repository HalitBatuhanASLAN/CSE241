#ifndef VALUECELL_H
#define VALUECELL_H

#include"Cell.h"
#include<iostream>
#include<string>
using namespace std;
namespace spread
{
    class ValueCell: public Cell
    {
        public:
            void setCell(const string& in);
            const string getCell();
        private:
            string tmp_value;
    };
}
#endif