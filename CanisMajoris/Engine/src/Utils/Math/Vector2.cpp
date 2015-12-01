////////////////////////////////////////// 
//! \brief   Vector2 - Canis Majoris Math Utils
//!	\author  Bogdan Vitel
//! \details Vector2 header - A 2D Vector Utility Class
//! \date    12/11/2014
//! \todo	 Add Polar Coordinate Support (overload, conversion methods)
//////////////////////////////////////////

#include<Utils/Math/Vector2.h>

Vector2::Vector2():
x(0.0f),
y(0.0f)
{};

Vector2::Vector2(float pozX, float pozY, bool polarCoordsFlag) :
x(pozX),
y(pozY),
isPolar(polarCoordsFlag)
{};

void Vector2::Normalize() //!< maintains direction, flattens to 1
{
	if (!isPolar)
	{
		float magnitude = Magnitude();
		if (x != 0)
			x /= magnitude;
		if (y != 0)
			y /= magnitude;
	}
};
const Vector2 Vector2::Normalized() //!< returns a normalized copy of this vector
{
	if (!isPolar)
	{
		Vector2 vect2 = *this;
		//if (vect2 != Vector2(0,0,0))
		vect2.Normalize();
		return vect2;
	}
	return Vector2::Zero(); //!< NOT IMPLEMENTED
};

float Vector2::Magnitude() //!< returns the length of the vector
{
	if (!isPolar)
	{
		float dist = sqrtf(x*x + y*y);
		return dist;
	}
	return y; //!< second argument corresponds to magnitude in polar coordinates
};

void Vector2::ToCartesian() //! \todo Update code for converion from Polar system
{
	float polarX = x;

	x = y * cosf(x);
	y = y * sinf(polarX);

	isPolar = false;
};

void Vector2::ToPolar() //! \todo Get Proper Cartesian - Polar conversion going
{
	float alpha, dist;
	//!< alpha is angle(XZ)
	alpha = atan2f(y, x);
	dist = Magnitude();

	x = alpha;
	y = dist;

	isPolar = true;
};

std::ostream& operator<<(std::ostream &os, const Vector2 &vect2)
{
	os << vect2.x << ", " << vect2.y;
	return os;
};

bool& operator==(const Vector2& v1, const Vector2& v2)
{
	bool flag = false;
	//!< Just in case they happen to be *numerically* identical
	if (v1.isPolar == v2.isPolar)
	{
		if ((v1.x == v2.x) && (v1.y == v2.y))
			flag = true;
	}
	return flag;
};

bool& operator!=(const Vector2& v1, const Vector2& v2)
{
	bool flag = false;
	//!< Just in case they happen to be *numerically* identical
	if (v1.isPolar == v2.isPolar)
	{
		if ((v1.x == v2.x) | (v1.y == v2.y))
			flag = true;
	}
	return flag;
};

Vector2::~Vector2()
{};