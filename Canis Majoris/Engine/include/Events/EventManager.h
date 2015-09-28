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
	
	bool RegisterClient(const int clientId, EventClient *client);
	void AddEvent(Event *event);

	bool RegisterClientToEvent(const SystemEventID sysId, const int clientId);
	bool RegisterClientToEvent(const int eventId, const int clientId);

	void DecrementEventReference(const int eventId, const int clientId);
	void DecrementEventReference(const SystemEventID eventId, const int clientId);

	~EventManager();

private:
	EventManager();
	static EventManager *m_eventManager;
	std::vector<EventClient*> m_registeredClients;
	std::vector<Event*> m_eventQueue;

	void RegisterSystemEvents();

};

} // Core
} // EventSys

#endif // EVENT_MGR_H