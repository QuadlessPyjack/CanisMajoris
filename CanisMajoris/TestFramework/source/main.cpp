#include <MathTests/Test_Vector.h>

//__declspec(dllexport) int PullInMyLibrary() { return 0; }

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}