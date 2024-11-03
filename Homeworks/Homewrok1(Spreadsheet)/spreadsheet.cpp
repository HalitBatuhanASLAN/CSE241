#include "Spreadsheet.h"
#include<iostream>
#include<vector>
#include<string>
/*
    *const for all headers
*/
using namespace std;

int Spreadsheet::getLine(){return frame.size();}
int Spreadsheet::getColumn(){return frame[0].size();}

void Spreadsheet::editCell(int line, int column,string value)
{frame[line][column].setStr(value);}
string Spreadsheet::getCell(int line, int column)
{return frame[line][column].getStr();}


void Spreadsheet::print_frame()
{
    for(int i = 0; i<getLine(); i++)
    {
        for(int j = 0; j<getColumn(); j++)
            cout << frame[i][j] << "|";
        cout << endl;
    }
}