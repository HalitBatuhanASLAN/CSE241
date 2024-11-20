#ifndef STUDENT_H
#define STUDENT_H

#include<string>
using std::string;
#include"Person.h"

namespace
{double verify_gpa(double d){return(d>=0 && d<=4) ? d : 0.0;}}

namespace GTUSpace
{
    class Student:public Person
    {
        public:
            Student(const string& n,const string& ma,double d):Person(n),major(ma),GPA(verify_gpa(d)){}
            
            double getGPA()const{return GPA;}
            void setGPA(double d){GPA = verify_gpa(d);}

            string getMajor()const{return major;}
            void setMajor(const string& ma){major = ma;}
        private:
            string major;
            double GPA;
    };
}

#endif