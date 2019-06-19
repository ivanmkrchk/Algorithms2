#include "Student.h"

#include <iostream>

Student::Student()
{
    //ctor
}

Student::~Student()
{
    //dtor
}

void Student::print(){
	std::cout << group << " " << surname << " " << name << " " << mean << std::endl;
}
