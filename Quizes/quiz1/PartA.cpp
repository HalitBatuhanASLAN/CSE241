#include<iostream>
#include<string>

using namespace std;

int main()
{
        string str1 = "Hello", str2 = "World", str3;
        str3 = str1;
        cout<< "String 1 : " << str1 << "\nString 2 : " << str2
            << "\nString 3 : " << str3 << endl;

        if(str1 < str2)
                cout<< "String 1 is less than string 2\n";
        return 0;
}