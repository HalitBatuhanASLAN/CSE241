                                                        ANSI Terminal-Based Spreadsheet Program
This repository contains a simplified spreadsheet application inspired by VisiCalc. The project demonstrates object-oriented programming (OOP), recursion, and file handling in C++. Below is an overview of the program's features and instructions for compiling and running the code.

                                                        Contents

Part 1: Spreadsheet Grid and Cell Management (Spreadsheet.cpp, Cell.cpp)

Part 2: Formula Parsing and Evaluation (new_formula.cpp)

Part 3: File I/O and Terminal Interface (fileManager.cpp, AnsiTerminal.cpp)

                Part 1: Spreadsheet Grid and Cell Management
  Problem
  
This part focuses on creating and managing a 2D spreadsheet grid. Each cell can store values, formulas, or references to other cells. The program supports navigation and editing within the grid using ANSI terminal commands.

  Key Concepts

Object-oriented design with Cell and Spreadsheet classes.

Dynamic 2D grid management using STL containers (std::vector).

Efficient navigation and editing of cells in an ANSI terminal.

              Part 2: Formula Parsing and Evaluation
  Problem
This part enables the use of formulas in spreadsheet cells. Users can input formulas to perform arithmetic operations or reference other cells. The program also supports basic functions like SUM, AVER, and MAX.

  Key Concepts

Recursive evaluation of formulas with cell references.

Support for arithmetic operations (+, -, *, /).

Built-in functions for ranges, including:

SUM(A1..B3) - Sum of values in a range.

AVER(A1..B3) - Average of values in a range.

MAX(A1..B3) - Maximum value in a range.

  How to Use

Enter formulas directly into a cell (e.g., =A1+B2 or =SUM(A1..A3)).

The program automatically recalculates dependent cells when references are updated.

            Part 3: File I/O and Terminal Interface
  Problem
This part adds functionality for saving and loading spreadsheets in CSV format. It also provides a user-friendly ANSI terminal interface for navigating and interacting with the spreadsheet.

  Key Concepts

File operations for saving and loading data in CSV format.

ANSI terminal commands for a visual spreadsheet interface.

Key bindings for navigation and operations:

Arrow keys or U/D/L/R - Navigate cells.

0 - Edit the current cell.

f - Load a file.

s - Save the spreadsheet to a file.

q - Quit the program.

          Additional Information
  Example Files:

example.csv - Sample spreadsheet input.

saved.csv - Example of a saved spreadsheet.

spreadsheet.csv - Large dataset for testing.

  Missing Features / Known Issues:

Cyclic references in formulas are not handled.

Parentheses in formulas are not supported.

Only ASCII characters are supported in cell values.

  UML Diagram:

A UML diagram of the class structure is provided in UML_spreadsheet.png.
