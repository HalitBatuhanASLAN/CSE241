#include <iostream>
#include "FileManager.h"
#include "Spreadsheet.h"
#include "Cell.h"
#include "AnsiTerminal.h"

using namespace std;

int main()
{
    File fileManager;
    Spreadsheet spreadsheet(24, 20);
    /*string filename = "example.csv";
    spreadsheet = fileManager.load_data(filename);*/


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
                        else*/
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
}
