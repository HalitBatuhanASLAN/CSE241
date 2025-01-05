#ifndef INTVALUE_H
#define INTVALUE_H

#include"ValueCell.h"
namespace spread
{
    /*derived rom ValueCell class*/
    class IntValue : public ValueCell
    {
        public:
            void setCell(const string& in);
            const string getCell();
        private:
            int int_value;/*attributes to keep int data*/
    };
}
#endif