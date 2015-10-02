// TestFramework.cpp : Defines the entry point for the console application.
//

#include<iostream>

#include<MathTests\MathTest.h>

int main(int argc, wchar_t* argv[])
{
	TestFramework::MathTest test1("MATH UTILS TEST");
	test1.ExecuteAllTests();
	
	std::getchar();
	return 0;
}

