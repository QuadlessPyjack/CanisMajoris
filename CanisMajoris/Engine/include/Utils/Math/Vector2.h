#ifndef VECTOR2_H
#define VECTOR2_H
////////////////////////////////////////// 
//! \brief   Vector2 - Canis Majoris Math Utils
//!	\author  Bogdan Vitel
//! \details Vector2 header - A 2D Vector Utility Class
//! \date    12/11/2014
//! \todo	 Add Polar Coordinate Support (overload, conversion methods)
//////////////////////////////////////////
#include<EngineDllExport.h>

#include<iostream>

namespace Math
{
	class CM_ENGINE_API Vector2
	{
	public:
		Vector2();

		//!< \todo argument names are misleading. change to something more general
		Vector2(float pozX, float pozY, bool polarCoordsFlag = false);

		inline static Vector2 Vector2::Zero() //!< vector2(0, 0)
		{
			return Vector2(0, 0);
		};

		inline static Vector2 Vector2::Up() //!< vector2(0,1)
		{
			return Vector2(0, 1);
		};

		inline static Vector2 Vector2::Down() //!< vector2(0, -1)
		{
			return Vector2(0, -1);
		};

		inline static Vector2 Vector2::Right() //!< vector2(1, 0)
		{
			return Vector2(1, 0);
		};

		inline static Vector2 Vector2::Left() //!< vector2(-1, 0)
		{
			return Vector2(-1, 0);
		};

		void Normalize(); //!< maintains direction, flattens to 1
		const Vector2 Normalized(); //!< returns a normalized copy of this vector

		float Magnitude(); //!< returns the length of the vector

		void ToCartesian(); //!< applies polar transformations to vector coordinates
		void ToPolar(); //!< converts vector coordinates into polar values

		const Vector2 GetCartesian(); //!< returns cartesian values from a spherical vector
		const Vector2 GetPolar(); //!< returns polar values from a cartesian vector

		float x;
		float y;

		bool isPolar; //!< set flag to prevent overwriting x,y with polar values during assignment operations

		friend CM_ENGINE_API std::ostream& operator<<(std::ostream &os, const Vector2 &vect2);
		friend CM_ENGINE_API bool& operator==(const Vector2& v1, const Vector2& v2);
		friend CM_ENGINE_API bool& operator!=(const Vector2& v1, const Vector2& v2);

		~Vector2();
	};

}
#endif