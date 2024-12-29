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
#include<typeinfo>

using namespace std;
using namespace spread;
// Constructor to initialize the spreadsheet with given dimensions (rows and columns)
namespace spread
{
    
   Spreadsheet::Spreadsheet(int line, int column)
    : line(line), column(column)
{
    frame = std::make_unique<std::unique_ptr<std::shared_ptr<Cell>[]>[]>(line);

    for (int i = 0; i < line; ++i) {
        frame[i] = std::make_unique<std::shared_ptr<Cell>[]>(column);

        for (int j = 0; j < column; ++j) {
            frame[i][j] = nullptr;
        }
    }
}

Spreadsheet::Spreadsheet(const Spreadsheet& other)
    : line(other.line), column(other.column)
{
    frame = std::make_unique<std::unique_ptr<std::shared_ptr<Cell>[]>[]>(line);

    for (int i = 0; i < line; ++i) {
        frame[i] = std::make_unique<std::shared_ptr<Cell>[]>(column);

        for (int j = 0; j < column; ++j) {
            frame[i][j] = other.frame[i][j];
        }
    }
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& other)
{
    if (this == &other)
        return *this;

    auto newFrame = std::make_unique<std::unique_ptr<std::shared_ptr<Cell>[]>[]>(other.line);

    for (int i = 0; i < other.line; ++i) {
        newFrame[i] = std::make_unique<std::shared_ptr<Cell>[]>(other.column);

        for (int j = 0; j < other.column; ++j) {
            newFrame[i][j] = other.frame[i][j];
        }
    }

    line = other.line;
    column = other.column;
    frame = std::move(newFrame);

    return *this;
}

int Spreadsheet::getLine() const { return line; }
int Spreadsheet::getColumn() const { return column; }

void Spreadsheet::editCell(int row, int col, const std::string value)
{
    frame[row][col] = std::make_shared<StringValue>();
    frame[row][col]->setCell(value);
    return;
    if (row < 0 || row >= line || col < 0 || col >= column) {
        throw std::out_of_range("Cell index out of bounds");
    }

    if (value.empty()) {
        frame[row][col] = nullptr;
        return;
    }

    if (value[0] == '=') {
        // Handle formula cell
        frame[row][col] = std::make_shared<FormulaCell>();
        frame[row][col]->setCell(value);
    } 
    else {
        try {
            // Try to parse as integer
            int intVal = std::stoi(value);
            frame[row][col] = std::make_shared<IntValue>();
            frame[row][col]->setCell(value);
        }
        catch (const std::invalid_argument&) {
            try {
                // Try to parse as double
                double doubleVal = std::stod(value);
                frame[row][col] = std::make_shared<DoubleValue>();
                frame[row][col]->setCell(value);
            }
            catch (const std::invalid_argument&) {
                // If not a number, treat as string
                frame[row][col] = std::make_shared<StringValue>();
                frame[row][col]->setCell(value);
            }
        }
    }
}


/*void Spreadsheet::editCell(int row, int col, const std::string value)
{
    frame[5][7] = make_shared<StringValue>();
    //frame[5][7]->setCell("123");

    /*if (row < 0 || row >= line || col < 0 || col >= column) {
        throw std::out_of_range("Cell index out of bounds");
    }

    if (value.empty()) {
        frame[row][col] = nullptr; // Clear the cell if the value is empty
        return;
    }

    if (value[0] == '=') {
        // FormulaCell
        frame[row][col] = std::make_shared<FormulaCell>();
    } else {
        try {
            // Try to parse as an integer
            std::stoi(value);
            frame[row][col] = std::make_shared<IntValue>();
        } catch (const std::invalid_argument&) {
            try {
                // Try to parse as a double
                std::stod(value);
                frame[row][col] = std::make_shared<DoubleValue>();
            } catch (const std::invalid_argument&) {
                // If neither, treat it as a string
                frame[row][col] = std::make_shared<StringValue>();
            }
        }
    }

    // Set the value in the cell
    frame[row][col]->setCell(value);

}*/
    // Retrieves the content of a specific cell in the spreadsheet
    /*string Spreadsheet::getFrame(int line, int column)
    {return frame[line][column]->getCell();}*/

