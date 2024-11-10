#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include"Cell.h"

#include<iostream>
#include<vector>
#include "AnsiTerminal.h"
#include "FormulaParser.h"
using namespace std;
class FormulaParser;
class Spreadsheet
{
    public:
        Spreadsheet(int line,int column);
        int getLine();
        int getColumn();
        void print_frame(AnsiTerminal& terminal);

        void editCell(int line, int column,string value);
        void set_num(int i,int j, double new_num);
        string getFrame(int line, int column);

        
        ~Spreadsheet();
    private:
        vector<vector<Cell>> frame;
};

#endif