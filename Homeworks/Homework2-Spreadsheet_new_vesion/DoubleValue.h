#ifndef DOUBLEVALUE_H
#define DOUBLEVALUE_H

#include"ValueCell.h"
namespace spread
{
    /*derived from ValueCell class*/
    class DoubleValue : public ValueCell
    {
        public:
            void setCell(const string& in);
            const string getCell();
        private:
            double double_value;/*to keep double value*/
    };
}
#endif