#include "TestClass.h"

#include <iostream>
#include <fstream>

TestClass::TestClass()
{
	std::ifstream in("database.txt");
	loadData(in);
	in.close();

	heap = new FibHeap<std::string, Student>();
	printData();
}

TestClass::~TestClass()
{
	delete heap;
}

void TestClass::start(){
	std::string c;
	double i;
	std::string s, t;

	std::cin >> c;
	while (c != "e"){

		if (c == "i"){
			std::cin >> i;
			if (i >= 1 && i <= 24){
				addElements((int)i-1,(int)i-1);
				std::cout << "Student " << data[i-1]->surname << " successfully added\n";
			}
			else std::cout << "Incorrect index\n";
		}
		else if (c == "dmin"){

			Student* student = heap->extractMinimum();
			if (student){
				std::cout << "Student " << student->surname << " successfully deleted\n";
			}
			else std::cout << "There are no students in heap " << s << '\n';
		}
		else if (c == "min"){

			Student* student = heap->getMinimum();
			if (student)
					student->print();
			else std::cout << "There are no students in heap\n";
		}
		else if (c == "p") heap->print();

		std::cin >> c;
	}
}

void TestClass::loadData(std::istream& in){

    int i = 0;
    while (!in.eof()){

		data.push_back(new Student());
        getline(in, data[i]->group, '\t');
        getline(in, data[i]->surname, '\t');
        getline(in, data[i]->name, '\t');

        std::string mean;
        getline(in, mean, '\n');

        data[i]->mean = atof(mean.c_str());
        i++;
    }
    data.erase(data.begin() + data.size()-1);
}

void TestClass::printData(){

	for (int i = 0; i < data.size(); i++){
		data[i]->print();
	}
}

void TestClass::addElements(int l, int r){

	for (int i = std::max(0,l); i <= std::min(r,(int)data.size()-1); i++)
		heap->insert(data[i]->surname, data[i]);
}
