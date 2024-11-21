#include <iostream>
#include "FileManager.h"
#include "Spreadsheet.h"
#include "Cell.h"
#include "AnsiTerminal.h"
#include<sstream>
#include<iomanip>
using namespace std;
string COLUMN_ALPHABET_MAIN = "ABCDEFGHIJ";

void printMenu(AnsiTerminal &terminal,int line) {
    int menuRow = line + 4 ; // Print menu starting at row 28, below the input prompt
    terminal.printAt(menuRow++, 0, "    Commands:");
    terminal.printAt(menuRow++, 0, " - Enter '0' to input data into the current cell");
    terminal.printAt(menuRow++, 0, " - Use 'U', 'D', 'L', 'R' or arrow keys to navigate Up, Down, Left, Right");
    terminal.printAt(menuRow++, 0, " - Enter 'f' to load data from a file");
    terminal.printAt(menuRow++, 0, " - Enter 's' to save data to a file");
    terminal.printAt(menuRow++, 0, " - Enter 'q' to quit the program");
    terminal.printAt(menuRow++, 0, "    Functions:");
    terminal.printAt(menuRow++, 0, " - '=SUM(A1..B3)' to sum of values in rectangle formed by A1 and B3");
    terminal.printAt(menuRow++, 0, " - '=AVER(A1..B3)' to average of values in rectangle formed by A1 and B3");
    terminal.printAt(menuRow++, 0, " - '=STDDIV(A1..B3)' to standard derivation of values in rectangle formed by A1 and B3");
    terminal.printAt(menuRow++, 0, " - '=MAX(A1..B3)' to find maximum value in rectangle formed by A1 and B3");
    terminal.printAt(menuRow++, 0, " - '=MIN(A1..B3)' to find minimum value in rectangle formed by A1 and B3");
    terminal.printInvertedAt(menuRow++, 0, "");
}

string getColumnLabel(int columnIndex)
{
    string columnLabel = "";
    while (columnIndex >= 0) {
        columnLabel = char('A' + (columnIndex % 26)) + columnLabel;
        columnIndex = columnIndex / 26 - 1;
    }
    return columnLabel;
}

