#include "PartA.h"
#include "Memory.h"
#include "CPU.h"

int Computer::total_memory = 0;

Computer::Computer(float speed,int cores, int tot_mem, int used_mem):
    mem(tot_mem), cp1(speed,cores), cp2(speed,cores)
    {total_memory += mem.getTotalCapacity();}
Computer::Computer():Computer(0.0f,0,0,0){};

void Computer::setMem(const Memory& m) {mem = m;}
void Computer::setCpu1(const CPU& c1) {cp1 = c1;}
void Computer::setCpu2(const CPU& c2) {cp2 = c2;}

Memory getMem() const {return mem;}
CPU getCpu1() const {return cp1;}
CPU getCpu2() const {return cp2;}

int total_cores() const {return cp1.getCores() + cp2.getCores();}
int total_mem_usage() {return total_memory;}