#ifndef FILE_H
#define FILE_H

#include "Spreadsheet.h"
#include <iostream>
#include <string>
#include<stdexcept>

using namespace std;

namespace Utils
{
    // Class representing file operations for loading and saving spreadsheet data
    class File
    {
        public:
            // Loads data from a file into a Spreadsheet object
            // Parameters:
            // - file_name: The name of the file to load data from
            // - size_line: The number of rows in the spreadsheet
            // - size_column: The number of columns in the spreadsheet
            spread::Spreadsheet load_data(string file_name, int size_line, int size_column);

            // Saves the content of a Spreadsheet object to a file
            // Parameters:
            // - tmp: The Spreadsheet object to save
            // - file_name: The name of the file to save data into
            void save_file(spread::Spreadsheet& tmp, string file_name);
    };

    class FileException:public std::runtime_error
    {
        public:
            explicit FileException(const std::string& message) : std::runtime_error(message) {}
    };

}
#endif