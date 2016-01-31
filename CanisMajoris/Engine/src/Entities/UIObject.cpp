/////////////////////////////////////////////////////////////////////// 
//! \brief   UIObject Entity
//! \author  Bogdan Vitel
//! \details Base object class for all UI entities
//! \date    30/01/2016
//! \todo    
//////////////////////////////////////////////////
#include <Entities/UIObject.h>
#include <Renderer/CoreUtils/Primitives/Mesh.h>

namespace Core     {
namespace Game     {
namespace Entities {

	UIObject::UIObject()
	: Object()
	{
		
	}

	UIObject::UIObject(Renderer::CoreUtils::Mesh *mesh, Vector2 position, float scaleFactor)
	: Object(mesh, Vector3(position.x, position.y, 0.0f))
	, m_position(position)
	{
		Object::Scale(scaleFactor);
	}

	void UIObject::Draw(Vector3 colour)
	{
		Object::Draw(colour);
		//updateMeshTransform();
		//m_mesh->Draw(colour);
	}

	Vector2 UIObject::position() const
	{
		return m_position;
	}

	void UIObject::setPosition(Vector2 position)
	{
		m_position = position;
		SetLocation(Vector3(position.x, position.y, 0.0f));
	}

	void UIObject::Scale(float scaleFactor)
	{
		Object::Scale(scaleFactor);
	}
}
}
}