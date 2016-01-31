#ifndef UI_OBJECT_H
#define UI_OBJECT_H
/////////////////////////////////////////////////////////////////////// 
//! \brief   UIObject Entity
//! \author  Bogdan Vitel
//! \details Base object class for all UI entities
//! \date    30/01/2016
//! \todo    
//////////////////////////////////////////////////
#include <EngineDllExport.h>
#include <Entities/Object.h>
#include <Utils/Math/Vector2.h>

#include <Utils/Colours.inl>

namespace Core     {
namespace Game     {
namespace Entities {
	using namespace Math;
	class CM_ENGINE_API UIObject : public Object
	{
	public:
		UIObject();
		UIObject(Renderer::CoreUtils::Mesh *mesh, Vector2 position, float scaleFactor = 1.0f);

		void Draw(Vector3 colour = Colour::Green);
		Vector2 position() const;
		void setPosition(Vector2 position);

		void Scale(float scaleFactor);

	private:
		Vector2 m_position;
	};
} // namespace Entities
} // namespace Game
} // namespace Core

#endif // UI_OBJECT_H