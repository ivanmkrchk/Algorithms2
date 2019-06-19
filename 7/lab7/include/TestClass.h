#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "BinomialHeap.h"
#include <vector>

class TestClass
{
	public:
		TestClass();
		virtual ~TestClass();
        void printData();
        void start();

	private:

		BinomialHeap<std::string, Student>* heap;
		std::vector <Student*> data;

		void loadData(std::istream& in);
		void addElements(int l, int r);
};

#endif // TESTCLASS_H
