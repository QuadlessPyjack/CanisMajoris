////////////////////////////////////////// 
//! \details Conversion Functions
//  Bogdan Vitel - Canis Majoris Renderer
//	Data Conversion Utilities
//  Created: 12/02/2015
//! \todo 
//////////////////////////////////////////

#include <Utils/Constants.h>

#include<Renderer/CoreUtils/Scene.h>
#include<Renderer/CoreUtils/Camera.h>

using namespace Core::Renderer::CoreUtils;

inline const Vector3 WorldToCameraCoords(const Vector3 &worldCoords)
{
	Vector3 v3 = worldCoords - Scene::GetInstance().GetCamera()->Location();
	return v3;
}

inline const Math::Vector2 WorldToScreenCoords(const Vector3 &worldCoords)
{
	Vector3 CameraPoz = Scene::GetInstance().GetCamera()->Location();
	Vector3 CamRelStartV3 = WorldToCameraCoords(worldCoords);

	float x_screen1 = (CamRelStartV3.x / CamRelStartV3.z) * SCREEN_WIDTH /* 1.5f*/ + SCREEN_WIDTH / 2.0f;// *SCREEN_WIDTH + SCREEN_WIDTH / 2;
	float y_screen1 = (CamRelStartV3.y / CamRelStartV3.z) * SCREEN_HEIGHT /* 1.5f*/ + SCREEN_HEIGHT / 2.0f;// *SCREEN_HEIGHT + SCREEN_HEIGHT / 2;


	return Math::Vector2((int)x_screen1, (int)y_screen1);
}