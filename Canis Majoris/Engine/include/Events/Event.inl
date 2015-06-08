#include<string>

struct Payload
{
	int numVal;
	float floatVal;
	bool flagVal;
	std::string stringVal;
};
struct Message
{
	int id;
	short priority;
	Payload payload;
};