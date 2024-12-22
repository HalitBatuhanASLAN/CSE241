#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include "Spreadsheet.h"
#include "Cell.h"
#include <iostream>
#include <string>

using namespace std;
// Forward declaration for Spreadsheet class
class Spreadsheet;

// Class responsible for parsing and evaluating formulas in spreadsheet cells
namespace formulaParsing
{
    class FormulaParser
    {
        public:
            // Constructor for FormulaParser
            FormulaParser() {}

            // Parses and evaluates a formula in a cell
            // Parameters:
            // - tmp: Reference to the spreadsheet object
            // - i: Row index of the cell
            // - j: Column index of the cell
            // Returns: Updated spreadsheet object
            spread::Spreadsheet& parsing(spread::Spreadsheet& tmp, int i, int j);

            // Checks if a given string contains a function
            // Parameters:
            // - tmp: The string to check
            // Returns: True if a function is found, otherwise false
            bool contain_func(string tmp);

            // Gets the numeric value of an operand from the spreadsheet
            // Parameters:
            // - expression: The operand expression (e.g., "A1")
            // - tmp: Reference to the spreadsheet object
            // Returns: The value of the operand as a double
            double get_operand_value(string expression, spread::Spreadsheet& tmp);

            // Computes the sum of values within a range in the spreadsheet
            // Parameters:
            // - expression: The range expression (e.g., "A1..B3")
            // - tmp: Reference to the spreadsheet object
            // Returns: The sum of the values
            double Sum(string expression, spread::Spreadsheet& tmp);

            // Computes the average of values within a range in the spreadsheet
            // Parameters:
            // - expression: The range expression (e.g., "A1..B3")
            // - tmp: Reference to the spreadsheet object
            // Returns: The average of the values
            double Aver(string expression, spread::Spreadsheet& tmp);

            // Computes the standard deviation of values within a range in the spreadsheet
            // Parameters:
            // - expression: The range expression (e.g., "A1..B3")
            // - tmp: Reference to the spreadsheet object
            // Returns: The standard deviation of the values
            double Stddev(string expression, spread::Spreadsheet& tmp);

            // Finds the maximum value within a range in the spreadsheet
            // Parameters:
            // - expression: The range expression (e.g., "A1..B3")
            // - tmp: Reference to the spreadsheet object
            // Returns: The maximum value
            double Max(string expression, spread::Spreadsheet& tmp);

            // Finds the minimum value within a range in the spreadsheet
            // Parameters:
            // - expression: The range expression (e.g., "A1..B3")
            // - tmp: Reference to the spreadsheet object
            // Returns: The minimum value
            double Min(string expression, spread::Spreadsheet& tmp);

            // Evaluates the value of a function in a cell
            // Parameters:
            // - tmp: Reference to the spreadsheet object
            // - i: Row index of the cell
            // - j: Column index of the cell
            // - main_expression: The formula expression to evaluate
            // Returns: The computed value of the function
            double func_value(spread::Spreadsheet& tmp, int i, int j, string main_expression);

            // Safely converts a string to a double, with a default value if conversion fails
            // Parameters:
            // - str: The string to convert
            // - defaultValue: The value to return if conversion fails (default is 0.0)
            // Returns: The converted double value
            double safeStringToDouble(string str, double defaultValue = 0.0);

            // Counts the number of specific delimiters in a string
            // Parameters:
            // - input: The string to search
            // - delimiters: The delimiter characters to count
            // Returns: The count of delimiters found
            int countDelimiters(const string& input, const string& delimiters);

            // Gets the column index for a given column label (e.g., "A" -> 0, "AA" -> 27)
            // Parameters:
            // - operand: The column label as a string
            // Returns: The column index as an integer
            int column_value(string operand);

            // Counts the number of letters in a given string
            // Parameters:
            // - expression: The string to analyze
            // Returns: The number of letters in the string
            int letter_count(string expression);
    };
}
#endif