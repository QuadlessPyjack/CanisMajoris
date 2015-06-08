#ifndef UNITTEST_H
#define UNITTEST_H

////////////////////////////////////////////////// 
//! \details UnitTest
//  Bogdan Vitel - Canis Majoris Test Framework
//	Base class for unit tests
//  Created: 07/04/2015
//! \todo 
////////////////////////////////////////////////

#include<string>

namespace TestFramework
{
	class UnitTestGroup
	{
	public:
		UnitTestGroup(std::string Name);
		std::string GetName() { return m_name; };
		~UnitTestGroup();
		virtual void ExecuteAllTests() = 0;

	private:
		std::string m_name;
	};
}

#endif