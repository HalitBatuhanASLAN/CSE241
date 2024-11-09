#include <iostream>
#include "FileManager.h"  // Assuming FileManager handles CSV loading
#include "Spreadsheet.h"  // Assuming Spreadsheet holds the vector of cells
#include "Cell.h"
int main() {
    // Create a FileManager instance to handle file operations
    File fileManager;

    // Create a Spreadsheet instance to store cell data
    Spreadsheet spreadsheet(10,10);

    // Load data from a CSV file
    std::string filename = "example.csv"; // Name of the CSV file
    spreadsheet = fileManager.load_data(filename);
    /*if (fileManager.load_data(filename)) {
        std::cout << "Data loaded successfully from " << filename << std::endl;
    } else {
        std::cerr << "Failed to load data from " << filename << std::endl;
        return 1;
    }*/

    // Print the loaded data to the console
    spreadsheet.print_frame(); // Assuming Spreadsheet has a print() function

    return 0;
}