int main()
{
    File fileManager;
    Spreadsheet spreadsheet(15,25);
    string filename;

    AnsiTerminal terminal;
    terminal.clearScreen();

    const int cellWidth = 10;
    int row = 2, col = 10; // Start at cell A1, considering headers
    terminal.printAt(row, col, "*");

    string input;
    char key;

    int starting = 0;
    while (true) {
        terminal.clearScreen();

        // 1. Display the current cell information at the top of the terminal
        int cellRow = (row - 2); // Adjusted for actual row index, skipping header rows
        int cellCol = (col / cellWidth) - 1; // Adjusted for actual column index
        if (cellRow >= 0 && cellCol >= 0 && cellCol < spreadsheet.getColumn())
        {
            string columnLabel = getColumnLabel(cellCol);
            string currentCell = "CELL: " + columnLabel + to_string(cellRow + 1);
            terminal.printInvertedAt(0, 0, currentCell); // Place "CELL: ..." at the top
        }

        // 2. Display the spreadsheet from the third line onwards, no overlap with "CELL: ..."
        spreadsheet.print_frame(terminal);

        // 3. Display the input prompt at the bottom of the terminal
        string cellValue = spreadsheet.getFrame(cellRow, cellCol);
        if (cellRow >= 0 && cellRow < spreadsheet.getLine() && cellCol >= 0 && cellCol < spreadsheet.getColumn() && !cellValue.empty())
        {
            try {
                double numValue = stod(cellValue);
                stringstream stream;
                stream << fixed << setprecision(2) << numValue;
                input = stream.str();
            } catch (const std::invalid_argument&) {
                input = cellValue; // Not a number, use as string
            }
        }
        else
        {
            input.clear();
        }
        string inputPrompt = "Input: " + input;
        terminal.printAt(spreadsheet.getLine()+3, 0, inputPrompt); // Assuming a total of 27 rows in the terminal (0-based index)

        // 4. Display the current selection marker
        terminal.printInvertedAt(row, col, "*");

        // 5. Display the menu at the bottom of the terminal
        printMenu(terminal,spreadsheet.getLine());

        // 6. Get the key from the user for navigation or input
        key = terminal.getSpecialKey();

        if (key == '0') {
            int pre_row = row;
            int pre_col = col;
            input.clear(); // Clear any previous input

            // Allow the user to input a value for the current cell
            while (true)
            {
                terminal.printAt(spreadsheet.getLine()+3, 0, "Input: " + input + " "); // Add space to clear leftover characters

                key = cin.get();
                if (key == '\n') // If Enter key is pressed
                {
                    if (!input.empty())
                    {
                        cellRow = (row - 2); // Adjusted to match spreadsheet indexing
                        cellCol = (pre_col / cellWidth) - 1; // Correct column index

                        if (cellRow >= 0 && cellRow < spreadsheet.getLine() &&
                            cellCol >= 0 && cellCol < spreadsheet.getColumn()) {
                            try {
                                double numValue = stod(input);
                                stringstream stream;
                                stream << fixed << setprecision(2) << numValue;
                                spreadsheet.editCell(cellRow, cellCol, stream.str());
                            } catch (const std::invalid_argument&) {
                                spreadsheet.editCell(cellRow, cellCol, input); // Use as string if not a valid number
                            }
                        }

                        input.clear(); // Clear input after updating
                    }
                    break; // Exit input loop after Enter key
                }
                else if (isprint(key)) // If printable character is pressed
                {
                    input += key;
                    if (input.length() < cellWidth) {
                        terminal.printAt(spreadsheet.getLine()+3, 0, "Input: " + input); // Update input display
                    }
                }
                else if (key == 127 || key == '\b') // Handle backspace key
                {
                    if (!input.empty()) {
                        input.pop_back();
                        terminal.printAt(spreadsheet.getLine()+3, 0, "Input: " + input + " "); // Add space to clear leftover characters
                    }
                }
            }

            row = pre_row; // Reset the cursor row after input
            col = pre_col; // Reset the cursor column after input
        }
        else if (key == 'f')
        {
            terminal.printAt(spreadsheet.getLine()+3, 0, "Enter filename: " + filename + " ");
            char key;
            while (true) {
                key = cin.get();
                if (key == '\n') { // If Enter key is pressed
                    break;
                } else if (isprint(key)) { // If printable character is pressed
                    filename += key;
                    terminal.printAt(spreadsheet.getLine()+3, 0, "Enter filename: " + filename + " ");
                } else if (key == 127 || key == '\b') { // Handle backspace key
                    if (!filename.empty()) {
                        filename.pop_back();
                        terminal.printAt(spreadsheet.getLine()+3, 0, "Enter filename: " + filename + " ");
                    }
                }
            }
            spreadsheet = fileManager.load_data(filename,spreadsheet.getLine(),spreadsheet.getColumn());
        }
        else if (key == 's') {
            terminal.printAt(spreadsheet.getLine()+3, 0, "Enter filename to save: " + filename + " ");
            filename.clear();
            while (true) {
                key = cin.get();
                if (key == '\n') { // If Enter key is pressed
                    break;
                } else if (isprint(key)) { // If printable character is pressed
                    filename += key;
                    terminal.printAt(spreadsheet.getLine()+3, 0, "Enter filename to save: " + filename + " ");
                } else if (key == 127 || key == '\b') { // Handle backspace key
                    if (!filename.empty()) {
                        filename.pop_back();
                        terminal.printAt(26, 0, "Enter filename to save: " + filename + " ");
                    }
                }
            }
            fileManager.save_file(spreadsheet, filename);
        }
        else {
            terminal.printAt(row, col, " "); // Clear the previous cursor
            int maxWidth = spreadsheet.getColumn() * cellWidth;
            switch (key)
            {
                case 'U': row = (row > 2) ? row - 1 : row; break;
                case 'D': row = (row < spreadsheet.getLine()+1) ? row + 1 : row; break;
                case 'R': col = (col + cellWidth < maxWidth) ? col + cellWidth : col; 
                    if(col<=spreadsheet.getColumn())
                        starting++;
                    break;
                case 'L': col = (col - cellWidth >= 10) ? col - cellWidth : col; 
                    if(col>=1)
                        starting--;
                    break;
                case 'q': return 0;
            }
        }

        terminal.printInvertedAt(row, col, "*");
    }


    terminal.clearScreen();
    return 0;
}
