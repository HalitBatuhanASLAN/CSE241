#include"FormulaParser.h"
#include"Spreadsheet.h"
#include"Cell.h"

#include<iostream>
#include<string>
using namespace std;

void FormulaParser::set_type(int i,int j)
{
    if(tmp.getFrame(i,j).find("SUM"))
        type = SUM;
    else if(tmp.getFrame(i,j).find("AVER"))
        type = AVER;
    else if(tmp.getFrame(i,j).find("STDDEV"))
        type = STDDEV;
    else if(tmp.getFrame(i,j).find("MAX"))
        type = MAX;
    else if(tmp.getFrame(i,j).find("MIN"))
        type = MIN;
    else
        type = OTHER;
}
formula_type FormulaParser::get_type(int i,int j)
{
    return type;
}

void Sum()
{

}

void FormulaParser::other_calc(int i,int j)
{
    
}