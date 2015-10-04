#include <iostream>
#include <string>

namespace TestFramework
{
	void inline printError(std::string message) {
		std::cout << "[ERROR] " << message << '\n';
	};

	enum TEST_STATUS
	{
		TEST_SUCCESS,
		TEST_FAIL
	};
}