#include "Cell.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// Returns the content of the cell as a string
string Cell::getCell()
{return inner_cell;}

// Helper function to check if a string represents a valid number
bool isValidNumber(const string& str)
{
    try
    {
        std::stod(str); // Attempt to convert the string to a double
        return true;    // Conversion successful
    }
    catch (const invalid_argument&)
    {
        return false;   // String is not a valid number
    }
    catch (const out_of_range&)
    {
        return false;   // Number is out of range
    }
}

// Sets the content of the cell and determines its data type
void Cell::setCell(string entered)
{
    inner_cell = entered; // Store the raw content
    set_dt();             // Determine the data type

    if (get_dt() == Formula)
        formula = entered;    // Store as formula if applicable
    else if (get_dt() == str_type)
        str = entered;        // Store as string if applicable
    else if (isValidNumber(entered))
        number = stod(entered); // Convert and store as number
    else
        str = entered;        // Default to storing as string
}

// Overloads the << operator to print the content of a cell
ostream& operator<<(ostream& out, Cell &tmp)
{
    out << tmp.getCell(); // Output the raw content
    return out;
}

// Determines the data type of the cell based on its content
void Cell::set_dt()
{
    if (is_formula())
        dt = Formula;         // Set as formula if it starts with '='
    else if (is_num())
    {    
        dt = Number;          // Set as number if it is numeric
        double num = stod(getCell());
        setNum(num);          // Store the numeric value
    }
    else
        dt = str_type;        // Otherwise, set as string type
}

// Returns the current data type of the cell
data_type Cell::get_dt()
{return dt;}

// Checks if the cell contains a valid numeric value
bool Cell::is_num()
{
    char* end = nullptr;
    strtod(inner_cell.c_str(), &end); // Convert to double
    return (end == inner_cell.c_str() + inner_cell.size()); // Check if conversion used the entire string
}

// Checks if the cell contains a formula (starts with '=')
bool Cell::is_formula()
{
    return (inner_cell[0] == '='); // Returns true if first character is '='
}

// Sets the numeric value for the cell
void Cell::setNum(double new_num)
{number = new_num;}

// Returns the numeric value stored in the cell
double Cell::getNum()
{return number;}

// Destructor for the Cell class
Cell::~Cell() {}