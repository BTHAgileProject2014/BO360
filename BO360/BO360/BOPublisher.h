#ifndef BOPUBLISHER_H_
#define BOPUBLISHER_H_
#include "BOSubscriber.h"
#include "BOComponent.h"
#include "BOUtility.h"
#include <vector>
class BOPublisher : public BOComponent
{
private:
	static std::vector<BOSubscriber*> m_subscribers;
	InputMessages m_inputMessage;
	void Notify();
public:
	BOPublisher();
	~BOPublisher();

	bool Initialize();
	void Shutdown();

	void Notify(KeyMessages p_keyMessage, bool p_value);
	void Notify(int p_x, int p_y);
	static void AddSubscriber(BOSubscriber* p_subscriber);
	static void Unsubscribe(BOSubscriber* p_subscriber);
};
#endif