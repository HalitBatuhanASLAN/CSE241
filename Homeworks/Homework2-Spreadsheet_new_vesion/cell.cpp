#include"Cell.h"

Cell::Cell(){}
void Cell::setCell(const string& in){tmp = in;}
const string Cell::getCell(){return tmp;}
Cell::~Cell() { }