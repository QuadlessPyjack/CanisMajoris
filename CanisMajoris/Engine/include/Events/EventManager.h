/////////////////////////////////////////////////////////////////// 
//! \brief   Event Manager
//!	\author  Bogdan Vitel
//! \details Registers event clients, handles the event que
//!          prioritises events and ensures QoS management
//! \date    20/07/2015
//! \todo Rewrite the whole thing based on left over references
//!       because of a git freak accident
//////////////////////////////////////////////////////
#ifndef EVENT_MGR_H
#define EVENT_MGR_H

#include<EngineDllExport.h>
#include"EngineEvents.h"
#include <deque>

namespace Core     {
namespace EventSys {

//forward declarations
class EventClient;

namespace
{
	enum type
	{
		EVENT,
		SYS_EVENT,
		CLIENT
	};
}

class CM_ENGINE_API EventManager
{
public:
	static EventManager &GetInstance();
	bool InitializeEventManager() const;
	
	bool RegisterClient(int &outClientId, EventClient *client);
	bool AddEvent(Event *event, int &outEventID);

	bool RegisterClientToEvent(const SystemEventID sysId, const int clientId);
	bool RegisterClientToEvent(const int eventId, const int clientId);

	void DecrementEventReference(const SystemEventID eventId, const int clientId);
	void DecrementEventReference(const int eventId, const int clientId);

	void FireEvent(const SystemEventID &sysEventID, const char dataParam[10]);
	void FireEvent(const int &eventID, const char dataParam[10]);

	void FireEvent(const SystemEventID &sysEventID);
	void FireEvent(const int &eventID);

	void Update();

	~EventManager();

private:
	EventManager();
	static EventManager *m_eventManager;

	int m_allowedNumberOfClients;
	int m_allowedNumberOfEvents;

	int m_lastCriticalEventIndex;
	int m_lastMediumEventIndex; // used for culling oldest low priority events first

	std::vector<int> m_clientIDPool;
	std::vector<int> m_eventIDPool;

	std::vector<EventClient*> m_registeredClients;
	std::deque<Event*> m_eventQueue;

	// cache for events that persist during the entire lifespan of the engine
	std::vector<Event*> m_persistentEventCache;
	// volatile storage for non-persistent events
	std::vector<Event*> m_registeredEvents;

	bool allocateClientID(int &outID);
	bool deallocateClientID(const int &clientID);

	bool allocateEventInstanceID(int &outID);
	bool deallocateEventInstanceID(const int &eventID);

	bool addClient(EventClient* client, const int index);
	bool removeClient(EventClient* client, const int index);

	bool validateID(const int &id, type objectType);
	void storeEventByPriorityOrder(Event* event);
	void RegisterSystemEvents();

};

} // Core
} // EventSys

#endif // EVENT_MGR_H