#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "OptBinSearchTree.h"
#include <vector>

class TestClass
{
	public:
		TestClass();
		virtual ~TestClass();
        void printData();
        void start();

	private:

		OptBinSearchTree<std::string, Student>* tree;
		std::vector <std::pair<std::string, Student*>> data;

		void loadData(std::istream& in);
		void setRandomWeights();
};

#endif // TESTCLASS_H
