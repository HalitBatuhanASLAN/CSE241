/*
    *chech for exceptions like taking inputs
*/


#include"Cell.h"

#include<iostream>
using namespace std;

string Cell::getStr()   {return str;}

void Cell::setStr(string entered)   {str = entered;}

ostream& operator<<(ostream& out,Cell &tmp)
{
    out << tmp.getStr();
    return out;
}