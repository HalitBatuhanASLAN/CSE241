/*
set floating parts as 2 digits 
*/


#include "Spreadsheet.h"
#include "AnsiTerminal.h"

//#include "FormulaParser.h"
#include<sstream>
#include<iomanip>
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
    for(int i = 0;i<line;i++)
    {
        for(int j = 0;j<column;j++)
            frame[i][j].setNum(0);
    }
}


int Spreadsheet::getLine(){return frame.size();}
int Spreadsheet::getColumn(){return frame[0].size();}

/*void Spreadsheet::editCell(int line, int column,string value)
{frame[line][column].setCell(value);}
*/
void Spreadsheet::editCell(int line, int column, string value)
{
    frame[line][column].setCell(value);
}


string Spreadsheet::getFrame(int line, int column)
{return frame[line][column].getCell();}

string getColumnName(int index)
{
    std::string columnName = "";
    while (index >= 0) {
        columnName = char('A' + (index % 26)) + columnName;
        index = index / 26 - 1;
    }
    return columnName;
}

void Spreadsheet::print_frame(AnsiTerminal& terminal, int max_column, int starting_point, int max_line, int starting_row) {
    int rowStart = 1;
    int colStart = 1;
    int cellWidth = 10;
    int rowHeight = 1;

    for (int i = starting_row; i < starting_row + max_line && i < getLine(); i++) {
        if (i >= starting_row + 2) { // Print row numbers only for visible rows
            int space_for_num = (i - starting_row <= 10) ? 8 : 7;
            terminal.printInvertedAt(i - starting_row, 0, to_string(i - 1) + string(space_for_num, ' '));
            terminal.printAt(i - starting_row, to_string(i - 1).size() + space_for_num, "|");
        }

        // Loop through visible columns only, based on starting_point and max_column
        for (int j = starting_point; j < starting_point + max_column && j < getColumn(); j++) {
            if (i == starting_row) {
                // Print column headers
                string alpha = getColumnName(j);
                int terminalCol = colStart + (j - starting_point) * cellWidth + 15; // Adjusted for visible range
                terminal.printInvertedAt(i - starting_row, terminalCol, alpha + "   |");
            }

            string cellData = getFrame(i, j);
            int terminalRow = rowStart + (i - starting_row) * rowHeight + 1;
            int terminalCol = colStart + (j - starting_point) * cellWidth + 10; // Adjusted for visible range

            if (cellData.size() < cellWidth) {
                if (frame[i][j].get_dt() != Formula) {
                    try {
                        double numValue = stod(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str();
                    } catch (const std::invalid_argument&) {
                        // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                } else {
                    FormulaParser pars;
                    *this = pars.parsing(*this, i, j);
                    double formulaResult = frame[i][j].getNum();
                    stringstream stream;
                    stream << fixed << setprecision(2) << formulaResult;
                    int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                    string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                    terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                }
            } else {
                if (frame[i][j].get_dt() != Formula) {
                    try {
                        double numValue = stod(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str();
                    } catch (const std::invalid_argument&) {
                        // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                } else {
                    FormulaParser pars;
                    *this = pars.parsing(*this, i, j);
                    double formulaResult = frame[i][j].getNum();
                    stringstream stream;
                    stream << fixed << setprecision(2) << formulaResult;
                    int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                    string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                    terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                }
            }
        }
    }
}




/*gadasını aldığım çözümü*/
/*void Spreadsheet::print_frame(AnsiTerminal& terminal, int max_column, int starting_point, int max_line, int starting_row) {
    int rowStart = 1;
    int colStart = 1;
    int cellWidth = 10;
    int rowHeight = 1;

    for (int i = starting_row; i < max_line; i++) {
        if (i > 1) {
            int space_for_num = (i <= 10) ? 8 : 7;
            terminal.printInvertedAt(i, 0, to_string(i - 1) + string(space_for_num, ' '));
            terminal.printAt(i, to_string(i - 1).size() + space_for_num, "|");
        }

        // Loop through visible columns only, based on starting_point and max_column
        for (int j = starting_point; j < starting_point + max_column && j < getColumn(); j++) {
            if (i == starting_point) {
                // Print column headers
                string alpha = getColumnName(j);
                int terminalCol = colStart + (j - starting_point) * cellWidth + 15; // Adjusted for visible range
                terminal.printInvertedAt(i, terminalCol, alpha + "   |");
            }

            string cellData = getFrame(i, j);
            int terminalRow = rowStart + (i - starting_row) * rowHeight + 1;
            int terminalCol = colStart + (j - starting_point) * cellWidth + 10; // Adjusted for visible range

            if (cellData.size() < cellWidth) {
                if (frame[i][j].get_dt() != Formula) {
                    try {
                        double numValue = stod(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str(); // Format the number to 2 decimal places
                    } catch (const std::invalid_argument&) {
                        // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                } else {
                    FormulaParser pars;
                    *this = pars.parsing(*this, i, j);
                    double formulaResult = frame[i][j].getNum();
                    stringstream stream;
                    stream << fixed << setprecision(2) << formulaResult;
                    int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                    string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                    terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                }
            } else {
                if (frame[i][j].get_dt() != Formula) {
                    try {
                        double numValue = stod(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str(); // Format the number to 2 decimal places
                    } catch (const std::invalid_argument&) {
                        // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                } else {
                    FormulaParser pars;
                    *this = pars.parsing(*this, i, j);
                    double formulaResult = frame[i][j].getNum();
                    stringstream stream;
                    stream << fixed << setprecision(2) << formulaResult;
                    int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                    string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                    terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                }
            }
        }
    }
}
*/



/*
void Spreadsheet::print_frame(AnsiTerminal& terminal)
{
    
    int rowStart = 1;
    int colStart = 1;
    int cellWidth = 10;
    int rowHeight = 1;
    
  
    for(int i = 0; i<getLine(); i++)
    {
        if(i>1)
        {
            int space_for_num = (i<=10) ? 8 : 7;
            terminal.printInvertedAt(i,0,to_string(i-1) + string(space_for_num ,' '));
            terminal.printAt(i,to_string(i-1).size() + space_for_num,"|");
        }
        for(int j = 0; j<getColumn(); j++)
        {
            if (i == 0 && j != 0)
            {
                string alpha = getColumnName(j-1);
                int terminalCol = colStart + (j-1) * cellWidth + 15;
                terminal.printInvertedAt(i,terminalCol, alpha + "   |");
            }
            string cellData = getFrame(i,j);
            int terminalRow = rowStart + i * rowHeight +1;
            int terminalCol = colStart + j * cellWidth +10;
            if(cellData.size() < cellWidth)
            {
                if(frame[i][j].get_dt() != Formula)
                {    
                    try {
                    double numValue = stod(cellData);
                    stringstream stream;
                    stream << fixed << setprecision(2) << numValue;
                    cellData = stream.str(); // Format the number to 2 decimal places
                    } 
                    catch (const std::invalid_argument&) {
                    // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1,' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                }
                else
                {
                    FormulaParser pars;
                    *this = pars.parsing(*this,i,j);
                    double formulaResult = frame[i][j].getNum();
                    stringstream stream;
                    stream << fixed << setprecision(2) << formulaResult;
                    int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                    string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                    terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                    //terminal.printAt(terminalRow, terminalCol, stream.str());
                }
            }
            else
            {
                if(frame[i][j].get_dt() != Formula)
                {    
                    try {
                    double numValue = stod(cellData);
                    stringstream stream;
                    stream << fixed << setprecision(2) << numValue;
                    cellData = stream.str(); // Format the number to 2 decimal places
                    } 
                    catch (const std::invalid_argument&) {
                    // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1,' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                }
                else
                {
                    FormulaParser pars;
                    *this = pars.parsing(*this,i,j);
                    double formulaResult = frame[i][j].getNum();
                    stringstream stream;
                    stream << fixed << setprecision(2) << formulaResult;
                    int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                    string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                    terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                    //terminal.printAt(terminalRow, terminalCol, stream.str());
                }
            }
        }
    }
    
}*/

void Spreadsheet::set_num(int i,int j, double new_num)
{
    frame[i][j].setNum(new_num);
}

Spreadsheet::~Spreadsheet(){}