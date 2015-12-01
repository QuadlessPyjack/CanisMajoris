////////////////////////////////////////// 
//! \details Conversion Functions
//  Bogdan Vitel - Canis Majoris Renderer
//	Data Conversion Utilities
//  Created: 12/02/2015
//! \todo 
//////////////////////////////////////////

#include<Renderer/CoreUtils/Scene.h>
#include<Renderer/CoreUtils/Camera.h>

#include<Renderer/CoreUtils/Primitives/Vertex.h>

#include<Utils/Math/Vector2.h>
#include<Utils/Math/Vector3.h>

#include<Utils/Constants.h>

using namespace Core::Renderer::CoreUtils;

inline const Vector3 WorldToCameraCoords(const Vector3 &worldCoords)
{
	Vector3 v3 = worldCoords - Scene::GetInstance().GetCamera()->Location();
	return v3;
}

inline const Vector2 VertexToScreenCoords(Vertex &vertex)
{
	Vector3 CameraPoz = Scene::GetInstance().GetCamera()->Location();
	Vector3 CamRelStartV3 = WorldToCameraCoords(vertex.Location());
	float x_screen1 = (CamRelStartV3.x / CamRelStartV3.z) * SCREEN_WIDTH + SCREEN_WIDTH / 2;
	float y_screen1 = (CamRelStartV3.y / CamRelStartV3.z) * SCREEN_HEIGHT + SCREEN_HEIGHT / 2;

	return Vector2(x_screen1, y_screen1);
}