#include "Spreadsheet.h"
#include<iostream>
#include<vector>
#include<string>
/*
    *const for all headers
*/
using namespace std;

Spreadsheet::Spreadsheet(int line,int column)
{
    vector<Cell>line_vec(column);
    for(int i = 0;i<line;i++)
        frame.push_back(line_vec);
}


int Spreadsheet::getLine(){return frame.size();}
int Spreadsheet::getColumn(){return frame[0].size();}

void Spreadsheet::editCell(int line, int column,string value)
{frame[line][column].setCell(value);}
string Spreadsheet::getFrame(int line, int column)
{return frame[line][column].getCell();}


void Spreadsheet::print_frame()
{
    for(int i = 0; i<getLine(); i++)
    {
        for(int j = 0; j<getColumn(); j++)
            cout << frame[i][j] << "|";
        cout << endl;
    }
}


Spreadsheet::~Spreadsheet(){}