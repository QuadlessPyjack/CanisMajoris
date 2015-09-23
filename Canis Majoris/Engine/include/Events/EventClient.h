#ifndef EVENT_CLIENT_H
#define EVENT_CLIENT_H
//////////////////////////////////////////////////////// 
//! \brief   Event Client
//!	\author  Bogdan Vitel
//! \details Registers for and receives events
//! \date    20/07/2015
//! \todo To be determined
//////////////////////////////////////////
#include <vector>
#include <Events/EngineEvents.h>
#include <EngineDllExport.h>

namespace Core     {
namespace EventSys {

class CM_ENGINE_API EventClient
{
 public:
  EventClient();
  virtual ~EventClient();

  bool ConnectToEvent(int id);
  bool ConnectToEvent(const SystemEventID &sysId);

  void DisconnectFromEvent(const int &id, int index = 0);
  void DisconnectFromEvent(SystemEventID sysId);

  bool RegisterEvent(Event *event);
  bool RegisterSystemEvent(const Event &sysEvent);

  virtual void OnReceive(Event const *event){};

private:
  int m_clientId;
  int m_registeredEventId;
  SystemEventID m_registeredSystemEventId;
  std::vector<int> m_trackedIdEvents;
};

} // EventSys
} // Core

#endif