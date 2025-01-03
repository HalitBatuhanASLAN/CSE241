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
#include<algorithm>

using namespace std;
using namespace spread;
// Constructor to initialize the spreadsheet with given dimensions (rows and columns)
namespace spread
{

    Spreadsheet::Spreadsheet(int line, int column): line(line), column(column)
    {
        frame = std::make_unique<std::unique_ptr<std::shared_ptr<Cell>[]>[]>(line);

        for (int i = 0; i < line; ++i) {
            frame[i] = std::make_unique<std::shared_ptr<Cell>[]>(column);

            for (int j = 0; j < column; ++j) {
                frame[i][j] = nullptr;
            }
        }
    }

    Spreadsheet::Spreadsheet(const Spreadsheet& other):line(other.line), column(other.column)
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
        /*frame[row][col] = std::make_shared<StringValue>();
        frame[row][col]->setCell(value);
        return;*/
        if (row < 0 || row >= line || col < 0 || col >= column) {
            throw std::out_of_range("Cell index out of bounds");
        }

        if (value.empty()) {
            frame[row][col] = nullptr;
            return;
        }

        if (value[0] == '=') {
            // Handle formula cell
            frame[row][col] = std::make_shared<FormulaCell<double>>();
            frame[row][col]->setCell(value);
        } 
        else {
            //use typeid for double, string instead of try-catch stoi-d ...
            try {
                // Try to parse as integer
                int intVal = std::stoi(value);
                double doubleValue = stod(value);
                if(intVal - doubleValue == 0.000000)
                    frame[row][col] = std::make_shared<IntValue>();
                else
                    frame[row][col] = std::make_shared<DoubleValue>();
                frame[row][col]->setCell(value);
            }
            catch (const std::invalid_argument&)
            {
                    frame[row][col] = std::make_shared<StringValue>();
                    frame[row][col]->setCell(value);    
            }
        }
    }



    string Spreadsheet::getFrame(int line, int column)
    {
        if (line < 0 || line >= this->line || column < 0 || column >= this->column)
            throw std::out_of_range("Cell index out of bounds");

        if (frame[line][column] == nullptr)
            return "";

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

                    if(frame[i][j] != nullptr)
                    {
                        try {
                            string cellData = frame[i][j]->getCell();
                            string displayValue;


                            if(typeid(*frame[i][j]).name() == typeid(StringValue).name())
                            {
                                displayValue = cellData;
                            }
                            else if(typeid(*frame[i][j]).name() == typeid(IntValue).name())
                            {
                                try {
                                    int num_int = stod(cellData);
                                    stringstream stream;
                                    stream << num_int;
                                    displayValue = stream.str();
                                } catch (...) {
                                    displayValue = cellData;
                                }
                            }
                            else if(typeid(*frame[i][j]).name() == typeid(DoubleValue).name())
                            {
                                try {
                                    double doubleValue = stod(cellData);
                                    stringstream stream;
                                    stream << fixed << setprecision(2) << doubleValue;
                                    displayValue = stream.str();
                                } catch (...) {
                                    displayValue = cellData;
                                }
                            }
                            else if(typeid(*frame[i][j]).name() == typeid(FormulaCell<double>).name() 
                                    || typeid(*frame[i][j]).name() == typeid(FormulaCell<int>).name())
                            {
                                try {
                                    displayValue = frame[i][j]->getCell();
                                    formulaParsing::FormulaParser pars;
                                    *this = pars.parsing(*this, i, j);
                                    string result = frame[i][j]->getCell();

                                    frame[i][j]->setCell(displayValue);
                                    //displayValue = result;

                                    double numValue = stod(result);
                                    int int_num = stoi(result);
                                    stringstream stream;
                                    /*if(numValue - int_num == 0.000000)
                                        stream << int_num;
                                    else
                                        stream << fixed << setprecision(2) << numValue;*/
                                    if(numValue - int_num != 0.00)
                                    {
                                        stream << fixed << setprecision(2) << numValue;
                                        auto doubleFormulaCell = make_shared<FormulaCell<double>>();
                                        doubleFormulaCell->setValue(numValue);
                                        doubleFormulaCell->setCell(displayValue);
                                        frame[i][j] = doubleFormulaCell;
                                    }
                                    else
                                    {
                                        stream << int_num;
                                        auto intFormulaCell = make_shared<FormulaCell<int>>();
                                        intFormulaCell->setValue(int_num);
                                        intFormulaCell->setCell(displayValue);
                                        frame[i][j] = intFormulaCell;
                                    }
                                    displayValue = stream.str();
                                } catch (...) {
                                    displayValue = frame[i][j]->getCell();
                                }
                            }
                            else
                            {
                                displayValue = cellData;
                            }


                            // Truncate or pad the display value
                            if(displayValue.size() >= cellWidth)
                            {
                                displayValue = displayValue.substr(0, cellWidth - 1);
                                terminal.printAt(terminalRow, terminalCol, displayValue + "|");
                            }
                            else
                            {
                                string spaces(cellWidth - displayValue.size() - 1, ' ');
                                terminal.printAt(terminalRow, terminalCol, displayValue + spaces + "|");
                            }
                        }
                        catch (...) {
                            terminal.printAt(terminalRow, terminalCol, string(cellWidth - 1, ' ') + "|");
                        }
                    }
                    else
                    {
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

                            // Handle different cell types
                            /*if(dynamic_cast<StringValue*>(frame[i][j].get()) != nullptr)
                            {
                                displayValue = cellData;
                            }
                            else if(dynamic_cast<IntValue*>(frame[i][j].get()) != nullptr || 
                                    dynamic_cast<DoubleValue*>(frame[i][j].get()) != nullptr)
                            {
                                try {
                                    double numValue = stod(cellData);
                                    int num_int = stod(cellData);
                                    stringstream stream;
                                    if(numValue - num_int == 0.00000)
                                        stream << num_int;
                                    else
                                        stream << fixed << setprecision(2) << numValue;
                                    displayValue = stream.str();
                                } catch (...) {
                                    displayValue = cellData;
                                }
                            }
                            else if(dynamic_cast<FormulaCell*>(frame[i][j].get()) != nullptr)
                            {
                                try {
                                    displayValue = frame[i][j]->getCell();
                                    formulaParsing::FormulaParser pars;
                                    *this = pars.parsing(*this, i, j);
                                    string result = frame[i][j]->getCell();

                                    frame[i][j]->setCell(displayValue);
                                    //displayValue = result;

                                    double numValue = stod(result);
                                    int int_num = stoi(result);
                                    stringstream stream;
                                    if(numValue - int_num == 0.000000)
                                        stream << int_num;
                                    else
                                        stream << fixed << setprecision(2) << numValue;
                                    displayValue = stream.str();
                                } catch (...) {
                                    displayValue = frame[i][j]->getCell();
                                }
                            }
                            else
                            {
                                displayValue = cellData;
                            }*/
