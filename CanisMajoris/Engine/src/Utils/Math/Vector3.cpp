////////////////////////////////////////// 
//! \brief   Vector3 - Canis Majoris Math Utils
//!	\author  Bogdan Vitel
//! \details Vector3 header
//! \date    12/11/2014
//! \todo 
//////////////////////////////////////////

#include<Utils/Math/Vector3.h>

Vector3::Vector3():
x(0.0f),
y(0.0f),
z(0.0f)
{};

Vector3::Vector3(float pozX, float pozY, float pozZ, bool polarCoordsFlag) :
x(pozX),
y(pozY),
z(pozZ),
isPolar(polarCoordsFlag)
{};

void Vector3::Normalize() //!< maintains direction, flattens to 1
{
	if (!isPolar)
	{
		float magnitude = Magnitude();
		if (x != 0)
			x /= magnitude;
		if (y != 0)
			y /= magnitude;
		if (z != 0)
			z /= magnitude;
	}
};
const Vector3 Vector3::Normalized() //!< returns a normalized copy of this vector
{
	if (!isPolar)
	{
		Vector3 vect3 = *this;
		//if (vect3 != Vector3(0,0,0))
		vect3.Normalize();
		return vect3;
	}
	return Vector3::Zero(); //!< NOT IMPLEMENTED
};

float Vector3::Magnitude() //!< returns the length of the vector
{
	if (!isPolar)
	{
		float dist = sqrtf(x*x + y*y + z*z);
		return dist;
	}
	return z; //!< third argument corresponds to magnitude in polar coordinates
};

void Vector3::ToCartesian() //! \todo Update code for converion from Spherical system
{
	isPolar = false;

	float polarX = x;
	
	x = cosf(z) * z;
	y = sinf(z) * z;

	z = cosf(polarX);
};

void Vector3::ToSpherical() //! \todo Get Proper Cartesian - Spherical conversion going
{
	isPolar = true;

	float alpha, beta, dist;
	//!< alpha is angle(XZ)
	//!< beta is angle(YZ)
	alpha = atan2f(z, x);
	beta = atan2f(z, y);
	dist = Magnitude();

	x = alpha;
	y = beta;
	z = dist;
};

std::ostream& operator<<(std::ostream &os, const Vector3 &vect3)
{
	os << vect3.x << ", " << vect3.y << ", " << vect3.z;
	return os;
};

bool& operator==(const Vector3& v1, const Vector3& v2)
{
	bool flag = true;
	//!< Just in case they happen to be *numerically* identical
	if (v1.isPolar == v2.isPolar)
	{
		
		if ((v1.x == v2.x) | (v1.y == v2.y) | (v1.z == v2.z))
			flag = false;
	}
	return flag;
};

bool& operator!=(const Vector3& v1, const Vector3& v2)
{
	bool flag = false;
	//!< Just in case they happen to be *numerically* identical
	if (v1.isPolar == v2.isPolar)
	{
		if ((v1.x == v2.x) | (v1.y == v2.y) | (v1.z == v2.z))
			flag = true;
	}
	return flag;
};

Vector3& operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 sum;
	sum.x = v1.x + v2.x;
	sum.y = v1.y + v2.y;
	sum.z = v1.z + v2.z;

	return sum;
}

Vector3& operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 diff;
	diff.x = v1.x - v2.x;
	diff.y = v1.y - v2.y;
	diff.z = v1.z - v2.z;

	return diff;
}

Vector3& operator*(const Vector3& v1, const Vector3& v2)
{
	Vector3 prod;
	prod.x = v1.x * v2.x;
	prod.y = v1.y * v2.y;
	prod.z = v1.z * v2.z;

	return prod;
};
Vector3& operator*(const float& f1, const Vector3& v2)
{
	Vector3 prod;
	prod.x = f1 * v2.x;
	prod.y = f1 * v2.y;
	prod.z = f1 * v2.z;

	return prod;
};

Vector3& operator*(const Vector3& v1, const float& f2)
{
	Vector3 prod;
	prod.x = f2 * v1.x;
	prod.y = f2 * v1.y;
	prod.z = f2 * v1.z;

	return prod;
};

Vector3& operator/(const Vector3& v1, const float& f2)
{
	Vector3 div;
	div.x = v1.x / f2;
	div.y = v1.y / f2;
	div.z = v1.z / f2;

	return div;
};

Vector3::~Vector3()
{};