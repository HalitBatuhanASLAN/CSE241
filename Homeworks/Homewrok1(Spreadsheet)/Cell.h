#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
using namespace std;

enum data_type
{
    Number,
    Formula,
    str_type
};


class Cell
{
    public:
        void set_dt();
        data_type get_dt();

        string getCell();
        void setCell(string entered);


        /*friend bool is_num(const string& str);
        friend bool is_formula(const string& str);*/
        bool is_num();
        bool is_formula();


        friend ostream& operator<<(ostream& out,Cell &tmp);
        ~Cell();
    private:
        data_type dt;
        string formula;
        string str;
        double number;
        string inner_cell;

};
/*bool is_num(const string& str);
bool is_formula(const string& str);*/

ostream& operator<<(ostream& out,Cell &tmp);

#endif