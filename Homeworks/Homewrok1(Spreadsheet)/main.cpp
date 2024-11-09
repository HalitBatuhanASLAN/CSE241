/*#include "AnsiTerminal.h"
#include <termios.h>
#include <iostream>
#include <string>
using namespace std;

#include "Cell.h"
#include "Spreadsheet.h"
#include "FileManager.h"
#include "FormulaParser.h"
int main() {
    AnsiTerminal terminal;
    terminal.clearScreen(); // Clear the screen at the beginning

    int row = 10, col = 10;
    terminal.printInvertedAt(row, col, "*"); // Initial cursor position in inverted mode

    string input;
    char key;
    while (true) {
        key = terminal.getSpecialKey();

        // Clear the previous position
        terminal.printAt(row, col, " ");

        // Update position based on arrow key input
        switch (key) {
            case 'U': row = (row > 1) ? row - 1 : row; break; // Up
            case 'D': row = (row < 24) ? row + 1 : row; break; // Down
            case 'R': col = (col < 80) ? col + 1 : col; break; // Right
            case 'L': col = (col > 1) ? col - 1 : col; break; // Left
            case 'q': return 0; // Quit program if 'q' is pressed
            case '0':
                key = cin.get();
                if (isprint(key)) {
                    input += key;
                    terminal.printAt(row, col, string(1, key));
                    col = (col < 80) ? col + 1 : col;
                }
                break;
        }

        // Display inverted cursor at new position
        terminal.printInvertedAt(row, col, "*");
        if (key == '\n') {
            input.clear();
            row = (row < 24) ? row + 1 : row;
            col = 10;
        }
    }

    terminal.clearScreen(); // Clear the screen on exit
    return 0;
}
*/
#include "AnsiTerminal.h"
#include <termios.h>
#include <iostream>
#include <string>
using namespace std;

#include "Cell.h"
#include "Spreadsheet.h"
#include "FileManager.h"
#include "FormulaParser.h"

int main() {
    AnsiTerminal terminal;
    terminal.clearScreen();

    const int cellWidth = 10;
    int row = 10, col = 10;
    terminal.printInvertedAt(row, col, "*");

    string input;
    char key;

    while (true) {
        key = terminal.getSpecialKey();

        if (key == '0') {
            while (true) {
                key = cin.get();

                if (key == '\n') {
                    if (!input.empty()) {
                        int displayCol = col - (input.length() % cellWidth);
                        terminal.printAt(row, displayCol, input);
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
