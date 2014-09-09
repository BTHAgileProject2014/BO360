#include "BOPublisher.h"


BOPublisher::BOPublisher()
{
}


BOPublisher::~BOPublisher()
{
}

void BOPublisher::Notify()
{
	for (int i = 0; i < m_subscribers.size(); i++)
	{
		// m_subscribers->Notify(messages);
	}
}