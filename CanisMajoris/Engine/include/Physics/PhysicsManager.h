//////////////////////////////////////////////////////// 
//! \brief   Physics Manager - Canis Lupus
//!	\author  Bogdan Vitel
//! \details Puts that shiny graphics to good use
//! \date    25/05/2015
//! \todo Force Vector (ie. Gravity), PoorMan'sCollision(tm)
//////////////////////////////////////////
#include <EngineDllExport.h>
#include <vector>

#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

//forward declarations
class Vector3;

namespace Core    {
namespace Physics {
	
	class SPBody;

	class CM_ENGINE_API PhysicsManager
	{
	public:
		~PhysicsManager();

		static void InitPhysics();
		static PhysicsManager &GetInstance();

		void AddPhysObject(SPBody* physObject);
		//void RemovePhysObject(SPBody* physObject);

		SPBody* GetPhysObject(int index);
		//SPBody* GetPhysObject(std::string id);

		void ApplyUniversalForce(Vector3 a);

		void Update();

	private:
		PhysicsManager();

		static PhysicsManager *m_Physics;
		float m_gravityScale = 1.0f;
		std::vector<SPBody*> m_physObjectsContainer;
	};


}
}




#endif // PHYSICS_MANAGER_H