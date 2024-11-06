#ifndef GTUS_H
#define GTUS_H
#include<iostream>
using namespace std;
class GTUString
{
    public:
        GTUString();
        GTUString(const char* cstr);
        ~GTUString();

        char &operator[](int i);
        char operator[](int i)const;
        int len()const;
        GTUString &operator+=(const GTUString& tmp);
        friend bool operator==(const GTUString& s1,const GTUString& s2);
        friend ostream& operator<<(ostream& out,const GTUString& tmp);

    private:
        char* str;
};
ostream& operator<<(ostream& out,const GTUString& tmp);
bool operator==(const GTUString& s1,const GTUString& s2)
{
    //return (strcmp(s1.str, s2.str) == 0);
    if(s1.len() != s2.len()) return false;
    for(int i = 0;i<s1.len();i++)
    {
        if(s1.str[i] != s2.str[i])
            return false;
    }
    return true;
}

#endif