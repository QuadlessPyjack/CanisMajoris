#include "TestUtils.inl"
#include "Test.h"

namespace TestFramework {
	Test::Test(std::string name, int& outStatus)
	{

		outStatus = TestFramework::TEST_STATUS::TEST_SUCCESS;
	}

}