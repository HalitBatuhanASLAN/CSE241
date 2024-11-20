#include <iostream>
#include "FileManager.h"
#include "Spreadsheet.h"
#include "Cell.h"
#include "AnsiTerminal.h"

using namespace std;
string COLUMN_ALPHABET_MAIN = "ABCDEFGHIJ";


int main()
{
    File fileManager;
    Spreadsheet spreadsheet(24, 20);
    /*string filename = "example.csv";
    spreadsheet = fileManager.load_data(filename);*/

    AnsiTerminal terminal;
    terminal.clearScreen();

    const int cellWidth = 10;
    int row = 2, col = 10; // Start at cell A1, considering headers
    terminal.printAt(row, col, "*");

    string input;
    char key;

    while (true) {
        terminal.clearScreen();

        // 1. Display the current cell information at the top of the terminal
        int cellRow = (row - 2); // Adjusted for actual row index, skipping header rows
        int cellCol = (col / cellWidth) - 1; // Adjusted for actual column index
        if (cellRow >= 0 && cellCol >= 0 && cellCol < spreadsheet.getColumn()) {
            string currentCell = "CELL: " + string(1, COLUMN_ALPHABET_MAIN[cellCol]) + to_string(cellRow + 1);
            terminal.printAt(0, 0, currentCell); // Place "CELL: ..." at the top
        }

        // 2. Display the spreadsheet from the third line onwards, no overlap with "CELL: ..."
        spreadsheet.print_frame(terminal);

        // 3. Display the input prompt at the bottom of the terminal
        string inputPrompt = "Input: " + input;
        terminal.printAt(26, 0, inputPrompt); // Assuming a total of 27 rows in the terminal (0-based index)

        // 4. Display the current selection marker
        terminal.printInvertedAt(row, col, "*");

        // 5. Get the key from the user for navigation or input
        key = terminal.getSpecialKey();

        if (key == '0') {
            int pre_row = row;
            int pre_col = col;
            input.clear(); // Clear any previous input

            // Allow the user to input a value for the current cell
            while (true)
            {
                // Continuously update the input prompt while typing
                terminal.printAt(26, 0, "Input: " + input + " "); // Add space to clear leftover characters

                key = cin.get();
                if (key == '\n') // If Enter key is pressed
                {
                    if (!input.empty())
                    {
                        cellRow = (row - 2); // Adjusted to match spreadsheet indexing
                        cellCol = (pre_col / cellWidth) - 1; // Correct column index

                        if (cellRow >= 0 && cellRow < spreadsheet.getLine() &&
                            cellCol >= 0 && cellCol < spreadsheet.getColumn()) {
                            // Update the spreadsheet with the new value
                            spreadsheet.editCell(cellRow, cellCol, input);
                        }

                        input.clear(); // Clear input after updating
                    }
                    break; // Exit input loop after Enter key
                }
                else if (isprint(key)) // If printable character is pressed
                {
                    input += key;
                    if (input.length() < cellWidth) {
                        terminal.printAt(26, 0, "Input: " + input); // Update input display
                        terminal.printInvertedAt(row, col, "*");
                    }
                }
                else if (key == 127 || key == '\b') // Handle backspace key
                {
                    if (!input.empty()) {
                        input.pop_back();
                        terminal.printAt(26, 0, "Input: " + input + " "); // Add space to clear leftover characters
                        terminal.printInvertedAt(row, col, "*");
                    }
                }
            }

            row = pre_row; // Reset the cursor row after input
            col = pre_col; // Reset the cursor column after input
        }
        else {
            terminal.printAt(row, col, " "); // Clear the previous cursor
            switch (key) {
                case 'U': row = (row > 2) ? row - 1 : row; break; // Update to start from row 2
                case 'D': row = (row < 25) ? row + 1 : row; break; // Allow navigation within spreadsheet bounds
                case 'R': col = (col + cellWidth < 200) ? col + cellWidth : col; break;
                case 'L': col = (col - cellWidth >= 10) ? col - cellWidth : col; break; // Prevent going before column headers
                case 'q': return 0; // Quit the program
            }
        }

        // Re-display the selection marker after navigation
        terminal.printInvertedAt(row, col, "*");
    }

    terminal.clearScreen();
    return 0;
}









/*int main()
{
    File fileManager;
    Spreadsheet spreadsheet(24, 20);
    /*string filename = "example.csv";
    spreadsheet = fileManager.load_data(filename);


    AnsiTerminal terminal;
    terminal.clearScreen();

    const int cellWidth = 10;
    int row = 0, col = 0;
    terminal.printAt(row, col, "*");

    string input;
    char key;

    while (true) {
        terminal.clearScreen();
        spreadsheet.print_frame(terminal);

        terminal.printAt(row, col, "*");
        key = terminal.getSpecialKey();

        if (key == '0') {
            int pre_row = row;
            int pre_col = col;
            while (true)
            {
                key = cin.get();
                if (key == '\n')
                {
                    if (!input.empty())
                    {
                        int cellRow = (row - 1) / 1;
                        int cellCol = (col - 0) / cellWidth;

                        /*if (cellRow >= 0 && cellRow < spreadsheet.getLine() &&
                            cellCol >= 0 && cellCol < spreadsheet.getColumn())
                        {
                            spreadsheet.editCell(row, cellCol, input);
                            terminal.printInvertedAt(row, col - input.length(), input);
                        }
                        else
                        {
                            spreadsheet.editCell(row-2, pre_col/10 - 1, input);
                            terminal.printInvertedAt(row, pre_col - input.length(), input);
                        }
                        input.clear();
                    }
                    break;
                }
                else if (isprint(key))
                {
                    input += key;
                    if (input.length() < cellWidth)
                    {
                        //input += key;
                        terminal.printInvertedAt(row, col, string(1, key));
                        col = (col < 200) ? col + 1 : col;
                    }
                }
            }
            row = pre_row;
            col = pre_col;
        }
        else {
            terminal.printAt(row, col, " ");
            switch (key) {
                case 'U': row = (row > 0) ? row - 1 : row; break;
                case 'D': row = (row < 24) ? row + 1 : row; break;
                case 'R': col = (col + cellWidth < 200) ? col + cellWidth  : col ; break;
                case 'L': col = (col - cellWidth >= 0) ? col - cellWidth : col; break;
                case 'q': return 0;
            }
        }

        terminal.printInvertedAt(row, col, "*");
    }

    terminal.clearScreen();
    return 0;
}*/
