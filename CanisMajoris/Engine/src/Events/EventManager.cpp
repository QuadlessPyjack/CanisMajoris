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
#include<Events/EventClient.h>
//#include<memory> header for std::shared_ptr
namespace Core    {
namespace EventSys{

	EventManager *EventManager::m_eventManager = nullptr;

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
	, m_lastCriticalEventIndex(0)
	, m_lastMediumEventIndex(0)
	, m_clientIDPool(m_allowedNumberOfClients)
	, m_eventIDPool(m_allowedNumberOfEvents)
	, m_registeredClients(m_allowedNumberOfClients)
	, m_registeredEvents(m_allowedNumberOfEvents)
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
		if (!validateID(clientID, CLIENT)) { return false; }

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
		if (!validateID(eventID, EVENT)) { return false; }

		m_eventIDPool[eventID] = FREE_ID;
		return true;
	}

	bool EventManager::addClient(EventClient* client, const int index)
	{
		if (!validateID(index, CLIENT)) { return false; }

		m_registeredClients[index] = client;
		return true;
	}

	//!  \todo we need a better handling mechanism for this
	//!        perhaps a smartptr
	bool EventManager::removeClient(EventClient* client, const int index)
	{
		if (!validateID(index, CLIENT)) { return false; }

		m_registeredClients[index] = nullptr;
		return true;
	}

	bool EventManager::validateID(const int& id, type objectType)
	{
		bool status = false;
		// the following conditions are all evaluated on a fail-by-default basis
		if (id == INVALID_ID) { return false; }
		if (objectType == CLIENT)
		{
			id > m_registeredClients.size() ? status = false : status = true;
			return status;
		}

		if (objectType == EVENT)
		{
			id > m_registeredEvents.size() ? status = false : status = true;
			return status;
		}

		return status;
	}

	void EventManager::storeEventByPriorityOrder(Event* event)
	{
		int priority = event->priority;
		switch(priority)
		{
			case Event::PriorityEnum::CRITICAL:
			{
				m_eventQueue.push_front(event);
			}
			case Event::PriorityEnum::MEDIUM:
			{
				for (int index = m_lastCriticalEventIndex; index < m_eventQueue.size(); ++index)
				{
					if (m_eventQueue[index]->id == FREE_ID)
					{
						m_eventQueue[index] = event;
						break;
					}
				}
			}
			default:
			{
				m_eventQueue.push_back(event);
			}
		}
	}

	void EventManager::RegisterSystemEvents()
	{
		// engine update loop tick event setup
		Event *engine_event = new Event();
		engine_event->isPersistent = true;
		engine_event->eid = EID_ENGINE_TICK_EVENT;
		engine_event->priority = Event::CRITICAL;
		engine_event->id = -1;
		engine_event->registeredIdsClients.push_back(INVALID_ID);

		// physics engine update loop tick event setup
		Event *phys_tick_event = new Event();
		phys_tick_event->isPersistent = true;
		phys_tick_event->eid = EID_PHYS_TICK_EVENT;
		phys_tick_event->priority = Event::CRITICAL;
		engine_event->id = -2;
		engine_event->registeredIdsClients.push_back(INVALID_ID);

		storeEventByPriorityOrder(engine_event);
		storeEventByPriorityOrder(phys_tick_event);

		m_persistentEventCache.push_back(engine_event);
		m_persistentEventCache.push_back(phys_tick_event);
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

	void EventManager::Update()
	{
		if (m_eventQueue.size() == 0) { return; }
		for (int queueIndex = 0; queueIndex < m_eventQueue.size(); ++queueIndex)
		{
			std::vector<int> clientIDs = m_eventQueue.front()->registeredIdsClients;
			for (int clientIndex = 0; clientIndex < clientIDs.size(); ++clientIndex)
			{
				if (clientIDs[0] == INVALID_ID) { break; }
				m_registeredClients[clientIndex]->OnReceive(m_eventQueue.front());
			}
			m_eventQueue.pop_front();
		}
	}


	bool EventManager::RegisterClient(int &outClientId, EventClient* client)
	{
		if (!allocateClientID(outClientId)) { return false; }
		if (!addClient(client, outClientId)) { return false; }

		return true;
	}

	bool EventManager::AddEvent(Event* event, int &outEventID)
	{
		if (m_eventQueue.size() >= m_allowedNumberOfEvents) { return false; }
		
		if (!allocateEventInstanceID(event->id)) { return false; };

		// persistent events are stored separately from non-persistent ones
		if (event->isPersistent)
		{
			// event is persistent, cache it for easy retrieval
			m_persistentEventCache.push_back(event);
		}

		// store the event at its assigned id
		m_registeredEvents[event->id] = event;
		outEventID = event->id;
		return true;
	}

	bool EventManager::RegisterClientToEvent(const SystemEventID sysId, const int clientId)
	{
		if (!validateID(clientId, CLIENT)) { return false; }

		for (int index = 0; index < m_persistentEventCache.size(); ++index)
		{
			if (m_persistentEventCache[index]->eid == sysId)
			{
				m_persistentEventCache[index]->refCount++;
				m_persistentEventCache[index]->registeredIdsClients.push_back(clientId);

				return true;
			}
		}
		return false;
	}

	bool EventManager::RegisterClientToEvent(const int eventId, const int clientId)
	{
		if (!validateID(clientId, CLIENT)) { return false; }

		m_registeredEvents[eventId]->refCount++;
		m_registeredEvents[eventId]->registeredIdsClients.push_back(clientId);

		return true;
	}

	void EventManager::DecrementEventReference(const int eventId, const int clientId)
	{
		if (!validateID(eventId, EVENT))   { return; }
		if (!validateID(clientId, CLIENT)) { return; }

		m_registeredEvents[eventId]->refCount--;
		m_registeredEvents[eventId]->registeredIdsClients[clientId] = FREE_ID;

		if (m_registeredEvents[eventId]->refCount <= 0)
		{
			m_registeredEvents[eventId] = nullptr;
			delete m_registeredEvents[eventId];
		}
	}

	void EventManager::DecrementEventReference(const SystemEventID eventId, const int clientId)
	{
		if (!validateID(clientId, CLIENT)) { return; }

		for (int index = 0; index < m_persistentEventCache.size(); ++index)
		{
			if (m_persistentEventCache[index]->eid == eventId)
			{
				m_persistentEventCache[index]->refCount--;
				m_persistentEventCache[index]->registeredIdsClients[clientId] = FREE_ID;
			}
		}
	}

	void EventManager::FireEvent(const int& eventID)
	{
		if (!validateID(eventID, EVENT)) return;
		m_eventQueue.push_back(m_registeredEvents[eventID]);
	}

	void EventManager::FireEvent(const SystemEventID& sysEventID)
	{
		for (int index = 0; index < m_persistentEventCache.size(); ++index)
		{
			if (m_persistentEventCache[index]->eid == sysEventID)
			{
				m_eventQueue.push_front(m_persistentEventCache[index]);
				return;
			}
		}
	}
}
}