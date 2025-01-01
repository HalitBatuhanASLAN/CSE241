#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Function to load data from a file into a Spreadsheet object
// Parameters:
// - file_name: The name of the file to load data from
// - size_line: The number of rows in the spreadsheet
// - size_column: The number of columns in the spreadsheet
namespace Utils
{
        
    spread::Spreadsheet File::load_data(string file_name, int size_line, int size_column)
    {
        spread::Spreadsheet tmp(size_line, size_column); // Create a Spreadsheet object with the specified dimensions
        
        try
        {
            ifstream file(file_name);              // Open the file for reading
            if(!file.is_open())
            {
                file.close();
                throw -1;
            }
            string line;
            int line_counter = 0, column_counter = 0;

            // Read the file line by line
            while(getline(file, line))
            {
                string str;

                // Parse the line character by character
                for(char character : line)
                {
                    if(character != ',')
                        str += character; // Append character to the current cell value
                    else if(character == ',' || character == '\n')
                    {
                        // If a comma or newline is encountered, store the value in the spreadsheet
                        if(!str.empty())
                            tmp.editCell(line_counter, column_counter, str);
                        else
                            tmp.editCell(line_counter, column_counter,"");
                        column_counter++;
                        str.clear(); // Clear the string for the next value
                    }
                }

                if(!str.empty())
                    tmp.editCell(line_counter, column_counter, str); // Store the last value in the line

                column_counter = 0; // Reset column counter for the next line
                line_counter++;

                // Ensure the line count does not exceed the spreadsheet's dimensions
                if(line_counter >= tmp.getLine())
                    break;
            }

            file.close(); // Close the file    
        }
        catch(int& e)
        {
            cerr << "Error code : " << e << endl;
            throw FileException("File " + file_name + " could not opened!!!");
        }
        catch(...)
        {
            throw FileException("Problem occured while readining file");
        }
        return tmp;   // Return the populated spreadsheet
    }

    // Function to save a Spreadsheet object's content to a file
    // Parameters:
    // - tmp: The Spreadsheet object containing the data to save
    // - file_name: The name of the file to save the data into
    void File::save_file(spread::Spreadsheet& tmp, string file_name)
    {
        try
        {
            ofstream file(file_name); // Open the file for writing

            if(!file.is_open())
            {
                file.close();
                throw -1;                
            }

            int line_counter = 0, column_counter = 0;

            // Loop through each cell in the spreadsheet
            for(line_counter = 0; line_counter < tmp.getLine(); line_counter++)
            {
                for(column_counter = 0; column_counter < tmp.getColumn(); column_counter++)
                {
                    file << tmp.getFrame(line_counter, column_counter); // Write the cell value to the file

                    if(column_counter != tmp.getColumn() - 1)
                        file << ","; // Add a comma if it's not the last column
                }
                file << "\n"; // Add a newline at the end of each row
            }
            file.close(); // Close the file
        }
        catch(const int& e)
        {
            cerr << "Error code " << e << endl;
            throw FileException("File coul not opened!!!");
        }
        catch(...)
        {
            throw FileException("Some problems occured");
        }
    }   
}