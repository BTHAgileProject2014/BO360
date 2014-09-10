#ifndef BOPUBLISHER_H_
#define BOPUBLISHER_H_
#include "BOSubscriber.h"
#include "BOUtility.h"
#include <vector>
class BOPublisher
{
private:
	std::vector<BOSubscriber*> m_subscribers;
	InputMessages m_inputMessage;
	void Notify();
public:
	BOPublisher();
	~BOPublisher();

	void Initialize();
	void Shutdown();

	void Notify(KeyMessages p_keyMessage, bool p_value);
	void Notify(int p_x, int p_y);
	void AddSubscriber(BOSubscriber* p_subscriber);
};
#endif