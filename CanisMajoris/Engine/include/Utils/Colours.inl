/////////////////////////////////////////////////// 
//! \brief   Validator Utils - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Misc engine utility functions
//! \date    10/02/2015
//! \todo 
//////////////////////////////////////////
#ifndef COLOURS_H
#define COLOURS_H

#include <Utils/Math/Vector3.h>

namespace Colour
{
	static const Vector3 Red   (255.0f, 0.0f, 0.0f);
	static const Vector3 Green (0.0f, 255.0f, 0.0f);
	static const Vector3 Blue  (0.0f, 0.0f, 255.0f);
	static const Vector3 Black (Vector3::Zero());
	static const Vector3 White (255.0f, 255.0f, 255.0f);
	static const Vector3 Yellow(255.0f, 242.0f, 0.0f);
	static const Vector3 Orange(255.0f, 128.0f, 0.0f);
	static const Vector3 Brown (128.0f, 64.0f, 0.0f);
	static const Vector3 Pink  (255.0f, 0.0f, 128.0f);
	static const Vector3 Purple(255.0f, 0.0f, 255.0f);
};

#endif // COLOURS_H