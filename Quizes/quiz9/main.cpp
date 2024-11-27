#include<list>
#include<vector>
#include<iostream>
using namespace std;

class Container
{
    public:
        virtual void add(int i) = 0;
        virtual int remove() = 0;
        bool empty() const{return data.size() == 0;};
    protected:
        list<int> data;
};

//Assume that it works as FIFO mentality
class Stack:public Container
{
    public:
        Stack() : Container(){}
        void add(int i){data.push_back(i);}
        int remove()
        {
            data.pop_front();
            return 0;
        }
};

//Assume that it works as LIFO mentality
class Queue:public Container
{
    public:
        Queue() : Container(){}
        void add(int i){data.push_back(i);}
        int remove()
        {
            data.pop_back();
            return 0;
        }
};

void remove_elements(vector<Container*>&elements)
{
    for(auto ve:elements)
        while(!ve->empty())
            ve->remove();
}

int main()
{
    Stack s1,s2;
    Queue q1,q2;

    s1.add(10);
    s2.add(20);
    q1.add(30);
    q2.add(40);
    s2.add(100);
    q1.add(5);
    
    vector<Container*>elements;
    elements.push_back(&s1);
    elements.push_back(&s2);
    elements.push_back(&q1);
    elements.push_back(&q2);

    remove_elements(elements);

    return 0;
}