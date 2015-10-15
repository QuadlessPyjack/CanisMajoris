////////////////////////////////////////// 
//! \details Conversion Functions
//  Bogdan Vitel - Canis Majoris Renderer
//	Data Conversion Utilities
//  Created: 12/02/2015
//! \todo 
//////////////////////////////////////////

#include<Renderer/CoreUtils/Scene.h>
#include<Renderer/CoreUtils/Camera.h>

#include<Utils/Math/Vector2.h>
#include<Utils/Math/Vector3.h>

using namespace Core::Renderer::CoreUtils;

inline const Vector3 WorldToCameraCoords(const Vector3 &worldCoords)
{
	Vector3 v3 = worldCoords - Scene::GetInstance().GetCamera()->Location();
	return v3;
}