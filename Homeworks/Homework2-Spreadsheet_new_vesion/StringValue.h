#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include"ValueCell.h"
namespace spread
{
    /*inherit from ValueCell class*/
    class StringValue : public ValueCell
    {
        public:
            void setCell(const string& in);
            const string getCell();
        private:
            string str_value;/*attribute to keep string data*/
    };
}
#endif