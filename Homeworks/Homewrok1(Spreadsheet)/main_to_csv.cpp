#include <iostream>
#include "FileManager.h"
#include "Spreadsheet.h"
#include "Cell.h"
#include "AnsiTerminal.h"
using namespace std;

int main() {
    File fileManager;
    Spreadsheet spreadsheet(24, 20);
    std::string filename = "example.csv";
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
            while (true) {
                key = cin.get();
                if (key == '\n') {
                    if (!input.empty()) {
                        int cellRow = (row - 1) / 1;
                        int cellCol = (col - 0) / cellWidth;

                        if (cellRow >= 0 && cellRow < spreadsheet.getLine() &&
                            cellCol >= 0 && cellCol < spreadsheet.getColumn()) {
                            spreadsheet.editCell(cellRow, cellCol-1, input);
                            terminal.printInvertedAt(row, col - input.length(), input);
                        }
                        else
                        {
                            spreadsheet.editCell(row-1, col/10, input);
                            terminal.printInvertedAt(row, col - input.length(), input);
                        }
                        input.clear();
                    }
                    break;
                } else if (isprint(key)) {
                    if (input.length() < cellWidth) {
                        input += key;
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
                case 'U': row = (row >= 0) ? row - 1 : row; break;
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























/*#include <iostream>
#include "FileManager.h"  // Assuming FileManager handles CSV loading
#include "Spreadsheet.h"  // Assuming Spreadsheet holds the vector of cells
#include "Cell.h"
#include "AnsiTerminal.h"
int main() {
    
    File fileManager;
    Spreadsheet spreadsheet(24,80);
    std::string filename = "example.csv";
    spreadsheet = fileManager.load_data(filename);
    
    AnsiTerminal terminal;
    terminal.clearScreen();

    const int cellWidth = 5;
    int row = 10, col = 10;
    terminal.printInvertedAt(row, col, "*");

    string input;
    char key;

    
    while (true) {
        spreadsheet.print_frame(terminal);
        key = terminal.getSpecialKey();

        if (key == '0') {
            while (true) {
                key = cin.get();

                if (key == '\n') {
                    if (!input.empty()) {
                        int displayCol = col - (input.length() % cellWidth);
                        terminal.printAt(row, displayCol, input);
                        spreadsheet.editCell(row-1,(displayCol-1)/cellWidth,input);
                        input.clear();
                        row = (row < 24) ? row + 1 : row;
                        col = 10;
                    }
                    break;
                } else if (isprint(key)) {
                    if (input.length() < cellWidth) {
                        input += key;
                        terminal.printAt(row, col, string(1, key));
                        col = (col < 80) ? col + 1 : col;
                    }
                }
            }
        } else {
            
            terminal.printAt(row, col, " ");

            switch (key) {
                case 'U': row = (row > 1) ? row - 1 : row; break;
                case 'D': row = (row < 24) ? row + 1 : row; break;
                case 'R': col = (col + cellWidth < 80) ? col + cellWidth : col; break;
                case 'L': col = (col - cellWidth > 1) ? col - cellWidth : col; break;
                case 'q': return 0;
            }
        }

        terminal.printInvertedAt(row, col, "*");
        
    }

    terminal.clearScreen();
    

    return 0;
}
*/