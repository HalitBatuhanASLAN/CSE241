#ifndef FILE_H
#define FILE_H
#include"Spreadsheet.h"
#include<iostream>
#include<string>
using namespace std;



class File
{
    public:
        Spreadsheet load_data(string file_name);
        void save_file(Spreadsheet& tmp,string file_name);
    private:
        string file_name;
};

#endif