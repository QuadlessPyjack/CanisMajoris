
#include<iostream>
#include<MathTests\MathTest.h>

#include<Utils\Math\Vector2.h>
#include<Utils\Math\Vector3.h>

namespace TestFramework
{
	static const Vector3 v3A = Vector3(1.0f, 2.0f, 3.0f);
	static const Vector3 v3B = Vector3(3.5f, 6.5f, 9.5f);

	MathTest::MathTest(std::string Name)
    :UnitTestGroup(Name)
	{};

	MathTest::~MathTest() {};

	void MathTest::ExecuteAllTests()
	{
		std::cout << "Executing Test Group: " << GetName() << std::endl;

		std::cout << "Running Vector2 Tests: " << std::endl;

		Vector3 additionCheck = v3A + v3B;
		Vector3 correctValue = Vector3(4.5f, 8.5f, 12.5f);

		if (additionCheck == correctValue)
			std::cout << "*";
		else
			std::cout << "Test Failed! Expected " << correctValue << " got " << additionCheck << std::endl;

	}
}