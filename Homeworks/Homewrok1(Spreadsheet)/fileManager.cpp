#include"FileManager.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

Spreadsheet File::load_data(string file_name)
{
    Spreadsheet tmp(10,10);
    ifstream file(file_name);
    if(!file.is_open())
    {
        cerr << "File could not opened!!!" << endl;
        exit(-1);
    }
    else
        cout << "File opened\n";
    string line;
    int line_counter = 0,column_counter = 0;
    while(getline(file,line))
    {
        cout << "inner line is: " << line << endl;
        string str;
        for(char character : line)
        {
            //cout << line;
            if(character != ',')
            {    
                //cout << character << endl;
                str += character;
            }
            else if(character == ',' || character == '\n')
            {
                tmp.editCell(line_counter,column_counter,str);
                //cout << line_counter << str << endl;
                //cout << tmp.getFrame(line_counter,column_counter) << endl;
                column_counter++;
                str.clear();
            }
        }
        if (!str.empty())
        {
            tmp.editCell(line_counter, column_counter, str);
            //tmp.getCell(line_counter, column_counter);
        }
        column_counter = 0;
        line_counter++;
    }
    cout << "file readed\n";

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
            file << tmp.getFrame(line_counter,column_counter);
            if(column_counter != tmp.getColumn() -1)
                file << ",";
        }
        file << "\n";
    }
    file.close();
}