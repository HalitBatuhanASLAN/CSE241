#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include "Cell.h"
#include <iostream>
#include <vector>
#include "AnsiTerminal.h"
using namespace std;
#include<memory>
// Forward declaration for FormulaParser class
class FormulaParser;

// Class representing a spreadsheet consisting of rows and columns of cells
namespace spread
{
    class Spreadsheet
    {
        public:
            // Constructor to initialize a spreadsheet with the specified number of rows and columns
            Spreadsheet(int line, int column);

            Spreadsheet(const Spreadsheet& other);

            Spreadsheet& operator=(const Spreadsheet& other);


            // Returns the number of rows (lines) in the spreadsheet
            int getLine()const;

            // Returns the number of columns in the spreadsheet
            int getColumn()const;

            // Prints the spreadsheet frame to the terminal
            // Parameters:
            // - terminal: Reference to an AnsiTerminal object for output
            // - max_column: Maximum number of columns to display
            // - starting_point: Starting column index for display
            // - max_line: Maximum number of rows to display
            // - starting_row: Starting row index for display
            void print_frame(AnsiTerminal& terminal, int max_column, int starting_point, int max_line, int starting_row);

            // Edits the value of a specific cell in the spreadsheet
            // Parameters:
            // - line: Row index of the cell
            // - column: Column index of the cell
            // - value: New value to be set in the cell
            void editCell(int line, int column, string value);

            // Sets a numeric value for a specific cell in the spreadsheet
            // Parameters:
            // - i: Row index of the cell
            // - j: Column index of the cell
            // - new_num: Numeric value to be set
            void set_num(int i, int j, double new_num);

            double get_num(int i, int j);

            // Retrieves the value of a specific cell in the spreadsheet as a string
            // Parameters:
            // - line: Row index of the cell
            // - column: Column index of the cell
            string getFrame(int line, int column);

            // Destructor to clean up resources used by the spreadsheet
            ~Spreadsheet();
            //std::unique_ptr<std::unique_ptr<std::shared_ptr<Cell>[]>[]> frame;
        private:
            // A 2D vector to store the cells in the spreadsheet
            std::unique_ptr<std::unique_ptr<std::shared_ptr<Cell>[]>[]> frame;
            int line;
            int column;
    };
}
#endif