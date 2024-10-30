#include "matrix2D.h"
#include<iostream>
using namespace std;

Matrix2D::Matrix2D(int line, int column)
{
    if(line < 1 || column < 1)  exit(-1);
    /*it creates a vector of vector with column size and assigning them 0 with line size
    data = vector<vector<int> >(line,vector<int>(column,0));*/
    //another way is
    vector<int>line_vec(column,0);
    for(int i = 0;i<line;i++)
        data.push_back(line_vec);
}
bool Matrix2D::operator==(Matrix2D& mat)const
{
    /*it is already valid for vectors
    return(mat.data == data);*/
    if( !areSameSize(mat))
        return false;
    for(int i = 0;i<getLine();i++)
    {
        for(int j = 0;j<getColumn();j++)
        {
            if(data[i][j] != mat.data[i][j])
                return false;
        }
    }
    return true;
}
Matrix2D Matrix2D::operator+(Matrix2D& mat)const
{
    if(!areSameSize(mat))
        exit(-1);
    Matrix2D res = mat;
    for(int i = 0;i<getLine();i++)
    {
        for(int j = 0;j<getColumn();j++)
            res.data[i][j] += getElement(i,j);//we can write += data[i][j] too
    }
    return res;
}
Matrix2D operator-(const Matrix2D& m)
{
    Matrix2D res(m,getline(),m.getColumn());
    for(int i = 0;i<getLine();i++)
    {
        for(int j = 0;j<getColumn();j++)
            res.data[i][j] = -getElement(i,j);
    }
    return res;    
}
ostream& operator<<(ostream& out,const Matrix2D& m)
{
    for(int i = 0;i< m.getLine();i++)
    {
        for(int j = 0;j< m.getColumn();j++)
            out << m.getElement(i,j) << " ";
        out << endl;
    }
    return out;
}