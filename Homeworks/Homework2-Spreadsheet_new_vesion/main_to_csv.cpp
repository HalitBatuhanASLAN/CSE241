#include <iostream>
#include "FileManager.h"
#include "Spreadsheet.h"
#include "Cell.h"
#include "AnsiTerminal.h"
#include <sstream>
#include <iomanip>
using namespace std;
using namespace spread;
// Function declarations
void printMenu(AnsiTerminal &terminal, int line);
string getColumnLabel(int columnIndex);

int main()
{
    File fileManager;
    Spreadsheet spreadsheet(1500,1500); // Initialize a spreadsheet with 35 rows and 45 columns
    string filename;

    AnsiTerminal terminal;
    terminal.clearScreen(); // Clear the terminal screen

    const int cellWidth = 10; // Width of each cell
    const int max_column = 15; // Maximum number of columns to display at the same time
    int starting_point = 0;  
    int max_line = 20; // Maximum number of rows to display at the same time
    int start_line = 0;
    int row = 2, col = 10; // Start at cell A1, considering headers
    terminal.printAt(row, col, "*"); // Place a cursor at the starting cell

    string input;
    char key;

    while (true) {
        terminal.clearScreen(); // Clear the terminal for each update

        // 1. Display the current cell information at the top of the terminal
        int cellRow = (row - 2); // Adjusted for actual row index, skipping header rows
        int cellCol = (col / cellWidth) - 1 + starting_point; // Adjusted for actual column index
        if (cellRow >= 0 && cellCol >= 0 && cellCol < spreadsheet.getColumn())
        {
            string columnLabel = getColumnLabel(cellCol);
            string currentCell = "CELL: " + columnLabel + to_string(cellRow + 1); // Display the current cell (e.g., CELL: A1)
            terminal.printInvertedAt(0, 0, currentCell); // Place "CELL: ..." at the top
        }

        // 2. Display the spreadsheet from the third line onwards, within the visible range
        spreadsheet.print_frame(terminal, max_column, starting_point, max_line, start_line);

        // 3. Display the input prompt at the bottom of the terminal
        string cellValue = spreadsheet.getFrame(cellRow, cellCol);
        if (cellRow >= 0 && cellRow < spreadsheet.getLine() && cellCol >= 0 && cellCol < spreadsheet.getColumn() && !cellValue.empty())
        {
            try
            {
                double numValue = stod(cellValue); // Try converting cell value to a number
                stringstream stream;
                stream << fixed << setprecision(2) << numValue;
                input = stream.str();
            }
            catch (const std::invalid_argument&) {
                input = cellValue; // If not a number, keep it as a string
            }
        }
        else
            input.clear(); // Clear input if no value
        string inputPrompt = "Input: " + input;
        terminal.printAt(max_line + 2, 0, inputPrompt); // Display input prompt

        // 4. Display the current selection marker
        terminal.printInvertedAt(row, col, "*");

        // 5. Display the menu at the bottom of the terminal
        printMenu(terminal, max_line + 3);

        // 6. Get the key from the user for navigation or input
        key = terminal.getSpecialKey();

        if (key == '0')
        {
            int pre_row = row;
            int pre_col = col;
            input.clear(); // Clear any previous input

            // Allow the user to input a value for the current cell
            while (true)
            {
                terminal.printAt(max_line + 2, 0, "Input: " + input + " "); // Add space to clear leftover characters

                key = cin.get();
                if (key == '\n') // If Enter key is pressed
                {
                    if (!input.empty())
                    {
                        cellRow = (row - 2); // Adjusted to match spreadsheet indexing
                        cellCol = (pre_col / cellWidth) - 1 + starting_point; // Correct column index

                        if (cellRow >= 0 && cellRow < spreadsheet.getLine() &&
                            cellCol >= 0 && cellCol < spreadsheet.getColumn()) 
                        {
                            try 
                            {
                                double numValue = stod(input); // Try converting input to a number
                                stringstream stream;
                                stream << fixed << setprecision(2) << numValue;
                                spreadsheet.editCell(cellRow, cellCol, stream.str());
                            }
                            catch (const std::invalid_argument&){
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
                    if (input.length() < cellWidth)
                        terminal.printAt(max_line + 2, 0, "Input: " + input); // Update input display
                }
                else if (key == 127 || key == '\b') // Handle backspace key
                {
                    if (!input.empty())
                    {
                        input.pop_back(); // Remove last character
                        terminal.printAt(max_line + 2, 0, "Input: " + input + " "); // Add space to clear leftover characters
                    }
                }
            }

            row = pre_row; // Reset the cursor row after input
            col = pre_col; // Reset the cursor column after input
        }
        else if (key == 'f')
        {
            terminal.printAt(max_line + 2, 0, "Enter filename: " + filename + " ");
            char key;
            while (true)
            {
                key = cin.get();
                if (key == '\n') // If Enter key is pressed
                    break;
                else if (isprint(key)) // If printable character is pressed
                {
                    filename += key;
                    terminal.printAt(max_line + 2, 0, "Enter filename: " + filename + " ");
                }
                else if (key == 127 || key == '\b') // Handle backspace key
                {
                    if (!filename.empty())
                    {
                        filename.pop_back();
                        terminal.printAt(max_line + 2, 0, "Enter filename: " + filename + " ");
                    }
                }
            }
            spreadsheet = fileManager.load_data(filename, spreadsheet.getLine(), spreadsheet.getColumn()); // Load data from file
        }
        else if (key == 's')
        {
            terminal.printAt(max_line + 2, 0, "Enter filename to save: " + filename + " ");
            filename.clear();
            while (true)
            {
                key = cin.get();
                if (key == '\n') // If Enter key is pressed
                    break;
                else if (isprint(key)) // If printable character is pressed
                {
                    filename += key;
                    terminal.printAt(max_line + 2, 0, "Enter filename to save: " + filename + " ");
                }
                else if (key == 127 || key == '\b') // Handle backspace key
                {
                    if (!filename.empty())
                    {
                        filename.pop_back();
                        terminal.printAt(max_line + 2, 0, "Enter filename to save: " + filename + " ");
                    }
                }
            }
            fileManager.save_file(spreadsheet, filename); // Save data to file
        }
        else
        {
            terminal.printAt(row, col, " "); // Clear the previous cursor
            int maxWidth = spreadsheet.getColumn() * cellWidth; // Maximum width of the spreadsheet
            switch (key)
            {
                case 'U': // Move up
                    if (row > 2)
                        row--;
                    else if (start_line > 0)
                        start_line--;
                    break;
                case 'D': // Move down
                    if (row < max_line)
                        row++;
                    else if (start_line + max_line - 1 < spreadsheet.getLine()) 
                        start_line++;
                    break;
                case 'R': // Move right
                    if (col / cellWidth - 1 < max_column - 1)
                        col += cellWidth;
                    else if (starting_point + max_column < spreadsheet.getColumn())
                        starting_point++;
                    break;
                case 'L': // Move left
                    if (col / cellWidth - 1 > 0)
                        col -= cellWidth;
                    else if (starting_point > 0)
                        starting_point--;
                    break;
                case 'q': return 0; // Quit the program
            }
        }
        terminal.printInvertedAt(row, col, "*"); // Place the cursor at the new position
    }
    terminal.clearScreen(); // Clear the screen when exiting
    return 0;
}

// Function to print the menu of commands and functions below the spreadsheet
// Parameters:
// - terminal: Reference to the AnsiTerminal object used for printing
// - line: The current number of rows in the spreadsheet (used to position the menu below the spreadsheet)
void printMenu(AnsiTerminal &terminal, int line)
{
    int menuRow = line + 1; // Print menu starting at row below the spreadsheet
    terminal.printAt(menuRow++, 0, "    Commands:");
    terminal.printAt(menuRow++, 0, " - Enter '0' to input data into the current cell"); // Command to edit the current cell
    terminal.printAt(menuRow++, 0, " - Use 'U', 'D', 'L', 'R' or arrow keys to navigate Up, Down, Left, Right"); // Navigation commands
    terminal.printAt(menuRow++, 0, " - Enter 'f' to load data from a file"); // Command to load data from a file
    terminal.printAt(menuRow++, 0, " - Enter 's' to save data to a file"); // Command to save data to a file
    terminal.printAt(menuRow++, 0, " - Enter 'q' to quit the program"); // Command to quit the program
    terminal.printAt(menuRow++, 0, "    Functions:");
    terminal.printAt(menuRow++, 0, " - '=SUM(A1..B3)' to sum of values in rectangle formed by A1 and B3"); // SUM function
    terminal.printAt(menuRow++, 0, " - '=AVER(A1..B3)' to average of values in rectangle formed by A1 and B3"); // AVERAGE function
    terminal.printAt(menuRow++, 0, " - '=STDDIV(A1..B3)' to standard derivation of values in rectangle formed by A1 and B3"); // STANDARD DEVIATION function
    terminal.printAt(menuRow++, 0, " - '=MAX(A1..B3)' to find maximum value in rectangle formed by A1 and B3"); // MAX function
    terminal.printAt(menuRow++, 0, " - '=MIN(A1..B3)' to find minimum value in rectangle formed by A1 and B3"); // MIN function
    terminal.printInvertedAt(menuRow++, 0, ""); // Empty line to separate menu visually
}

// Function to convert a zero-based column index to a spreadsheet-style column label (e.g., 0 -> "A", 27 -> "AA")
// Parameters:
// - columnIndex: The zero-based index of the column
// Returns: A string representing the column label
string getColumnLabel(int columnIndex)
{
    string columnLabel = "";
    while(columnIndex >= 0)
    {
        columnLabel = char('A' + (columnIndex % 26)) + columnLabel; // Calculate the character for the current index
        columnIndex = columnIndex / 26 - 1; // Move to the next higher "digit" in the label
    }
    return columnLabel; // Return the constructed column label
}