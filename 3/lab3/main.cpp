#include <iostream>

#include "TestClass.h"

using namespace std;

int main()
{
	TestClass test = TestClass();
	test.printData();

	test.start();
	test.~TestClass();

	return 0;
}
