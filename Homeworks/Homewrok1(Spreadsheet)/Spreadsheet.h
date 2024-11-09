#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include"Cell.h"

#include<iostream>
#include<vector>
using namespace std;

class Spreadsheet
{
    public:
        Spreadsheet(int line,int column);
        int getLine();
        int getColumn();
        void print_frame();

        void editCell(int line, int column,string value);
        string getFrame(int line, int column);

        ~Spreadsheet();
    private:
        vector<vector<Cell>> frame;
};

#endif