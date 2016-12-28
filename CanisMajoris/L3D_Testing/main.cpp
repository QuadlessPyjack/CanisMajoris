#include <iostream>
#include <Lupus3DImpex/FileInfo.h>
#include "l3dTest.h"

int main(int argc, char* argv[])
{
	std::cout << "Executing L3D Test" << std::endl;

	L3D_TEST test;
	
	std::cout << "Creating blank file test.." << std::endl;
	test.SaveFileTest();

	getchar();

	return 0;
}
