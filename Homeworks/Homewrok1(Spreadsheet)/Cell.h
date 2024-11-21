#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<string>
using namespace std;

// Enum to define the type of data a Cell can hold
enum data_type
{
    Number,     // Represents a numeric value
    Formula,    // Represents a formula
    str_type    // Represents a string
};

// Class representing a cell, which can store different types of data
class Cell
{
    public:
        // Sets the data type of the cell
        void set_dt();
        
        // Gets the current data type of the cell
        data_type get_dt();

        // Returns the content of the cell as a string
        string getCell();
        
        // Sets the content of the cell as a string
        void setCell(string entered);
        
        // Checks if the cell contains a numeric value
        bool is_num();
        
        // Checks if the cell contains a formula
        bool is_formula();
        
        // Sets a numeric value to the cell
        void setNum(double new_num);
        
        // Returns the numeric value stored in the cell
        double getNum();

        // Overloads the << operator to allow easy printing of a Cell object
        friend ostream& operator<<(ostream& out, Cell &tmp);

        // Destructor for the Cell class
        ~Cell();

    private:
        // Variable to store the data type of the cell
        data_type dt;
        
        // Stores the formula in the cell (if applicable)
        string formula;
        
        // Stores the string value in the cell (if applicable)
        string str;
        
        // Stores the numeric value in the cell (if applicable)
        double number;
        
        // Stores the raw content of the cell
        string inner_cell;
};
// Declaration of the overloaded << operator outside the class
ostream& operator<<(ostream& out, Cell &tmp);

#endif
