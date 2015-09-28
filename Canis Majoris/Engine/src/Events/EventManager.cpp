/////////////////////////////////////////////////////////////////// 
//! \brief   Event Manager
//!	\author  Bogdan Vitel
//! \details Registers event clients, handles the event que
//!          prioritises events and ensures QoS management
//! \date    20/07/2015
//! \todo Rewrite the whole thing based on left over references
//!       because of a git freak accident
//////////////////////////////////////////////////////
#include<Events/EventManager.h>

namespace Core    {
namespace EventSys{

	EventManager *m_eventManager = nullptr;

	EventManager& EventManager::GetInstance()
	{
		if (m_eventManager == nullptr)
		{
			m_eventManager = new EventManager();
		}
		return *m_eventManager;
	}

	EventManager::EventManager()
	: m_registeredClients()
	, m_eventQueue()
	{
		RegisterSystemEvents();
	}

	void EventManager::RegisterSystemEvents()
	{
		Event *engine_event = new Event();
		engine_event->isPersistent = true;
		engine_event->eid = EID_ENGINE_TICK_EVENT;
		engine_event->priority = Event::CRITICAL;
		engine_event->id = 0;

		Event *phys_tick_event = new Event();
		phys_tick_event->isPersistent = true;
		phys_tick_event->eid = EID_PHYS_TICK_EVENT;
		phys_tick_event->priority = Event::CRITICAL;
		engine_event->id = 1;

		m_eventQueue.push_back(engine_event);
		m_eventQueue.push_back(phys_tick_event);
	}

	bool EventManager::InitializeEventManager() const
	{
		if (EventManager::m_eventManager)
		{
			return true;
		}
		return false;
	}
}
}