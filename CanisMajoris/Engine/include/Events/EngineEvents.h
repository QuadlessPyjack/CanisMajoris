#ifndef ENGINE_EVENTS_H
#define ENGINE_EVENTS_H

//////////////////////////////////////////////////////// 
//! \brief   Event Helpers
//!	\author  Bogdan Vitel
//! \details Engine Event IDs, event structure 
//!          and other misc stuff
//! \date    21/07/2015
//! \todo To be determined
//////////////////////////////////////////
#include <guiddef.h>
#include <vector>

namespace Core     {
namespace EventSys {

// {C5352D25-5BC7-4A57-9C75-471790CF8188}
static const GUID  EID_ENGINE_TICK_EVENT =
{ 0xc5352d25, 0x5bc7, 0x4a57, { 0x9c, 0x75, 0x47, 0x17, 0x90, 0xcf, 0x81, 0x88 } };

// {68D42E7C-6DEF-45BE-8C9C-5689EC4DCBD9}
static const GUID EID_PHYS_TICK_EVENT =
{ 0x68d42e7c, 0x6def, 0x45be, { 0x8c, 0x9c, 0x56, 0x89, 0xec, 0x4d, 0xcb, 0xd9 } };

// {93754F3D-13D1-4E03-88A6-2EA7A9DB144C}
static const GUID EID_NON_SYS_EVENT =
{ 0x93754f3d, 0x13d1, 0x4e03, { 0x88, 0xa6, 0x2e, 0xa7, 0xa9, 0xdb, 0x14, 0x4c } };

//! we use them only for core events that exist only once
typedef GUID SystemEventID;

const int FREE_ID = 0;
const int USED_ID = 1;
const int INVALID_ID = -1;

const int DEFAULT_CLIENTS_CAP = 100;
const int DEFAULT_EVENTS_CAP = 100;

//! event structure used in client - server - client communication
struct Event
{
 //! ID used for dynamically generated events
 int id = 0;
 //! ID used for engine events
 SystemEventID eid = EID_NON_SYS_EVENT;

 //! ID of the EventClient that generated the event
 int ownerId = -1;

 //! Number of EventClients subscribed to this event
 int refCount = -1;

 //! Category identifier for this event
 int eventType = -1;

 //! Determines if event persists without subscribers
 bool isPersistent = false;

 //!
 std::vector<int> registeredIdsClients;

 //! Data associated with event
 char data[50];

 //! Sets event priority
 enum PriorityEnum
 {
	 CRITICAL = 0,
	 MEDIUM   = 1,
	 LOW      = 2
 } priority;

 Event &operator=(const int& i) { Event e; e.priority = PriorityEnum::LOW; return e; }
 operator int() { return 0; }
};

} // EventSys
} // Core

#endif