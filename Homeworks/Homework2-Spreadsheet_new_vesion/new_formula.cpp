#include "new_formula.h"
#include "Cell.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm> // for all_of

using namespace std;
#define ERR -9999
#define MAX 1000000000
#define MIN -111111111



// Global variable representing column labels
string COLUMN_ALPHABET = "ABCDEFGHIJ";

// Function to parse and evaluate a formula in a cell
// Parameters:
// - tmp: Reference to the spreadsheet object
// - i: Row index of the cell
// - j: Column index of the cell
// Returns: The updated spreadsheet object
namespace formulaParsing
{
    spread::Spreadsheet& FormulaParser::parsing(spread::Spreadsheet& tmp, int i, int j)
    {
        bool flag = true; // Flag to check if the cell contains a function
        bool flag_err = true; // Flag to check for errors during evaluation
        string delimeters = "+-/*"; // Supported operators
        string main_expression = tmp.getFrame(i, j); // Get the formula from the cell
        int count = countDelimiters(main_expression, delimeters); // Count the number of operators in the formula
        size_t position;
        size_t next_pos;
        bool first_iteration = true;
        double result = 0;
        bool is_func = contain_func(main_expression); // Check if the formula contains a function

        // If there are no operators and no function, evaluate the single operand
        if (count == 0 && !is_func)
            result = (get_operand_value(main_expression.substr(1), tmp)); // e.g., "=A5" -> A5

        // Process the formula while there are operators to evaluate
        while (count > 0)
        {
            position = main_expression.find_first_of(delimeters); // Find the first operator
            if (position != string::npos)
            {
                char first_operator = main_expression[position]; // Get the operator
                string l_exp; // Left expression
                if (main_expression[0] == '=')
                    l_exp = main_expression.substr(1, position - 1); // Remove the '=' and extract the left operand
                else
                    l_exp = main_expression.substr(0, position); // Extract the left operand

                string r_exp = main_expression.substr(position + 1); // Extract the right operand
                next_pos = r_exp.find_first_of(delimeters); // Check for another operator in the right operand
                if (next_pos != string::npos)
                    r_exp = r_exp.substr(0, next_pos); // Extract the right operand up to the next operator

                double l_value, r_value;

                // Set the left operand value during the first iteration
                if (first_iteration) 
                {
                    if (!contain_func(l_exp)) // If left operand is not a function
                    {
                        l_value = get_operand_value(l_exp, tmp); // Get the numeric value
                        flag = false;
                    }
                    else
                        l_value = func_value(tmp, i, j, l_exp); // Evaluate the function
                    result = l_value; // Initialize the result with the left operand value
                    first_iteration = false;
                }

                // Evaluate the right operand
                if (!contain_func(r_exp)) // If right operand is not a function
                {
                    r_value = get_operand_value(r_exp, tmp); // Get the numeric value
                    flag = false;
                }
                else
                    r_value = func_value(tmp, i, j, r_exp); // Evaluate the function

                // Check for error values in operands
                if (r_value == ERR || l_value == ERR)
                    flag_err = false;

                // Perform the operation based on the operator
                switch (first_operator)
                {
                    case '+':
                        result += r_value; break;
                    case '-':
                        result -= r_value; break;
                    case '*':
                        result *= r_value; break;
                    case '/':
                        if (r_value == 0) // Division by zero error
                            flag_err = false;
                        else
                            result /= r_value;
                        break;
                    default:
                        flag_err = false; // Invalid operator
                }
                // Update the main_expression to process the next operator
                if (next_pos != string::npos)
                    main_expression = main_expression.substr(position + next_pos + 1);
            }
            count--; // Decrease the count of remaining operators
        }

        // If the formula contains a function, evaluate it
        if (flag && is_func)
            result = func_value(tmp, i, j, main_expression);

        // If no errors occurred, update the cell with the result
        if (flag_err)
            tmp.set_num(i, j, (result));
        else
            tmp.editCell(i, j, "ERROR"); // Update the cell with "ERROR" if an error occurred
        return tmp; // Return the updated spreadsheet
    }

    // Function to count the number of delimiters in a given string
    // Parameters:
    // - input: The string to search
    // - delimiters: A string containing the delimiters to count
    // Returns: The count of delimiters found in the input string
    int FormulaParser::countDelimiters(const string& input, const string& delimiters)
    {
        int count = 0; // Initialize the delimiter count
        for (char c : input) // Iterate through each character in the input string
        {
            if (delimiters.find(c) != std::string::npos) // Check if the character is a delimiter
                count++; // Increment the count if a delimiter is found
        }
        return count; // Return the total count of delimiters
    }

