#include "Spreadsheet.h"
#include "AnsiTerminal.h"
#include <sstream>
#include <iomanip>
#include "new_formula.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constructor to initialize the spreadsheet with given dimensions (rows and columns)
Spreadsheet::Spreadsheet(int line = 24, int column = 20)
{
    vector<Cell> line_vec(column); // Create a row of cells with specified column size
    for (int i = 0; i < line; i++)
        frame.push_back(line_vec); // Add rows to the frame
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < column; j++)
            frame[i][j].setNum(0); // Initialize each cell with 0
    }
}

// Returns the number of rows in the spreadsheet
int Spreadsheet::getLine() { return frame.size(); }

// Returns the number of columns in the spreadsheet
int Spreadsheet::getColumn() { return frame[0].size(); }

// Edits the value of a specific cell in the spreadsheet
void Spreadsheet::editCell(int line, int column, string value)
{frame[line][column].setCell(value);}

// Retrieves the content of a specific cell in the spreadsheet
string Spreadsheet::getFrame(int line, int column)
{return frame[line][column].getCell();}

// Utility function to convert a column index into a column name (e.g., 0 -> "A", 27 -> "AA")
string getColumnName(int index)
{
    string columnName = "";
    while (index >= 0)
    {
        columnName = char('A' + (index % 26)) + columnName;
        index = index / 26 - 1;
    }
    return columnName;
}

// Prints the spreadsheet frame to the terminal with formatting
void Spreadsheet::print_frame(AnsiTerminal& terminal, int max_column, int starting_point, int max_line, int starting_row)
{
    int rowStart = 1;
    int colStart = 1;
    int cellWidth = 10; // Width of each cell
    int rowHeight = 1;  // Height of each row

    for(int i = starting_row; i < starting_row + max_line && i < getLine(); i++)
    {
        if(i >= starting_row + 2)
        { // Print row numbers only for visible rows
            int space_for_num = (i - starting_row <= 10) ? 8 : 7;
            terminal.printInvertedAt(i - starting_row, 0, to_string(i - 1) + string(space_for_num, ' '));
            terminal.printAt(i - starting_row, to_string(i - 1).size() + space_for_num, "|");
        }

        // Loop through visible columns only, based on starting_point and max_column
        for(int j = starting_point; j < starting_point + max_column && j < getColumn(); j++)
        {
            if(i == starting_row)
            {
                // Print column headers
                string alpha = getColumnName(j);
                int terminalCol = colStart + (j - starting_point) * cellWidth + 15; // Adjusted for visible range
                terminal.printInvertedAt(i - starting_row, terminalCol, alpha + "   |");
            }

            string cellData = getFrame(i, j);
            int terminalRow = rowStart + (i - starting_row) * rowHeight + 1;
            int terminalCol = colStart + (j - starting_point) * cellWidth + 10; // Adjusted for visible range

            if(cellData.size() < cellWidth)
            {
                if(frame[i][j].get_dt() != Formula)
                {
                    try
                    {
                        double numValue = stod(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str();
                    }
                    catch(const invalid_argument&) {
                        // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                }
                else
                {
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
            else
            {
                if(frame[i][j].get_dt() != Formula)
                {
                    try
                    {
                        double numValue = stod(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str();
                    }
                    catch (const invalid_argument&) {
                        // Not a number; keep cellData unchanged
                    }
                    string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                    terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                }
                else
                {
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

// Sets a numeric value to a specific cell in the spreadsheet
void Spreadsheet::set_num(int i, int j, double new_num)
{frame[i][j].setNum(new_num);}

// Destructor to clean up resources used by the spreadsheet
Spreadsheet::~Spreadsheet() {}