#include"FileManager.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

Spreadsheet File::load_data(string file_name,int size_line,int size_column) {
    Spreadsheet tmp(size_line,size_column);
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "File could not be opened! Please check the filename and try again." << endl;
        return tmp;  // Returning an empty spreadsheet instead of exiting
    } else {
        cout << "File opened successfully." << endl;
    }

    string line;
    int line_counter = 0, column_counter = 0;
    while (getline(file, line)) {
        string str;
        for (char character : line) {
            if (character != ',') {
                str += character;
            } else if (character == ',' || character == '\n') {
                tmp.editCell(line_counter, column_counter, str);
                column_counter++;
                str.clear();
            }
        }
        if (!str.empty()) {
            tmp.editCell(line_counter, column_counter, str);
        }
        column_counter = 0;
        line_counter++;

        // Make sure we don't exceed spreadsheet dimensions
        if (line_counter >= tmp.getLine()) {
            break;
        }
    }

    cout << "File read successfully." << endl;
    file.close();
    return tmp;
}


void File::save_file(Spreadsheet& tmp,string file_name)
{
    ofstream file(file_name);
    if(!file.is_open())
    {
        cerr << "File could not opened!!!" << endl;
        exit(-1);
    }
    int line_counter = 0,column_counter = 0;
    for(line_counter = 0; line_counter < tmp.getLine();line_counter++)
    {
        for(column_counter = 0;column_counter<tmp.getColumn();column_counter++)
        {
            file << tmp.getFrame(line_counter,column_counter);
            if(column_counter != tmp.getColumn() -1)
                file << ",";
        }
        file << "\n";
    }
    file.close();
}