    // Function to evaluate a function value in a cell based on its formula
    // Parameters:
    // - tmp: Reference to the spreadsheet object
    // - i: Row index of the cell
    // - j: Column index of the cell
    // - main_expression: The main formula string to evaluate
    // Returns: The computed result of the function
    double FormulaParser::func_value(spread::Spreadsheet& tmp, int i, int j, string main_expression)
    {
        double result = 0; // Initialize the result
        string delimeter = "("; // Delimiter to identify the start of the function arguments
        size_t pos = tmp.getFrame(i, j).find_first_of(delimeter); // Find the position of the '(' character
        string expression = tmp.getFrame(i, j).substr(pos); // Extract the arguments starting from the '(' character

        // Check for specific functions and compute the result
        if (main_expression.find("SUM") != string::npos) // If "SUM" is found in the expression
            result = Sum(expression, tmp); // Compute the sum of the specified range
        else if (main_expression.find("AVER") != string::npos) // If "AVER" is found in the expression
            result = Aver(expression, tmp); // Compute the average of the specified range
        else if (main_expression.find("STDDIV") != string::npos) // If "STDDIV" is found in the expression
            result = Stddev(expression, tmp); // Compute the standard deviation of the specified range
        else if (main_expression.find("MAX") != string::npos) // If "MAX" is found in the expression
            result = Max(expression, tmp); // Compute the maximum value in the specified range
        else if (main_expression.find("MIN") != string::npos) // If "MIN" is found in the expression
            result = Min(expression, tmp); // Compute the minimum value in the specified range
        return result; // Return the computed result
    }


