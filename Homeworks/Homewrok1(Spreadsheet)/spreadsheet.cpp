/*
set floating parts as 2 digits 
*/


#include "Spreadsheet.h"
#include "AnsiTerminal.h"
#include "FormulaParser.h"
#include<iostream>
#include<vector>
#include<string>
/*
    *const for all headers
*/
using namespace std;

Spreadsheet::Spreadsheet(int line = 24,int column = 80)
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


void Spreadsheet::print_frame(AnsiTerminal& terminal)
{
    
    int rowStart = 1;
    int colStart = 1;
    int cellWidth = 10;
    int rowHeight = 1;
    for(int i = 0; i<getLine(); i++)
    {
        for(int j = 0; j<getColumn(); j++)
        {
            string cellData = getFrame(i,j);
            int terminalRow = rowStart + i * rowHeight ;
            int terminalCol = colStart + j * cellWidth ;
            string spaces(cellWidth - static_cast<int>(cellData.size()) - 1,' ');
            if(frame[i][j].get_dt() != Formula)
                terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
            else
            {
                FormulaParser parser(*this);
                /*parser.set_type(i,j);
                //formula_type = parser.get_type(i,j);
                cout << getFrame(i,j);
                cout << parser.get_operand_value(frame[i][j].getCell());*/
                parser.relevant_func();
                //terminal.printAt(terminalRow, terminalCol, "formu" + spaces + '|');
                //terminal.printAt(terminalRow, terminalCol,frame[i][j].getCell() + spaces + '|');
                terminal.printAt(terminalRow, terminalCol,to_string(parser.get_operand_value("B2")) + spaces + '|');
            }    
        }
        cout << endl;
    }
}


Spreadsheet::~Spreadsheet(){}