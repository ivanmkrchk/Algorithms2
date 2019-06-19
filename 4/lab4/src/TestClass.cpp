#include "TestClass.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

TestClass::TestClass()
{
	std::ifstream in("database.txt");
	loadData(in);
	in.close();

	printData();
	srand(time(0));
}

TestClass::~TestClass()
{
	tree->~OptBinSearchTree();
	delete tree;
}

void TestClass::start(){

	tree = new OptBinSearchTree<std::string, Student>();

	while(true){

		getchar();
		setRandomWeights();
		tree->buildOptTree();
		int cost = tree->calcOptTree();
		std::cout << "MIN COST = " << cost << '\n';

		tree->print();
		std::cout << '\n';
	}
}

void TestClass::loadData(std::istream& in){

    int i = 0;
    while (!in.eof()){

		data.push_back(std::make_pair("", new Student()));
        getline(in, data[i].second->group, '\t');
        getline(in, data[i].second->surname, '\t');
        getline(in, data[i].second->name, '\t');

        std::string mean;
        getline(in, mean, '\n');

 //       std::string frequency;
  //      getline(in, frequency, '\n');

        data[i].second->mean = atof(mean.c_str());
 //       data[i].second->frequency = atoi(frequency.c_str());
        data[i].first = data[i].second->surname;
        i++;
    }
    data.erase(data.begin() + data.size()-1);
}

void TestClass::printData(){

	for (int i = 0; i < data.size(); i++){
		data[i].second->print();
	}
}

void TestClass::setRandomWeights(){

	for (int i = 0; i < data.size(); i++){

		int x = rand() % 100 + 1;
		data[i].second->frequency = x;
	}

	tree->setData(data);
}

