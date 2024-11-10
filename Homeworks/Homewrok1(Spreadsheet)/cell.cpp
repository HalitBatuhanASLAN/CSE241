/*
    *chech for exceptions like taking inputs
*/


#include"Cell.h"
#include<cstdlib>
#include<sstream>
#include<iostream>
using namespace std;

string Cell::getCell()
{
    return inner_cell;
}

void Cell::setCell(string entered)
{
    inner_cell = entered;
    set_dt();
    if(get_dt() == Formula)
        formula = entered;
    else if(get_dt() == str_type)
        str = entered;
    else
    {
        stringstream ss(str);
        ss >> number;
    }
}

ostream& operator<<(ostream& out,Cell &tmp)
{
    out << tmp.getCell();
    return out;
}

void Cell::set_dt()
{
    if(is_formula())
        dt = Formula;
    else if(is_num())
    {    
        /*last changes happened here*/
        dt = Number;
        string str = getCell();
        double new_num = stod(str);
        setNum(new_num);
    }
    else
        dt = str_type;
}
data_type Cell::get_dt(){return dt;}


bool Cell::is_num()
{
    char* end = nullptr;
    std::strtod(inner_cell.c_str(), &end);
    return (end == inner_cell.c_str() + inner_cell.size());
}
bool Cell::is_formula()
{
    return(inner_cell[0] == '=');
}

void Cell::setNum(double new_num)
{
    number = new_num;
}

double Cell::getNum()
{
    return number;
}

Cell::~Cell(){}







/*
bool is_num(const string& str)
{
    char* end = nullptr;
    std::strtod(str.c_str(), &end);
    return (end == str.c_str() + str.size());
}
bool is_formula(const string& str)
{
    return(str[0] == '=');
}*/