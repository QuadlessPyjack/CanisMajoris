//////////////////////////////////////////////////////// 
//! \brief   Simple Physics Body - Canis Majoris
//!	\author  Bogdan Vitel
//! \details Crude Rigidbody Implementation
//! \date    25/05/2015
//! \todo Force Vector (ie. Gravity), PoorMan'sCollision(tm)
//////////////////////////////////////////

#ifndef SIMPLE_PHYS_BODY_H
#define SIMPLE_PHYS_BODY_H

//forward declarations
class Vector3;
namespace Core     {
namespace Renderer {
namespace CoreUtils{

class Mesh;

} // CoreUtils
} // Renderer
} // Core

namespace Core    {
namespace Physics {
	class SPBody
	{
	public:
	SPBody();
	~SPBody();

	void AddForce(Vector3 a);

	void SetMesh(const Renderer::CoreUtils::Mesh &mesh);
	Renderer::CoreUtils::Mesh* GetMesh();

	void  SetMass(float mass);
	float GetMass();

	void  SetGravityScale(float gravScale);
	float GetGravityScale();

	void  SetAwakeState(bool isAwake);
	bool  GetAwakeState();

	private:
	Renderer::CoreUtils::Mesh* m_mesh;
	float m_mass;
	float m_gravScale;
	bool  m_awake;
	};
}
}

#endif // SIMPLE_PHYS_BODY_H