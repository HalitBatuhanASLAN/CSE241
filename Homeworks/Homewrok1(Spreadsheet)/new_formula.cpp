#include"new_formula.h"
#include"FormulaParser.h"
#include"Cell.h"
#include<iostream>
#include<string>
using namespace std;
string COLUMN_ALPHABET = "ABCDEFGHIJ";
Spreadsheet& FormulaParser::parsing(Spreadsheet& tmp,int i, int j)
{
    string delimeters = "+-/*";
    string expression = tmp.getFrame(i,j);
    size_t position = expression.find_first_of(delimeters);
    char first_operator = expression[position];
    string l_exp = expression.substr(1,position);
    string r_exp = expression.substr(position+1);

    double l_value = get_operand_value(l_exp,tmp);
    double r_value = get_operand_value(r_exp,tmp);
    //double r_value = 10;
    double result;
    switch(first_operator)
    {
        case '+':
            result = l_value + r_value;
            break;
        case '-':
            result = l_value - r_value;
            break;
        case '*':
            result = l_value * r_value;
            break;
        case '/':
            result = l_value / r_value;
            break;
        default:
            break;
    }
    tmp.editCell(i,j,to_string(result));
    return tmp;
}

double FormulaParser::get_operand_value(string expression,Spreadsheet& tmp)
{
    int column = COLUMN_ALPHABET.find(expression[0]);
    const string new_str = expression.substr(1);
    int line = stoi(new_str);
    double num = stod(tmp.getFrame(line -1,column));
    return num;
}