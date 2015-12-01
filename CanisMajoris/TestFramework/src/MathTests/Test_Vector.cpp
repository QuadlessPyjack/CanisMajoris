#include <MathTests/Test_Vector.h>

Vector2 VECTOR2_REFERENCE(5.0f, 5.0f);
Vector2 VECTOR2_ADDER(3.0f, 3.0f);
Vector2 VECTOR2_SCALAR_ADDITION_RESULT(8.0f, 8.0f);
Vector2 VECTOR2_SCALAR_SUBSTRACTION_RESULT(2.0f, 2.0f);

float SCALAR_F = 3.0f;
int   SCALAR_I = 3;

TEST(Test_Vector2, Assignment)
{
	Vector2 v2(SCALAR_F, SCALAR_I);

	EXPECT_EQ(v2.x, SCALAR_F, "Foo");
	EXPECT_EQ(v2.y, SCALAR_I);

	EXPECT_EQ(v2.x, v2.y);
}

TEST(Test_Vector2, Methods)
{
	Vector2 v2(0.0f, 0.0f);
	Vector2 v2_B = VECTOR2_REFERENCE.Zero();

	EXPECT_EQ(v2, Vector2::Zero());
}