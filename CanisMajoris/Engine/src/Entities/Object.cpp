////////////////////////////////////////// 
//! \brief   Scene Object Entity
//!	\author  Bogdan Vitel
//! \details Object virtual class header
//! \date    29/01/2016
//! \todo Group duplicate base methods into a virtual class
//////////////////////////////////////////

#include<Entities/Object.h>
#include<Renderer/CoreUtils/Primitives/Mesh.h>

namespace Core     {
namespace Game     {
namespace Entities {
	
	Object::Object()
	: m_mesh(nullptr)
	, m_location(Vector3::Zero())
	{
	}

	Object::Object(Renderer::CoreUtils::Mesh* mesh, Vector3 location)
	: m_mesh(mesh)
	, m_location(location)
	{
	}

	Object::~Object()
	{
		//! \todo implement reference counter for mesh?
	}

	void Object::Draw()
	{
		updateMeshTransform();
		m_mesh->Draw();
	}

	Vector3 Object::Location() const
	{
		return m_location;
	}

	void Object::SetLocation(Vector3 location)
	{
		m_location = location;
	}

	Renderer::CoreUtils::Mesh& Object::GetMesh()
	{
		return *m_mesh;
	}

	void Object::SetMesh(Renderer::CoreUtils::Mesh* mesh)
	{
		m_mesh = mesh;
	}

	void Object::Translate(Vector3 offset)
	{
		m_location = m_location + offset;
		updateMeshTransform();
		m_mesh->Translate(offset);
		m_mesh->SetLocked(false);
	}

	void Object::Scale(Vector3 centre, float scaleFactor)
	{
		updateMeshTransform();
		m_mesh->Scale(centre, scaleFactor);
		m_mesh->SetLocked(false);
	}

	void Object::Scale(float scaleFactor)
	{
		updateMeshTransform();
		m_mesh->Scale(scaleFactor);
		m_mesh->SetLocked(false);
	}

	void Object::Rotate(Vector3 centre, Vector3 amount)
	{
		updateMeshTransform();
		m_mesh->Rotate(centre, amount);
		m_mesh->SetLocked(false);
	}

	void Object::Rotate(Vector3 amount)
	{
		updateMeshTransform();
		m_mesh->Rotate(amount);
		m_mesh->SetLocked(false);
	}

	//! @brief Checks if mesh was previously used by other objects and resets its transform accordingly
	void Object::updateMeshTransform()
	{
		if (!m_mesh->IsLocked())
		{
			m_mesh->ResetTransform();
			m_mesh->SetPivot(m_location);
			m_mesh->SetLocation(m_location);
			m_mesh->SetLocked(true);
		}
	}
} // namespace Entities
} // namespace Game
} // namespace Core