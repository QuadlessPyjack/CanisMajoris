#include <Events/TestEventClient.h>

void EventClientTest::OnReceive(Core::EventSys::Event const *event)
{
	std::cout << "[INFO] The Test Event Client has been successfully fired!\n";
}
