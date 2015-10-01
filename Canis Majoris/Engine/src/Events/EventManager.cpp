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
//#include<memory> header for std::shared_ptr
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
	: m_allowedNumberOfClients(DEFAULT_CLIENTS_CAP)
	, m_allowedNumberOfEvents(DEFAULT_EVENTS_CAP)
	, m_clientIDPool(m_allowedNumberOfClients)
	, m_eventIDPool(m_allowedNumberOfEvents)
	, m_registeredClients()
	, m_eventQueue()
	{
		RegisterSystemEvents();
	}

	EventManager::~EventManager()
	{
		delete m_eventManager;
		m_eventManager = nullptr;
	}


	bool EventManager::allocateClientID(int& outID)
	{
		for (int index = 0; index < m_clientIDPool.size(); ++index)
		{
			if (m_clientIDPool[index] == FREE_ID)
			{
				m_clientIDPool[index] = USED_ID;
				outID = index;
				return true;
			}
		}
		outID = INVALID_ID;
		return false;
	}

	bool EventManager::deallocateClientID(const int& clientID)
	{
		m_clientIDPool[clientID] = FREE_ID;
		return true;
	}

	bool EventManager::allocateEventInstanceID(int& outID)
	{
		for (int index = 0; index < m_eventIDPool.size(); ++index)
		{
			if (m_eventIDPool[index] == FREE_ID)
			{
				m_eventIDPool[index] = USED_ID;
				outID = index;
				return true;
			}
		}
		outID = INVALID_ID;
		return false;
	}

	bool EventManager::deallocateEventInstanceID(const int& eventID)
	{
		m_eventIDPool[eventID] = FREE_ID;
		return true;
	}

	bool EventManager::addClient(EventClient* client, const int index)
	{
		m_registeredClients[index] = client;
		return true;
	}

	//!  \todo we need a better handling mechanism for this
	//!        perhaps a smartptr
	bool EventManager::removeClient(EventClient* client, const int index)
	{
		m_registeredClients[index] = nullptr;
		return true;
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
			//do other init logic here
			return true;
		}
		return false;
	}

	bool EventManager::RegisterClient(int &outClientId, EventClient* client)
	{
		if (!allocateClientID(outClientId)) { return false; }
		if (!addClient(client, outClientId)) { return false; }

		return true;
	}

	bool EventManager::AddEvent(Event* event)
	{
		if (m_eventQueue.size() >= m_allowedNumberOfEvents) { return false; }
		
		if (!allocateEventInstanceID(event->id)) { return false; };

		m_eventQueue.push_back(event);
		return true;
	}
}
}