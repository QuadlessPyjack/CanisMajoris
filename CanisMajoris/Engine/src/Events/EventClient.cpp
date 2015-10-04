//////////////////////////////////////////////////////// 
//! \brief   Event Client
//!	\author  Bogdan Vitel
//! \details Registers for and receives events
//! \date    20/07/2015
//! \todo To be determined
//////////////////////////////////////////
#include <Events/EventClient.h>
#include <Events/EventManager.h>

namespace Core     {
namespace EventSys {

EventClient::EventClient()
{
	EventManager::GetInstance()->RegisterClient(m_clientId, this);
}

bool EventClient::RegisterEvent(Event *event)
{
	bool status = EventManager::GetInstance()->AddEvent(event);
	return status;
}

//bool EventClient::RegisterSystemEvent(const Event &sysEvent)
//{
//	bool status = EventManager::GetInstance()->AddEvent(sysEvent);
//	assert(status);
//	return status;
//}

	bool EventClient::ConnectToEvent(const SystemEventID &sysId)
{
	bool status = EventManager::GetInstance()->RegisterClientToEvent(sysId, m_clientId);
	if(status) m_trackedIdEvents.push_back(1);
	return status;
}

bool EventClient::ConnectToEvent(int eventId)
{
	bool status = EventManager::GetInstance()->RegisterClientToEvent(eventId, m_clientId);
	if(status) m_trackedIdEvents.push_back(eventId);
	return status;
}

void EventClient::DisconnectFromEvent(const int &eventId, int index)
{
	EventManager::GetInstance()->DecrementEventReference(eventId, m_clientId);
	if (index != 0) m_trackedIdEvents[index] = INVALID_ID;
	else
	{
		for (index = 0; index < m_trackedIdEvents.size(); ++index)
		{
			if (m_trackedIdEvents[index] == eventId) m_trackedIdEvents[index] = INVALID_ID;
		}
	}
}

void EventClient::DisconnectFromEvent(SystemEventID sysId)
{
	EventManager::GetInstance()->DecrementEventReference(sysId, m_clientId);
}


EventClient::~EventClient()
{
	for (int index = 0; index < m_trackedIdEvents.size(); ++index)
	{
		if(m_trackedIdEvents[index] != INVALID_ID) DisconnectFromEvent(m_trackedIdEvents[index], index);
	}
}


} // Core
} // EventSys