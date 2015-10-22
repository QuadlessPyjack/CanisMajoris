//////////////////////////////////////////////////////// 
//! \brief   Physics Manager - Canis Majoris
//!	\author  Bogdan Vitel
//! \details Puts that shiny graphics to good use
//! \date    25/05/2015
//! \todo Force Vector (ie. Gravity), PoorMan'sCollision(tm)
//////////////////////////////////////////
#include <time.h>

#include <Utils/Math/Vector3.h>

#include <Physics/PhysicsManager.h>
#include <Physics/SimplePhysBody.h>

namespace Core    {
namespace Physics {

	    PhysicsManager *PhysicsManager::m_Physics = nullptr;

		void PhysicsManager::InitPhysics()
		{
			if (PhysicsManager::m_Physics)
			{
				// do init stuff here
			}
		}

		PhysicsManager &PhysicsManager::GetInstance()
		{
			if (m_Physics == nullptr)
			{
				m_Physics = new PhysicsManager();
				return *m_Physics;
			}

			return *m_Physics;
		}

		PhysicsManager::~PhysicsManager()
		{
			delete m_Physics;
			m_Physics = nullptr;
		}

		PhysicsManager::PhysicsManager()
		{

		}

		void PhysicsManager::AddPhysObject(SPBody* physObject)
		{
			m_physObjectsContainer.push_back(physObject);
		}

		/*void PhysicsManager::RemovePhysObject(SPBody* physObject)
		{
			m_physObjectsContainer.erase(physObject);
		}*/

		SPBody* PhysicsManager::GetPhysObject(int index)
		{
			if (index <= m_physObjectsContainer.capacity())
			{
				return m_physObjectsContainer[index];
			}

			return new SPBody;
		}

		void PhysicsManager::ApplyUniversalForce(Vector3 a)
		{
			for (int index = 0; index < m_physObjectsContainer.capacity(); ++index)
			{
				m_physObjectsContainer[index]->AddForce(a);
			}
		}

		void PhysicsManager::OnReceive(EventSys::Event const *event)
		{
			double out = -666;
			long range = sizeof(double);
			memcpy(&out, &event->data, 10);
			if (out > range || out < -range) out = 0;
			std::cout << "[INFO] Physics engine received delta frame time: " << out / CLOCKS_PER_SEC << "\n";
		}

		void PhysicsManager::Update()
		{
			//TODO: Implement Timer System - Use SDL_Delay in main loop
			//      to count the ticks for PHYS_TICK
			//      otherwise two delays are being added - not what we want!
		}

} // Physics
} // Core