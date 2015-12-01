//////////////////////////////////////////////////////// 
//! \brief   Simple Physics Body - Canis Lupus
//!	\author  Bogdan Vitel
//! \details Crude Rigidbody Implementation
//! \date    25/05/2015
//! \todo Force Vector (ie. Gravity), PoorMan'sCollision(tm)
//////////////////////////////////////////

#include<Renderer/CoreUtils/Primitives/Mesh.h>
#include<Physics/SimplePhysBody.h>

namespace Core   {
namespace Physics{

	SPBody::SPBody()
	: m_mesh()
	, m_mass(1.0f)
	, m_gravScale(1.0f)
	, m_awake(false)
	{};

	SPBody::~SPBody()
	{
		
	};

	void SPBody::SetMesh(Renderer::CoreUtils::Mesh &mesh)
	{
		m_mesh = &mesh;
	};

	const Renderer::CoreUtils::Mesh* SPBody::GetMesh()
	{
		return m_mesh;
	};

	void SPBody::SetMass(float mass)
	{
		m_mass = mass;
	};

	const float SPBody::GetMass()
	{
		return m_mass;
	};

	void SPBody::SetGravityScale(float gravScale)
	{
		m_gravScale = gravScale;
	};

	const float SPBody::GetGravityScale()
	{
		return m_gravScale;
	};

	void SPBody::SetAwakeState(bool isAwake)
	{
		m_awake = isAwake;
	};

	const bool SPBody::GetAwakeState()
	{
		return m_awake;
	};

	void SPBody::AddForce(Vector3 a)
	{
		Vector3 dir = m_mesh->Location();
		dir = a / (m_mass * m_gravScale) * dir;

		m_mesh->Translate(dir);
	};

} // Physics
} // Core