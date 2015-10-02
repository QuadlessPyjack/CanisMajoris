#ifndef TEST_EVENT_CLIENT_H
#define TEST_EVENT_CLIENT_H
#include <iostream>
#include <Events/EventClient.h>

class CM_ENGINE_API EventClientTest : public Core::EventSys::EventClient
{
public:
	void OnReceive(const Core::EventSys::Event const *event) override;
};

#endif