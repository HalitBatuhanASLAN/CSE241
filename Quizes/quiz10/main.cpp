#include<vector>
#include<iostream>

#include"Shape.h"
#include"Circle.h"
#include"Rectangle.h"

template<class T>

class shapeContainer
{
    public:
        shapeContainer() = default;
        void addShape(const T* s){vect.push_back(s);}
        double totalArea(){
            double tot_area = 0;
            for(auto v : vect)
                tot_area += v->area();
            return tot_area;
        }
        int numberOfCircles(){
            int num_of_circle = 0;
            for(auto v : vect)
            {
                Circle* cp = dynamic_cast<Container*>(v);
                if(cp != nullptr)
                    num_of_circle++;
            }
            return num_of_circle;
        }
        ~shapeContainer() = default;
    protected:
        std::vector<T*> vect;
};

int main()
{
    shapeContainer<Shape> sc1,sc2;
    Circle c1(3.0),c2(4.6);
    Rectangle r1(4,5),r2(12,5);

    sc1.addShape(&c1);
    sc1.addShape(&r1);

    sc2.addShape(&c2);
    sc2.addShape(&r2);
    
    std::cout << "Total area of shapes in sc1 and sc2 " << sc1.totalArea() 
              << " " << sc2.totalArea() << std::endl;
    
    std::cout << "Number of circles in sc1 and sc2 " << sc1.numberOfCircles()
              << " " << sc2.numberOfCircles() << std::endl;
    
    return 0;
}