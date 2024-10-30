#ifndef MATRIX2D_H
#define MATRIX2D_H

#include<iostream>
#include<cstdlib>//for exit
#include<vector>
using namespace std;

class Matrix2D
{
    public:
        Matrix2D(int line,int column);

        const int getLine(){return data.size();}
        const int getColumn(){return data[0].size();}
        void setElements(int line,int column,int element)
        {
            if( !isValid(line,column)) exit(-1);
            data[line][column] = element;
        }
        int getElement(int line, int column)
        {
            if( !isValid(line,column)) exit(-1);
            return data[line][column];            
        }

        Matrix2D operator+(Matrix2D& mat) const;
        bool operator==(Matrix2D& mat) const;
    private:
        vector< vector<int> > data;
        bool isValid(int line, int column) const
        {
            if( line < 0 || column < 0 || line >= getLine() || column >= getColumn())
                return false;
            return true;
        }
        bool areSameSize(Matrix2D &other) const
        {
            if(getLine() == other.getLine() && getColumn() == other.getColumn())
                return true;
            return false;
        }
};

ostream& operator<<(ostream& out,const Matrix2D& m);
Matrix2D operator-(const Matrix2D& m);

#endif