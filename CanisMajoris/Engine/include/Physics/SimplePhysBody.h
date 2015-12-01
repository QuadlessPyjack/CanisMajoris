//////////////////////////////////////////////////////// 
//! \brief   Simple Physics Body - Canis Majoris
//!	\author  Bogdan Vitel
//! \details Crude Rigidbody Implementation
//! \date    25/05/2015
//! \todo Force Vector (ie. Gravity), PoorMan'sCollision(tm)
//////////////////////////////////////////
#ifndef SIMPLE_PHYS_BODY_H
#define SIMPLE_PHYS_BODY_H

#include <EngineDllExport.h>

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
	class CM_ENGINE_API SPBody
	{
	public:
	SPBody();
	~SPBody();

	void AddForce(Vector3 a);

	void SetMesh(Renderer::CoreUtils::Mesh &mesh);
	const Renderer::CoreUtils::Mesh* GetMesh();

	void  SetMass(float mass);
	const float GetMass();

	void  SetGravityScale(float gravScale);
	const float GetGravityScale();

	void  SetAwakeState(bool isAwake);
	const bool  GetAwakeState();

	private:
	Renderer::CoreUtils::Mesh* m_mesh;
	float m_mass;
	float m_gravScale;
	bool  m_awake;
	};
}
}

#endif // SIMPLE_PHYS_BODY_H