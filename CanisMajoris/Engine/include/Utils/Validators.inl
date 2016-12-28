/////////////////////////////////////////////////// 
//! \brief   Validator Utils - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Misc engine utility functions
//! \date    10/02/2015
//! \todo 
//////////////////////////////////////////
#ifndef VALIDATORS_INL
#define VALIDATORS_INL

#include<Utils/Constants.h>
#include<Renderer/CoreUtils/Primitives/Vertex.h>
#include<Utils/Math/Vector2.h>

using namespace Math;

//if a single value is given, check for bounds
// axis - 0 for X, 1 for Y
inline bool ValidateScreenCoord(float coord, int axis = 0)
{
if (coord < 0)
 return false;
if (axis == 0 && coord > SCREEN_WIDTH)
 return false;
if (axis == 1 && coord > SCREEN_HEIGHT)
 return false;

return true;
}

inline bool ValidateScreenCoord(Vector2 coords)
{
if (coords.x < 0 || coords.x > SCREEN_WIDTH)
 return false;
if (coords.y < 0 || coords.y > SCREEN_HEIGHT)
 return false;

return true;
}

inline void ValidateAndCapScreenCoordinates(Vector2 &coords)
{
	if (coords.x > SCREEN_WIDTH)
	{
		coords.x = SCREEN_WIDTH - 1;
	}

	if (coords.x < 0)
	{
		coords.x = 1;
	}

	if (coords.y > SCREEN_HEIGHT)
	{
		coords.y = SCREEN_HEIGHT - 1;
	}

	if (coords.y < 0)
	{
		coords.y = 1;
	}
}

inline bool ValidateScreenCoord(Core::Renderer::CoreUtils::Vertex &vert)
{
	if (vert.Location().x < 0 || vert.Location().y < 0)
	   return false;
	if (vert.Location().x > SCREEN_WIDTH)
	   return false;
	if (vert.Location().y > SCREEN_HEIGHT)
	   return false;

	return true;
}

#endif // VALIDATORS_INL