#ifndef COM_H
#define COM_H

#include "Memory.h"
#include "CPU.h"

class Computer
{
    public:
        Computer(float,int,int,int);
        Computer();

        void setMem(const Memory&);
        void setCpu1(const CPU&);
        void setCpu2(const CPU&);

        Memory getMem() const;
        CPU getCpu1() const;
        CPU getCpu2() const;

        int total_cores() const;
        static int total_mem_usage();
    private:
        Memory mem;
        CPU cp1,cp2;
        static int total_memory;
};

#endif