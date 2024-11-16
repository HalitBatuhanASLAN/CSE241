/*
set floating parts as 2 digits 
*/


#include "Spreadsheet.h"
#include "AnsiTerminal.h"

//#include "FormulaParser.h"

#include"new_formula.h"
#include<iostream>
#include<vector>
#include<string>
/*
    *const for all headers
*/
using namespace std;
string alphabet = "ABCDEFGHIJ";
Spreadsheet::Spreadsheet(int line = 24,int column = 20)
{
    vector<Cell>line_vec(column);
    for(int i = 0;i<line;i++)
        frame.push_back(line_vec);
}


int Spreadsheet::getLine(){return frame.size();}
int Spreadsheet::getColumn(){return frame[0].size();}

/*void Spreadsheet::editCell(int line, int column,string value)
{frame[line][column].setCell(value);}
*/
void Spreadsheet::editCell(int line, int column, string value) {
    frame[line][column].setCell(value);
/*    if (frame[line][column].get_dt() == Formula) {
        FormulaParser parser(*this);
        parser.set_type(line, column);
        parser.relevant_func(line, column);
    }*/
}


string Spreadsheet::getFrame(int line, int column)
{return frame[line][column].getCell();}


void Spreadsheet::print_frame(AnsiTerminal& terminal)
{
    
    int rowStart = 1;
    int colStart = 1;
    int cellWidth = 10;
    int rowHeight = 1;
    
    for(int i = 0; i<24; i++)
    {
        if(i>1)
        {
            int space_for_num = (i<10) ? 8 : 7;
            terminal.printAt(i,0,to_string(i-1) + string(space_for_num ,' ') + '|');
        }
        for(int j = 0; j<19; j++)
        {
            if (i == 0 && j != 0)
            {
                string alpha(1, alphabet[j - 1]);
                int terminalCol = colStart + (j-1) * cellWidth + 15;
                terminal.printAt(i,terminalCol, alpha + "   |");
            }
            string cellData = getFrame(i,j);
            int terminalRow = rowStart + i * rowHeight +1;
            int terminalCol = colStart + j * cellWidth +10;
            if(cellData.size() < cellWidth)
            {
                string spaces(cellWidth - static_cast<int>(cellData.size()) - 1,' ');
                if(frame[i][j].get_dt() != Formula)
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                else
                {
                    //FormulaParser parser(*this);
                    //parser.set_type(i,j);
                    //parser.relevant_func(i,j);
                    FormulaParser pars;
                    *this = pars.parsing(*this,i,j);
                    //terminal.printAt(terminalRow, terminalCol, "For" + spaces + '|');
                    terminal.printAt(terminalRow, terminalCol,to_string(frame[i][j].getNum()));
                }
            }
            else
            {
                string sub = cellData.substr(0,9);
                if(frame[i][j].get_dt() != Formula)
                    terminal.printAt(terminalRow, terminalCol, sub + '|');
                else
                {
                    //FormulaParser parser(*this);
                    //parser.set_type(i,j);
                    //parser.relevant_func(i,j);
                    FormulaParser pars;
                    *this = pars.parsing(*this,i,j);
                    terminal.printAt(terminalRow, terminalCol,to_string(frame[i][j].getNum()));
                }
            }
        }
    }
    
}

void Spreadsheet::set_num(int i,int j, double new_num)
{
    frame[i][j].setNum(new_num);
}

Spreadsheet::~Spreadsheet(){}