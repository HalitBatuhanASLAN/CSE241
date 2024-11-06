#include"GTUString.h"
#include<iostream>
using namespace std;
#include<cstring>
GTUString::GTUString()
{
    str = new char[1];
    str[0] = '\0';
}
GTUString::GTUString(const char* cstr)
{
    if(cstr == nullptr)
    {
        str = new char[1];
        str[0] = '\0';
    }
    else
    {
        str = new char[strlen(cstr) + 1];
        strcpy(str,cstr);
    }
}
GTUString::~GTUString(){delete[] str;}

char &GTUString::operator[](int i)
{
    if(i<0 || i>=len()) exit(-1);
    return str[i];
}
char GTUString::operator[](int i)const
{
    if(i<0 || i>=len()) exit(-1);
    return str[i];
}
int GTUString::len()const
{
    char* tmp = str;
    while(*tmp !='\0') tmp++;
    return(tmp - str);
}
GTUString &GTUString::operator+=(const GTUString& tmp)
{
    char *old = str;
    char *str = new char[len() + tmp.len() + 1];
    strcpy(str,old);
    strcat(str,tmp.str);
    delete[] old;
    return *this;
}

ostream& operator<<(ostream& out,const GTUString& tmp)
{
    //out << tmp.str;
    for(int i = 0;i<tmp.len();i++)
        out << tmp.str[i];
    return out;
}