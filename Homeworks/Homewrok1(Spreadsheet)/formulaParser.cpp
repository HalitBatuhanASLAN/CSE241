#include"FormulaParser.h"
#include"Spreadsheet.h"
#include"Cell.h"

#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include<regex>
#include<vector>
using namespace std;

const string COLUMN_ALPHABET = "ABCDEFGHIJ";

void FormulaParser::set_type(int i,int j)
{
    if(tmp.getFrame(i,j).find("SUM"))
        type = SUM;
    else if(tmp.getFrame(i,j).find("AVER"))
        type = AVER;
    else if(tmp.getFrame(i,j).find("STDDEV"))
        type = STDDEV;
    else if(tmp.getFrame(i,j).find("MAX"))
        type = MAX;
    else if(tmp.getFrame(i,j).find("MIN"))
        type = MIN;
    else
        type = OTHER;
}
formula_type FormulaParser::get_type(int i,int j)
{
    return type;
}

void FormulaParser::relevant_func(int i,int j)
{
    switch(type)                    
    {
        case SUM:
            //sSum();
            break;
        case AVER:

            break;
        case STDDEV:
            break;
        case MAX:
            break;
        case MIN:
            break;
        case OTHER:
            other_calc(i,j);
            break;
    }
}


/*void Sum()
{

}*/

void FormulaParser::other_calc(int i,int j)
{
    double res = 12,l_res,r_res;
    string expression = tmp.getFrame(i,j);
    stringstream ss(expression);
    string l_item;
    string r_item;
    string delimeters = "+-/*";
    
    size_t start = 0;
    size_t end = expression.find_first_of(delimeters);
    char current_delimeter;
    
    while(true)
    {
        if (end > start)
            l_item = expression.substr(start,end - start);
        current_delimeter = expression[end];
        start = end + 1;
        end = expression.find_first_of(delimeters,start);
        /*r_item = expression.substr(start,end - start);*/
        switch(current_delimeter)
        {
            case '+':
                if(l_item[0] <= '9' && l_item[0] >= '0')
                    l_res = stod(l_item);
                else
                    l_res = get_operand_value(l_item);
                
                /*if(r_item[0] <= '9' && r_item[0] >= '0')
                    r_res = stod(r_item);
                else
                    r_res = get_operand_value(r_item);
                
                res = l_res + r_res;*/
                res += l_res;
                break;
            case '-':
                if(l_item[0] <= '9' && l_item[0] >= '0')
                    l_res = stod(l_item);
                else
                    l_res = get_operand_value(l_item);
                
                if(r_item[0] <= '9' && r_item[0] >= '0')
                    r_res = stod(r_item);
                else
                    r_res = get_operand_value(r_item);
                
                res = l_res - r_res;
                break;
            case '*':
                if(l_item[0] <= '9' && l_item[0] >= '0')
                    l_res = stod(l_item);
                else
                    l_res = get_operand_value(l_item);
                
                if(r_item[0] <= '9' && r_item[0] >= '0')
                    r_res = stod(r_item);
                else
                    r_res = get_operand_value(r_item);
                
                res = l_res * r_res;
                break;
            case '/':
                /*add controller for divider 0 condition*/
                if(l_item[0] <= '9' && l_item[0] >= '0')
                    l_res = stod(l_item);
                else
                    l_res = get_operand_value(l_item);
                
                if(r_item[0] <= '9' && r_item[0] >= '0')
                    r_res = stod(r_item);
                else
                    r_res = get_operand_value(r_item);
                
                res = l_res / r_res;
                break;
        }
        if(end == string::npos)
            break;
    }
    tmp.set_num(i,j,res);
    string res_str = to_string(res);
    tmp.editCell(tmp.getLine(),tmp.getColumn(),res_str);
}


double FormulaParser::get_operand_value(const string operand)
{
    int index_column = COLUMN_ALPHABET.find(operand[0]);
    string line_part = operand.substr(1);
    int index_line = stoi(line_part);
    double result = stod(tmp.getFrame(index_line - 1,index_column));
    return result;
}