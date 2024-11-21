#include"new_formula.h"
#include"FormulaParser.h"
#include"Cell.h"
#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>//for all_of_it
using namespace std;
#define ERR -9999
#define MAX 1000000000
#define MIN -111111111
string COLUMN_ALPHABET = "ABCDEFGHIJ";

Spreadsheet& FormulaParser::parsing(Spreadsheet& tmp, int i, int j)
{
    bool flag = true;
    bool flag_err = true;
    string delimeters = "+-/*";
    string main_expression = tmp.getFrame(i, j);
    int count = countDelimiters(main_expression, delimeters);
    size_t position;
    size_t next_pos;
    bool first_iteration = true;
    double result = 0;
    bool is_func = contain_func(main_expression);
    if(count == 0 && !is_func)
    {
        result = (get_operand_value(main_expression.substr(1),tmp));//=A5 -> A5
    }
    while (count > 0)
    {
        position = main_expression.find_first_of(delimeters);
        if (position != string::npos)
        {
            char first_operator = main_expression[position];
            string l_exp;
            if (main_expression[0] == '=')
                l_exp = main_expression.substr(1, position - 1);
            else
                l_exp = main_expression.substr(0, position);

            string r_exp = main_expression.substr(position + 1);
            next_pos = r_exp.find_first_of(delimeters);
            if (next_pos != string::npos)
                r_exp = r_exp.substr(0, next_pos);

            double l_value, r_value;
            if(first_iteration) // Only set l_value in the first iteration
            {
                if (!contain_func(l_exp))
                {
                    l_value = get_operand_value(l_exp, tmp);
                    flag = false;
                }
                else
                {
                    l_value = func_value(tmp, i, j, l_exp);
                }
                result = l_value;
                first_iteration = false;
            }

            if (!contain_func(r_exp))
            {
                r_value = get_operand_value(r_exp, tmp);
                flag = false;
            }
            else
            {
                r_value = func_value(tmp, i, j, r_exp);
            }

            if (r_value == ERR || l_value == ERR)
                flag_err = false;

            switch (first_operator)
            {
                case '+':
                    result += r_value;
                    break;
                case '-':
                    result -= r_value;
                    break;
                case '*':
                    result *= r_value;
                    break;
                case '/':
                    if (r_value == 0)
                        flag_err = false;
                    else
                        result /= r_value;
                    break;
                default:
                    flag_err = false;
            }

            if (next_pos != string::npos)
                main_expression = main_expression.substr(position + next_pos + 1);
        }

        count--;
    }
    if(flag && is_func)
    {
        result = func_value(tmp,i,j,main_expression);
    }
    if (flag_err)
    {
        tmp.set_num(i, j, (result));
        //tmp.editCell(i, j, to_string(result));
    }
    else
        tmp.editCell(i, j, "ERROR");

    return tmp;
}

int FormulaParser::countDelimiters(const string& input, const string& delimiters)
{
    int count = 0;
    for(char c : input)
    {
        if(delimiters.find(c) != std::string::npos)
            count ++;
    }
    return count;
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
    
    const string first_line = l_part.substr(letter_count(l_part));//it keeps 2
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(letter_count(r_part));
    int line_last = stoi(last_line);
    //int column_starting = COLUMN_ALPHABET.find(l_part[0]);
    //int end_column = COLUMN_ALPHABET.find(r_part[0]);
    int column_starting = column_value(l_part);
    int end_column = column_value(r_part);
    double result = 0;
    while(line_first <= line_last)
    {
        int col = column_starting;
        while(col <= end_column)
        {
            double tmp_num = safeStringToDouble(tmp.getFrame(line_first-1,col));
            result += (tmp_num == ERR ? 0 : tmp_num);
            col++;
        }
        line_first++;
    }
    return result;
}
double FormulaParser::Aver(string expression, Spreadsheet& tmp)
{
    // expression like (A2..A4)
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1, position - 1); // Sol taraf (örneğin A2)
    string r_part = expression.substr(position + 2, expression.size() - position - 3); // Sağ taraf (örneğin A4)

    // Satır numaralarını ayır
    const string first_line = l_part.substr(letter_count(l_part)); // Örneğin "2"
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(letter_count(r_part)); // Örneğin "4"
    int line_last = stoi(last_line);

    // Sütun değerlerini al
    int column_starting = column_value(l_part); // Örneğin A = 0, B = 1, AA = 26
    int end_column = column_value(r_part);

    // Sum fonksiyonunu kullanarak toplamı hesapla
    double result = Sum(expression, tmp);

    // Geçerli hücrelerin sayısını hesapla
    int valid_cells = 0;
    while (line_first <= line_last) {
        int col = column_starting;
        while (col <= end_column) {
            double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, col));
            if (tmp_num != ERR) { // Geçerli bir sayıysa sayacı artır
                valid_cells++;
            }
            col++;
        }
        line_first++;
    }

    return valid_cells > 0 ? result / valid_cells : 0; // Geçerli hücre yoksa 0 döndür
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

