#include <iostream>
#include "CalleeVariable.h"
using namespace std;
#define EXE_NAME "CallerLogger"

void basicExample()
{
	CalleeVariable<double> var(EXE_NAME, 1.2);
	var = 3.415926;
	double newVar = var + 5;
	newVar = var - 1;
	cout << newVar << endl;

	var += 0.12345;
	var -= 0.0000000123456;
	var *= 1.23456789;
	var /= 0.987654321;
	var = var + 12.321;

	var.printCalleeInfo();
}

class PublicClass
{
	public:
		CalleeVariable<double> dynamic;

		PublicClass();
};

PublicClass::PublicClass() : dynamic(EXE_NAME, 0.0)
{
}

void foo2(PublicClass *publicClass)
{
	publicClass->dynamic /= 0.000111;
}

void foo1(PublicClass *publicClass)
{
	publicClass->dynamic += 1.23456789;
	foo2(publicClass);
}

void advanceExample()
{
	PublicClass publicClass;
	publicClass.dynamic *= 0.33;
	foo1(&publicClass);
	publicClass.dynamic -= 0.33;

	publicClass.dynamic.printCalleeInfo();
}

int main()
{
	cout << "Hello CallerLogger !!!" << endl;

	cout << "============ basicExample() ==============================" << endl;
	basicExample();

	cout << "============ advanceExample() ==============================" << endl;
	advanceExample();

	return 0;
}
