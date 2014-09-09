#ifndef BOPUBLISHER_H_
#define BOPUBLISHER_H_
#include "BOSubscriber.h"
#include <vector>
class BOPublisher
{
private:

	struct KeyMessages
	{
		int mouseX;
		int mouseY;
		bool mouseKeyDown;
		bool rightArrow;
		bool leftArrow;
		bool upArrow;
		bool downArrow;
	};


	std::vector<BOSubscriber*> m_subscribers;
	KeyMessages m_keyMessage;
public:
	BOPublisher();
	~BOPublisher();
	void Notify();
	//void Notify(KeyMessages p_keyMessages);

};
#endif