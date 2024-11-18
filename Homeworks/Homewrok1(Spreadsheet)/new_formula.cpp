#include"new_formula.h"
#include"FormulaParser.h"
#include"Cell.h"
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
#define ERR -9999999
#define MAX 1000000000
#define MIN -111111111
string COLUMN_ALPHABET = "ABCDEFGHIJ";
Spreadsheet& FormulaParser::parsing(Spreadsheet& tmp,int i, int j)
{
    bool flag = true;//for controlling if contains function
    bool flag_err = true;
    string delimeters = "+-/*";
    string main_expression = tmp.getFrame(i,j);
    size_t position = main_expression.find_first_of(delimeters);
    double result;
    if(position != string::npos)
    {
        char first_operator = main_expression[position];
        string l_exp = main_expression.substr(1,position);
        string r_exp = main_expression.substr(position+1);
        double l_value;
        double r_value;
        if(!contain_func(l_exp))
        {
            l_value = get_operand_value(l_exp,tmp);
            flag = false;
        }
        else{l_value = func_value(tmp,i,j,main_expression);}
        if(!contain_func(r_exp))
        {
            r_value = get_operand_value(r_exp,tmp);
            flag = false;
        }
        else{r_value = func_value(tmp,i,j,main_expression);}
        if(r_value == ERR || l_value == ERR)
            flag_err = false;
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
    }
    if(flag == true)
    {
        result = func_value(tmp,i,j,main_expression);
    }
    if(flag_err)
        tmp.editCell(i,j,to_string(result));
    else
        tmp.editCell(i,j,"ERROR");
    return tmp;
}

double FormulaParser::func_value(Spreadsheet& tmp,int i,int j,string main_expression)
{
    double result = 0;
    string delimeter = "(";
    size_t pos = tmp.getFrame(i,j).find_first_of(delimeter);
    string expression = tmp.getFrame(i,j).substr(pos);
    if(main_expression.find("SUM") != string::npos)
        result = Sum(expression,tmp);
    else if(main_expression.find("AVER") != string::npos)
        result = Aver(expression,tmp);
    else if(main_expression.find("STDDIV") != string::npos)
        result = Stddev(expression,tmp);
    else if(main_expression.find("MAX") != string::npos)
        result = Max(expression,tmp);
    else if(main_expression.find("MIN") != string::npos)
        result = Min(expression,tmp);
    return result;
}
double FormulaParser::Sum(string expression,Spreadsheet& tmp)
{
    //expression like (A2..A4)
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1,position-1);
    string r_part = expression.substr(position+2,expression.size()-position-3);
    const string first_line = l_part.substr(1);//it keeps 2
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(1);
    int line_last = stoi(last_line);
    int column = COLUMN_ALPHABET.find(l_part[0]);
    double result = 0;
    while(line_first <= line_last)
    {
        double tmp_num = safeStringToDouble(tmp.getFrame(line_first-1,column));
        result += (tmp_num == ERR ? 0 : tmp_num);
        line_first++;
    }
    return result;
}

double FormulaParser::Aver(string expression,Spreadsheet& tmp)
{
    //expression like (A2..A4)
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1,position-1);
    string r_part = expression.substr(position+2,expression.size()-position-3);
    const string first_line = l_part.substr(1);//it keeps 2
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(1);
    int line_last = stoi(last_line);
    int column = COLUMN_ALPHABET.find(l_part[0]);
    double result = 0;
    int quantity = line_last - line_first + 1;
    result = Sum(expression,tmp);
    /*for now it works but it divides sum to total cell unmber it should not contain empty or string cells*/
    /*while(line_first <= line_last)
    {
        result += stod(tmp.getFrame(line_first - 1,column));
        line_first++;
    }*/
    return result/quantity;
}

double FormulaParser::Stddev(string expression,Spreadsheet& tmp)
{
    double average = Aver(expression,tmp);
    double stddev = 0;
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1,position-1);
    string r_part = expression.substr(position+2,expression.size()-position-3);
    const string first_line = l_part.substr(1);//it keeps 2
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(1);
    int line_last = stoi(last_line);
    int column = COLUMN_ALPHABET.find(l_part[0]);
    int quantity = line_last - line_first;
    double sum_of_pow = 0;
    for(int i = line_first;i<=line_last;i++)
    {
        double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1,column));
        tmp_num = (tmp_num == ERR) ? 0 : tmp_num;
        sum_of_pow += pow(tmp_num - average,2);
    }
    sum_of_pow /= (quantity+1);
    stddev = sqrt(sum_of_pow);
    return stddev;
}

double FormulaParser::Max(string expression,Spreadsheet& tmp)
{
    //expression like (A2..A4)
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1,position-1);
    string r_part = expression.substr(position+2,expression.size()-position-3);
    const string first_line = l_part.substr(1);//it keeps 2
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(1);
    int line_last = stoi(last_line);
    int column = COLUMN_ALPHABET.find(l_part[0]);
    double max_num  = safeStringToDouble(tmp.getFrame(line_first-1,column),MIN);
    max_num = (max_num == ERR) ? MIN : max_num ;double next;
    while(line_first <= line_last)
    {
        double tmp_num = safeStringToDouble(tmp.getFrame(line_first-1,column),MIN);
        next = (tmp_num == ERR) ? MIN : tmp_num;
        if(next > max_num)
            max_num = next;
        line_first++;
    }
    return max_num;
}
double FormulaParser::Min(string expression,Spreadsheet& tmp)
{
    //expression like (A2..A4)
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1,position-1);
    string r_part = expression.substr(position+2,expression.size()-position-3);
    const string first_line = l_part.substr(1);//it keeps 2
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(1);
    int line_last = stoi(last_line);
    int column = COLUMN_ALPHABET.find(l_part[0]);
    double min_num  = safeStringToDouble(tmp.getFrame(line_first-1,column),MAX);
    min_num = (min_num == ERR) ? MAX : min_num;
    double next;
    while(line_first <= line_last)
    {
        double tmp_num = safeStringToDouble(tmp.getFrame(line_first-1,column),MAX);
        next = (tmp_num == ERR) ? MAX : tmp_num;
        if(next < min_num)
            min_num = next;
        line_first++;
    }
    return min_num;
}

double FormulaParser::get_operand_value(string expression,Spreadsheet& tmp)
{
    int column = COLUMN_ALPHABET.find(expression[0]);
    const string new_str = expression.substr(1);
    int line = stoi(new_str);
    double num;
    num = safeStringToDouble(tmp.getFrame(line-1,column));
    return num;
}

double FormulaParser::safeStringToDouble(string str, double defaultValue)
{
    if(str.empty())
        return defaultValue;
    try
    {
        return stod(str);
    }
    catch(const std::invalid_argument&)
    {
        return ERR;
    }
}


bool FormulaParser::contain_func(string tmp)
{
    if(tmp.find("SUM") != string::npos
        ||tmp.find("STDDIV") != string::npos
        ||tmp.find("AVER") != string::npos
        ||tmp.find("MAX") != string::npos
        ||tmp.find("MIN") != string::npos)
        return true;
    return false;
}
