#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student
{
    public:
        Student();
        virtual ~Student();
        void print();

        std::string name;
        std::string surname;
        std::string group;
        double mean;
};

#endif // STUDENT_H