    // Function to calculate the sum of values in a specified range
    // Parameters:
    // - expression: The range expression (e.g., "(A2..A4)")
    // - tmp: Reference to the spreadsheet object
    // Returns: The sum of the values in the range
    double FormulaParser::Sum(string expression, spread::Spreadsheet& tmp)
    {
        // Extract the left and right parts of the range (e.g., "A2" and "A4")
        string delim = ".";
        size_t position = expression.find_first_of(delim);
        string l_part = expression.substr(1, position - 1); // Left part (e.g., "A2")
        string r_part = expression.substr(position + 2, expression.size() - position - 3); // Right part (e.g., "A4")

        // Extract the row numbers
        const string first_line = l_part.substr(letter_count(l_part)); // Extract the row number from the left part (e.g., "2")
        int line_first = stoi(first_line);
        const string last_line = r_part.substr(letter_count(r_part)); // Extract the row number from the right part (e.g., "4")
        int line_last = stoi(last_line);

        // Extract the column indices
        int column_starting = column_value(l_part); // Convert column label (e.g., "A") to index (e.g., 0)
        int end_column = column_value(r_part); // Convert column label (e.g., "B") to index

        double result = 0;

        // Iterate through the range of rows and columns
        while (line_first <= line_last)
        {
            int col = column_starting;
            while (col <= end_column)
            {
                // Get the numeric value of the cell and add it to the result
                double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, col));
                result += (tmp_num == ERR ? 0 : tmp_num); // Ignore cells with ERR value
                col++;
            }
            line_first++; // Move to the next row
        }
        return result; // Return the computed sum
    }

    // Function to calculate the average of values in a specified range
    // Parameters:
    // - expression: The range expression (e.g., "(A2..A4)")
    // - tmp: Reference to the spreadsheet object
    // Returns: The average of the values in the range
    double FormulaParser::Aver(string expression, spread::Spreadsheet& tmp)
    {
        // Extract the left and right parts of the range (e.g., "A2" and "A4")
        string delim = ".";
        size_t position = expression.find_first_of(delim);
        string l_part = expression.substr(1, position - 1); // Left part (e.g., "A2")
        string r_part = expression.substr(position + 2, expression.size() - position - 3); // Right part (e.g., "A4")

        // Extract the row numbers
        const string first_line = l_part.substr(letter_count(l_part)); // Extract the row number from the left part (e.g., "2")
        int line_first = stoi(first_line);
        const string last_line = r_part.substr(letter_count(r_part)); // Extract the row number from the right part (e.g., "4")
        int line_last = stoi(last_line);

        // Extract the column indices
        int column_starting = column_value(l_part); // Convert column label (e.g., "A") to index (e.g., 0)
        int end_column = column_value(r_part); // Convert column label (e.g., "B") to index

        // Use the Sum function to calculate the total sum of the range
        double result = Sum(expression, tmp);

        // Count the number of valid cells in the range
        int valid_cells = 0;
        while (line_first <= line_last)
        {
            int col = column_starting;
            while (col <= end_column)
            {
                double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, col));
                if (tmp_num != ERR) // Increment the counter if the cell contains a valid number
                    valid_cells++;
                col++;
            }
            line_first++; // Move to the next row
        }
        return valid_cells > 0 ? result / valid_cells : 0; // Calculate and return the average, or 0 if no valid cells
    }

    // Function to calculate the standard deviation of values in a specified range
    // Parameters:
    // - expression: The range expression (e.g., "(A2..A4)")
    // - tmp: Reference to the spreadsheet object
    // Returns: The standard deviation of the values in the range
    double FormulaParser::Stddev(string expression, spread::Spreadsheet& tmp)
    {
        double average = Aver(expression, tmp); // Calculate the average of the range
        double stddev = 0;
        string delim = ".";
        size_t position = expression.find_first_of(delim);
        string l_part = expression.substr(1, position - 1); // Left part (e.g., "A2")
        string r_part = expression.substr(position + 2, expression.size() - position - 3); // Right part (e.g., "A4")
        
        // Extract row numbers
        const string first_line = l_part.substr(1); // Extract row number from the left part
        int line_first = stoi(first_line);
        const string last_line = r_part.substr(1); // Extract row number from the right part
        int line_last = stoi(last_line);

        // Extract column index
        int column = COLUMN_ALPHABET.find(l_part[0]); // Get column index based on the letter
        int quantity = line_last - line_first; // Calculate the number of rows in the range

        double sum_of_pow = 0;

        // Iterate through the range and calculate the sum of squared differences
        for (int i = line_first; i <= line_last; i++)
        {
            double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, column));
            tmp_num = (tmp_num == ERR) ? 0 : tmp_num; // Ignore ERR values
            sum_of_pow += pow(tmp_num - average, 2); // Calculate squared difference from the mean
        }

        sum_of_pow /= (quantity + 1); // Divide by the number of elements
        stddev = sqrt(sum_of_pow); // Take the square root to get the standard deviation
        return stddev;
    }

    // Function to calculate the maximum value in a specified range
    // Parameters:
    // - expression: The range expression (e.g., "(A2..A4)")
    // - tmp: Reference to the spreadsheet object
    // Returns: The maximum value in the range
    double FormulaParser::Max(string expression, spread::Spreadsheet& tmp)
    {
        string delim = ".";
        size_t position = expression.find_first_of(delim);
        string l_part = expression.substr(1, position - 1); // Left part (e.g., "A2")
        string r_part = expression.substr(position + 2, expression.size() - position - 3); // Right part (e.g., "A4")

        // Extract row numbers
        const string first_line = l_part.substr(letter_count(l_part)); // Extract row number from the left part
        int line_first = stoi(first_line);
        const string last_line = r_part.substr(letter_count(r_part)); // Extract row number from the right part
        int line_last = stoi(last_line);

        // Extract column indices
        int column_starting = column_value(l_part); // Get starting column index
        int end_column = column_value(r_part); // Get ending column index

        double max_num = MIN; // Initialize with a very low value

        // Iterate through the range to find the maximum value
        while (line_first <= line_last)
        {
            int col = column_starting;
            while (col <= end_column)
            {
                double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, col), MIN);
                if (tmp_num != ERR && tmp_num > max_num) // Check if the value is valid and greater than the current maximum
                    max_num = tmp_num;
                col++;
            }
            line_first++;
        }

        return max_num; // Return the maximum value found
    }

    // Function to calculate the minimum value in a specified range
    // Parameters:
    // - expression: The range expression (e.g., "(A2..A4)")
    // - tmp: Reference to the spreadsheet object
    // Returns: The minimum value in the range
    double FormulaParser::Min(string expression, spread::Spreadsheet& tmp)
    {
        string delim = ".";
        size_t position = expression.find_first_of(delim);
        string l_part = expression.substr(1, position - 1); // Left part (e.g., "A2")
        string r_part = expression.substr(position + 2, expression.size() - position - 3); // Right part (e.g., "A4")

        // Extract row numbers
        const string first_line = l_part.substr(letter_count(l_part)); // Extract row number from the left part
        int line_first = stoi(first_line);
        const string last_line = r_part.substr(letter_count(r_part)); // Extract row number from the right part
        int line_last = stoi(last_line);

        // Extract column indices
        int column_starting = column_value(l_part); // Get starting column index
        int end_column = column_value(r_part); // Get ending column index

        double min_num = MAX; // Initialize with a very high value

        // Iterate through the range to find the minimum value
        while (line_first <= line_last)
        {
            int col = column_starting;
            while (col <= end_column)
            {
                double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, col), MAX);
                if (tmp_num != ERR && tmp_num < min_num) // Check if the value is valid and less than the current minimum
                    min_num = tmp_num;
                col++;
            }
            line_first++;
        }
        return min_num; // Return the minimum value found
    }


    // Function to get the numeric value of an operand (cell reference or number)
    // Parameters:
    // - expression: The operand as a string (e.g., "A1", "123")
    // - tmp: Reference to the spreadsheet object
    // Returns: The numeric value of the operand
    double FormulaParser::get_operand_value(string expression, spread::Spreadsheet& tmp)
    {
        // If the expression is purely numeric, convert it to a double and return
        if (std::all_of(expression.begin(), expression.end(), ::isdigit))
            return stod(expression);

        // Count the number of letters in the operand (to separate column and row parts)
        int counter_letter = 0;
        for (char c : expression)
            if (isalpha(c)) counter_letter++;

        // Calculate the column index based on the column letters (e.g., "A" -> 0, "AA" -> 26)
        int column = 0, i = 0;
        while (counter_letter > i)
        {
            column = column * 26 + (toupper(expression[i]) - 'A' + 1); // Base-26 calculation for column
            i++;
        }
        column -= 1; // Convert to zero-based index

        // Extract the row number from the operand
        const string new_str = expression.substr(counter_letter);
        int line = stoi(new_str);

        // Get the numeric value from the specified cell in the spreadsheet
        double num = safeStringToDouble(tmp.getFrame(line - 1, column));
        return num;
    }

    // Function to safely convert a string to a double, returning a default value if conversion fails
    // Parameters:
    // - str: The string to convert
    // - defaultValue: The value to return if conversion fails (default is 0.0)
    // Returns: The numeric value or default value
    double FormulaParser::safeStringToDouble(string str, double defaultValue)
    {
        if (str.empty()) // If the string is empty, return the default value
            return defaultValue;
        try
        {
            return stod(str); // Attempt to convert the string to a double
        }
        catch (const std::invalid_argument&) // Catch invalid argument exceptions
        {
            return ERR; // Return error code if conversion fails
        }
    }

    // Function to check if a string contains a recognized function
    // Parameters:
    // - tmp: The string to check
    // Returns: True if the string contains a function, otherwise false
    bool FormulaParser::contain_func(string tmp)
    {
        // Check for any of the recognized function keywords
        if (tmp.find("SUM") != string::npos
            || tmp.find("STDDIV") != string::npos
            || tmp.find("AVER") != string::npos
            || tmp.find("MAX") != string::npos
            || tmp.find("MIN") != string::npos)
            return true;
        return false;
    }

    // Function to count the number of letters at the start of a string
    // Parameters:
    // - expression: The string to analyze
    // Returns: The number of letters at the start of the string
    int FormulaParser::letter_count(string expression)
    {
        int count = 0;
        for (char c : expression)
        {
            if (isalpha(c))
                count++; // Increment the count for each letter
            else
                break; // Stop counting when a non-letter is encountered
        }
        return count;
    }

    // Function to calculate the zero-based column index from a column label
    // Parameters:
    // - operand: The column label as a string (e.g., "A", "AA")
    // Returns: The zero-based column index
    int FormulaParser::column_value(string operand)
    {
        int count = letter_count(operand); // Get the number of letters in the column label
        string columnName = operand.substr(0, count); // Extract the column part of the operand
        int column = 0;

        // Convert the column letters to a zero-based index
        for (char c : columnName)
            column = column * 26 + (toupper(c) - 'A' + 1);
        return column - 1; // Return the zero-based index
    }
}