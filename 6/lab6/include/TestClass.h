#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "BPlusTree.h"
#include <vector>

class TestClass
{
	public:
		TestClass();
		virtual ~TestClass();
        void printData();
        void start();

	private:

		BPlusTree<std::string, Student>* tree;
		std::vector <Student*> data;

		void loadData(std::istream& in);
		void addElements(int l, int r);
};

#endif // TESTCLASS_H
