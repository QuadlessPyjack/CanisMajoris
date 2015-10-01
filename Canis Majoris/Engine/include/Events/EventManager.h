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

namespace Core     {
namespace EventSys {

//forward declarations
class EventClient;

class CM_ENGINE_API EventManager
{
public:
	static EventManager &GetInstance();
	bool InitializeEventManager() const;
	
	bool RegisterClient(int &outClientId, EventClient *client);
	bool AddEvent(Event *event);

	bool RegisterClientToEvent(const SystemEventID sysId, const int clientId);
	bool RegisterClientToEvent(const int eventId, const int clientId);

	void DecrementEventReference(const int eventId, const int clientId);
	void DecrementEventReference(const SystemEventID eventId, const int clientId);

	~EventManager();

private:
	EventManager();
	static EventManager *m_eventManager;

	int m_allowedNumberOfClients;
	int m_allowedNumberOfEvents;

	std::vector<int> m_clientIDPool;
	std::vector<int> m_eventIDPool;

	std::vector<EventClient*> m_registeredClients;
	std::vector<Event*> m_eventQueue;

	bool allocateClientID(int &outID);
	bool deallocateClientID(const int &clientID);

	bool allocateEventInstanceID(int &outID);
	bool deallocateEventInstanceID(const int &eventID);

	bool addClient(EventClient* client, const int index);
	bool removeClient(EventClient* client, const int index);

	void RegisterSystemEvents();
	void Update();

};

} // Core
} // EventSys

#endif // EVENT_MGR_H