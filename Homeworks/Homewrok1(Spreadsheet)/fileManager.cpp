#include"FileManager.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

Spreadsheet File::load_data(string file_name)
{
    Spreadsheet tmp;
    ifstream file(file_name);
    if(!file.is_open())
    {
        cerr << "File could not opened!!!" << endl;
        exit(-1);
    }
    string line,inner_line,str;
    int line_counter = 0,column_counter = 0;
    while(getline(file,line))
    {
        inner_line = line;
        for(char character: inner_line)
        {
            while(character != ',')
                str += character;
            tmp.editCell(line_counter,column_counter,str);
            column_counter++;
        }
        column_counter = 0;
        line_counter++;
    }


    file.close();
    return tmp;
}

void save_file(Spreadsheet& tmp,string file_name)
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
            file << tmp.getCell(line_counter,column_counter);
            if(column_counter != tmp.getColumn() -1)
                file << ",";
        }
        file << "\n";
    }
    file.close();
}