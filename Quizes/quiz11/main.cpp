#include<iostream>
#include<vector>
#include<list>
#include<forward_list>
#include<exception>
using namespace std;

template<class T,class C>
typename C::iterator findInContainer(const C& data,const T element)
{
    for(auto it = data.begin();it!= data.end();it++)
        if(*it == element)
            retrun it;
    throw runtime_error("Element not found\n");
}

int main()
{
    vector<int>v1 = {1,2,3,4,5};
    list<double>l1 = {1.0,5.6,9.8};
    forward_list<int>f1 = {9,8,7,6};
    try
    {
        cout << "Element found :" << *findInContainer(v1,5);
        cout << "Element found :" << *findInContainer(l1,0);
        cout << "Element found :" << *findInContainer(f1,6);
    }
    catch(exception& e)
    {
        cerr << e.what() << '\n';
    }
}