double FormulaParser::Max(string expression, Spreadsheet& tmp)
{
    // expression like (A2..A4)
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1, position - 1); // Sol taraf (örneğin A2)
    string r_part = expression.substr(position + 2, expression.size() - position - 3); // Sağ taraf (örneğin A4)

    // Satır numaralarını ayır
    const string first_line = l_part.substr(letter_count(l_part)); // Örneğin "2"
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(letter_count(r_part)); // Örneğin "4"
    int line_last = stoi(last_line);

    // Sütun değerlerini al
    int column_starting = column_value(l_part); // Örneğin A = 0, B = 1, AA = 26
    int end_column = column_value(r_part);

    double max_num = MIN; // Başlangıçta minimum değeri ata

    while (line_first <= line_last) {
        int col = column_starting;
        while (col <= end_column) {
            double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, col), MIN);
            if (tmp_num != ERR && tmp_num > max_num) { // Geçerli sayıysa kontrol et
                max_num = tmp_num;
            }
            col++;
        }
        line_first++;
    }

    return max_num;
}
double FormulaParser::Min(string expression, Spreadsheet& tmp)
{
    // expression like (A2..A4)
    string delim = ".";
    size_t position = expression.find_first_of(delim);
    string l_part = expression.substr(1, position - 1); // Sol taraf (örneğin A2)
    string r_part = expression.substr(position + 2, expression.size() - position - 3); // Sağ taraf (örneğin A4)

    // Satır numaralarını ayır
    const string first_line = l_part.substr(letter_count(l_part)); // Örneğin "2"
    int line_first = stoi(first_line);
    const string last_line = r_part.substr(letter_count(r_part)); // Örneğin "4"
    int line_last = stoi(last_line);

    // Sütun değerlerini al
    int column_starting = column_value(l_part); // Örneğin A = 0, B = 1, AA = 26
    int end_column = column_value(r_part);

    double min_num = MAX; // Başlangıçta maksimum değeri ata

    while (line_first <= line_last) {
        int col = column_starting;
        while (col <= end_column) {
            double tmp_num = safeStringToDouble(tmp.getFrame(line_first - 1, col), MAX);
            if (tmp_num != ERR && tmp_num < min_num) { // Geçerli sayıysa kontrol et
                min_num = tmp_num;
            }
            col++;
        }
        line_first++;
    }

    return min_num;
}

double FormulaParser::get_operand_value(string expression,Spreadsheet& tmp)
{
    if(std::all_of(expression.begin(), expression.end(), ::isdigit))
        return stod(expression);
    int counter_letter = 0;
    for(char c:expression)
        if(isalpha(c))counter_letter++;
    int column = 0,i = 0;
    while (counter_letter > i) {
        column = column * 26 + (toupper(expression[i]) - 'A' + 1); // Correct the calculation for base-26
        i++;
    }
    column -= 1;
    const string new_str = expression.substr(counter_letter);
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



int FormulaParser::letter_count(string expression)
{
    int count = 0;
    for (char c : expression) {
        if (isalpha(c)) {
            count++;
        } else {
            break; // Sayıya ulaştığımızda dur
        }
    }
    return count;
}

int FormulaParser::column_value(string operand)
{
    int count = letter_count(operand); // Sütun adının uzunluğunu al
    string columnName = operand.substr(0, count); // Sütun kısmını al
    int column = 0;
    for (char c : columnName) {
        column = column * 26 + (toupper(c) - 'A' + 1);
    }
    return column - 1;
}
