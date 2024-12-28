#include "Spreadsheet.h"
#include "AnsiTerminal.h"
#include <sstream>
#include <iomanip>
#include "new_formula.h"           /********************big5 eklenecek************ */
#include <iostream>
#include <vector>
#include <string>
#include<memory>
#include"FormulaCell.h"
#include"IntValue.h"
#include"DoubleValue.h"
#include"StringValue.h"

using namespace std;
using namespace spread;
// Constructor to initialize the spreadsheet with given dimensions (rows and columns)
namespace spread
{
    Spreadsheet::Spreadsheet(int line = 24, int column = 20):line(line),column(column),
    frame(std::make_shared<std::shared_ptr<shared_ptr<Cell>[]>[]>(line))
    {
        for (int i = 0; i < line; i++)
            frame[i] = make_shared<shared_ptr<Cell>[]>();
    }

    Spreadsheet::Spreadsheet(const Spreadsheet& other)
    : line(other.line), column(other.column), frame(std::make_shared<std::shared_ptr<shared_ptr<Cell>[]>[]>(other.line))
    {
        for (int i = 0; i < line; i++)
        {
            frame[i] = std::make_shared<shared_ptr<Cell>[]>(column);
            for (int j = 0; j < column; ++j)
                frame[i][j] = other.frame[i][j];
        }
    }

    Spreadsheet& Spreadsheet::operator=(const Spreadsheet& other)
    {
        if (this == &other)
            return *this;
        
        frame.reset();
        
        line = other.line;
        column = other.column;

        frame = std::make_shared<std::shared_ptr<shared_ptr<Cell>[]>[]>(line);
        for (int i = 0; i < line; ++i)
        {
            frame[i] = std::make_shared<shared_ptr<Cell>[]>(column);
            for (int j = 0; j < column; ++j)
                frame[i][j] = other.frame[i][j];
        }
        return *this;
    }


    // Returns the number of rows in the spreadsheet
    int Spreadsheet::getLine(){return line;}
    int Spreadsheet::getColumn() { return column;}

    // Edits the value of a specific cell in the spreadsheet
    void Spreadsheet::editCell(int line, int column, string value)
    {
        if(value[0] == '=')
        {
            frame[line][column] = make_shared<FormulaCell>();
            frame[line][column]->setCell(value);
        }
        else
        {
            try
            {
                stoi(value);
                frame[line][column] = make_shared<IntValue>();
                frame[line][column]->setCell(value);
            }
            catch(...)
            {
                try
                {
                    stod(value);
                    frame[line][column] = make_shared<DoubleValue>();
                    frame[line][column]->setCell(value);

                }
                catch(...)
                {
                    frame[line][column] = make_shared<StringValue>();
                    frame[line][column]->setCell(value);                
                }
                
            }
            
        }

    }

    // Retrieves the content of a specific cell in the spreadsheet
    string Spreadsheet::getFrame(int line, int column)
    {return frame[line][column]->getCell();}

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
                        formulaParsing::FormulaParser pars;
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
                        string tmp = cellData.substr(0,9);
                        terminal.printAt(terminalRow, terminalCol, tmp + '|');
                    }
                    else
                    {
                        formulaParsing::FormulaParser pars;
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
}