    string Spreadsheet::getFrame(int line, int column)
{
    if (line < 0 || line >= this->line || column < 0 || column >= this->column)
        throw std::out_of_range("Cell index out of bounds");
        
    if (frame[line][column] == nullptr)
        return "a";
        
    return "abc";
    return frame[line][column]->getCell();
}


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
    /*void Spreadsheet::print_frame(AnsiTerminal& terminal, int max_column, int starting_point, int max_line, int starting_row)
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
            else
            {
                int terminalRow = rowStart + (i - starting_row) * rowHeight + 1;
                int terminalCol = colStart + (j - starting_point) * cellWidth + 10; // Adjusted for visible range

                if(frame[i][j] != nullptr)
                { 
                string cellData = getFrame(i, j);
               
                if(cellData.size() < cellWidth)
                {
                    if(typeid(frame[i][j]).name() == "StringCell")
                    {
                        string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                        terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                    }
                    else if(typeid(frame[i][j]).name() == "IntCell")
                    {
                        int numValue = stoi(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str();
                    }
                    else if(typeid(frame[i][j]).name() == "DoubleCell")
                    {
                        double numValue = stod(cellData);
                        stringstream stream;
                        stream << fixed << setprecision(2) << numValue;
                        cellData = stream.str();
                        string spaces(cellWidth - static_cast<int>(cellData.size()) - 1, ' ');
                        terminal.printAt(terminalRow, terminalCol, cellData + spaces + '|');
                    }
                    else
                    {
                        formulaParsing::FormulaParser pars;
                        *this = pars.parsing(*this, i, j);
                        double formulaResult = stod(frame[i][j]->getCell());
                        stringstream stream;
                        stream << fixed << setprecision(2) << formulaResult;
                        int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                        string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                        terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                    }
                }
                else
                {
                    if(typeid(frame[i][j]).name() != "FormulaCell")
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
                        double formulaResult = stod(frame[i][j]->getCell());
                        stringstream stream;
                        stream << fixed << setprecision(2) << formulaResult;
                        int spaceCount = cellWidth - static_cast<int>(stream.str().size()) - 1;
                        string spaces(spaceCount > 0 ? spaceCount : 0, ' ');
                        terminal.printAt(terminalRow, terminalCol, stream.str() + spaces + '|');
                    }
                }
                }
                else
                    terminal.printAt(terminalRow,terminalCol,"        |");
            }
            }
        }
    }
*/

void Spreadsheet::print_frame(AnsiTerminal& terminal, int max_column, int starting_point, int max_line, int starting_row)
{
    int rowStart = 1;
    int colStart = 1;
    int cellWidth = 10;
    int rowHeight = 1;

    for(int i = starting_row; i < starting_row + max_line && i < getLine(); i++)
    {
        if(i >= starting_row + 2)
        {
            int space_for_num = (i - starting_row <= 10) ? 8 : 7;
            terminal.printInvertedAt(i - starting_row, 0, to_string(i - 1) + string(space_for_num, ' '));
            terminal.printAt(i - starting_row, to_string(i - 1).size() + space_for_num, "|");
        }

        for(int j = starting_point; j < starting_point + max_column && j < getColumn(); j++)
        {
            if(i == starting_row)
            {
                string alpha = getColumnName(j);
                int terminalCol = colStart + (j - starting_point) * cellWidth + 15;
                terminal.printInvertedAt(i - starting_row, terminalCol, alpha + "   |");
            }
            else
            {
                int terminalRow = rowStart + (i - starting_row) * rowHeight + 1;
                int terminalCol = colStart + (j - starting_point) * cellWidth + 10;

                // Add null check before accessing cell
                if(frame[i][j] != nullptr)
                {
                    string cellData = frame[i][j]->getCell();
                    
                    if(!cellData.empty())  // Check if cellData is not empty
                    {
                        if(cellData.size() < cellWidth)
                        {
                            string spaces(cellWidth - cellData.size() - 1, ' ');
                            terminal.printAt(terminalRow, terminalCol, cellData + spaces + "|");
                        }
                        else
                        {
                            string truncated = cellData.substr(0, cellWidth - 1);
                            terminal.printAt(terminalRow, terminalCol, truncated + "|");
                        }
                    }
                    else
                    {
                        // Print empty cell
                        terminal.printAt(terminalRow, terminalCol, string(cellWidth - 1, ' ') + "|");
                    }
                }
                else
                {
                    // Print empty cell
                    terminal.printAt(terminalRow, terminalCol, string(cellWidth - 1, ' ') + "|");
                }
            }
        }
    }
}


    // Sets a numeric value to a specific cell in the spreadsheet
    void Spreadsheet::set_num(int i, int j, double new_num)
    {frame[i][j]->setCell(to_string(new_num));}

    // Destructor to clean up resources used by the spreadsheet
    Spreadsheet::~Spreadsheet() {}
}



/*Spreadsheet::Spreadsheet(int line = 24, int column = 20):line(line),column(column),
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

    }*/