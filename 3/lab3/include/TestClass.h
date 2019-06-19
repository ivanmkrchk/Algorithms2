#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "SplayTree.h"
#include <vector>

class TestClass
{
	public:
		TestClass();
		virtual ~TestClass();
        void printData();
        void start();

	private:

		SplayTree<std::string, Student>* tree;
		std::vector <Student*> data;

		void loadData(std::istream& in);
		void addElements(int l, int r);
};

#endif // TESTCLASS_H
