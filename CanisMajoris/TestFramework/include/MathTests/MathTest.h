#ifndef MATH_TEST_H
#define MATH_TEST_H

#include<UnitTestGroup.h>

namespace TestFramework
{
	class MathTest: UnitTestGroup
	{
	public:
		MathTest(std::string Name);
		~MathTest();

		void ExecuteAllTests();
	};
}



#endif