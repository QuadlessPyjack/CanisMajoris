#ifndef VECTOR3_H
#define VECTOR3_H
////////////////////////////////////////// 
//! \brief   Vector3 - Canis Majoris Math Utils
//!	\author  Bogdan Vitel
//! \details Vector3 header - A 3D Vector Utility Class
//! \date    12/11/2014
//! \todo	 Vector2 should derive from Vector3 because they're fucking identical
//////////////////////////////////////////
#include<EngineDllExport.h>

#include<iostream>
#include "Vector2.h"

// forward declaration
namespace Math { class Vector2; }

class CM_ENGINE_API Vector3
{
public:
	Vector3();
	//!< \todo argument names are misleading. change to something more general
	Vector3(float pozX, float pozY, float pozZ, bool polarCoordsFlag = false);

	inline static Vector3 Vector3::Zero() //!< vector3(0, 0, 0)
	{
		return Vector3(0, 0, 0);
	};

	inline static Vector3 Vector3::Up() //!< vector3(0,0,1)
	{
		return Vector3(0, 0, 1);
	};

	inline static Vector3 Vector3::Down() //!< vector3(0,0,-1)
	{
		return Vector3(0, 0, -1);
	};

	inline static Vector3 Vector3::Right() //!< vector3(1, 0, 0)
	{
		return Vector3(1, 0, 0);
	};

	inline static Vector3 Vector3::Left() //!< vector3(-1, 0, 0)
	{
		return Vector3(-1, 0, 0);
	};

	inline static Vector3 Vector3::Forward() //!< vector3(0, 1, 0)
	{
		return Vector3(0, 1, 0);
	};

	inline static Vector3 Vector3::Backward() //!< vector3(0, -1, 0)
	{
		return Vector3(0, -1, 0);
	};

	void Normalize(); //!< maintains direction, flattens to 1
	const Vector3 Normalized(); //!< returns a normalized copy of this vector

	float Magnitude(); //!< returns the length of the vector

	void ToCartesian(); //!< applies spherical transformations to vector coordinates
	void ToSpherical(); //!< converts vector coordinates into spherical values

	const Vector3 GetCartesian(); //!< returns cartesian values from a spherical vector
	const Vector3 GetSpherical(); //!< returns spherical values from a cartesian vector

	float x;
	float y;
	float z;

	bool isPolar; //!< set flag to prevent overwriting x,y,z with spherical values during assignment operations
	
	friend CM_ENGINE_API std::ostream& operator<<(std::ostream &os, const Vector3 &vect3);
	friend CM_ENGINE_API bool& operator==(const Vector3& v1, const Vector3& v2);
	friend CM_ENGINE_API bool& operator!=(const Vector3& v1, const Vector3& v2);

	friend CM_ENGINE_API bool operator<(const Vector3& v1, const Vector3& v2);
	friend CM_ENGINE_API bool operator<=(const Vector3& v1, const Vector3& v2);
	friend CM_ENGINE_API bool operator>(const Vector3& v1, const Vector3& v2);
	friend CM_ENGINE_API bool operator>=(const Vector3& v1, const Vector3& v2);
	
	friend CM_ENGINE_API Vector3 operator+(const Vector3& v1, const Vector3& v2);
	friend CM_ENGINE_API Vector3 operator-(const Vector3& v1, const Vector3& v2);
	friend CM_ENGINE_API Vector3& operator*(const Vector3& v1, const Vector3& v2);
	
	friend CM_ENGINE_API Vector3& operator*(const float& f1, const Vector3& v2);
	friend CM_ENGINE_API Vector3& operator*(const Vector3& v1, const float& f2);

	friend CM_ENGINE_API Vector3& operator/(const Vector3& v1, const float& f2);

	Vector3 Cross(const Vector3& rhs) const;
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
	//! this is a horrible hack, please see class todo
	operator Math::Vector2();

	void operator=(Vector3 v1) {	x = v1.x; y = v1.y; z = v1.z; };

	~Vector3();
};

struct Bounds
{
	Bounds(Vector3 min, Vector3 max)
	: minCorner(min)
	, maxCorner(max)
	, lowerCorner(maxCorner.x, minCorner.y, minCorner.z)
	, upperCorner(minCorner.x, maxCorner.y, maxCorner.z)
	{}

	Bounds(Math::Vector2 min, Math::Vector2 max)
	: minCorner(Vector3(min.x, min.y, 0))
	, maxCorner(Vector3(max.x, max.y, 0))
	, lowerCorner(maxCorner.x, minCorner.y, 0)
	, upperCorner(minCorner.x, maxCorner.y, 0)
	{}
	
	Bounds()
	: minCorner(Vector3::Zero())
	, lowerCorner(Vector3::Zero())
	, maxCorner(Vector3::Zero())
	, upperCorner(Vector3::Zero())
	{}

	Vector3 minCorner;
	Vector3 maxCorner;
	// the corner adjacent horizontally to minCorner
	Vector3 lowerCorner;
	// the corner adjacent horizontally to maxCorner
	Vector3 upperCorner;
};

#endif