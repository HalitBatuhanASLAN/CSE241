#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include"Cell.h"

#include<iostream>
#include<vector>
using namespace std;

class Spreadsheet
{
    public:
        int getLine();
        int getColumn();
        void print_frame();

        void editCell(int line, int column,string value);
        string getCell(int line, int column);

        ~Spreadsheet();
    private:
        vector<vector<Cell>> frame;
};

#endif