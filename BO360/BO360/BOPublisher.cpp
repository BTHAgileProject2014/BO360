#include "BOPublisher.h"
std::vector<BOSubscriber*> BOPublisher::m_subscribers;

BOPublisher::BOPublisher()
{
}


BOPublisher::~BOPublisher()
{
}

bool BOPublisher::Initialize()
{
	m_subscribers = std::vector<BOSubscriber*>();

	// All key messages is set to false(not pressed)
	m_inputMessage = InputMessages();
	m_inputMessage.mouseX = 0;
	m_inputMessage.mouseY = 0;
	m_inputMessage.leftMouseKey = false;
	m_inputMessage.rightMouseKey = false;
	m_inputMessage.middleMouseKey = false;
	m_inputMessage.spacebarKey = false;
	m_inputMessage.upArrow = false;
	m_inputMessage.downArrow = false;
	m_inputMessage.leftArrow = false;
	m_inputMessage.rightArrow = false;
	m_inputMessage.zKey = false;
	m_inputMessage.xKey = false;
	m_inputMessage.escKey = false;

	return true;
}

void BOPublisher::Shutdown()
{
	m_subscribers.clear();
}

// Call the subscribers
void BOPublisher::Notify()
{
	for (unsigned int i = 0; i < m_subscribers.size(); i++)
	{
		m_subscribers[i]->Handle(m_inputMessage);
	}
}

// Change value for specified key (true = pressed, false = not pressed)
void BOPublisher::Notify(KeyMessages p_keyMessage, bool p_value)
{
	switch (p_keyMessage)
	{
	case leftMouseKey:
		m_inputMessage.leftMouseKey = p_value;
		break;
	case rightMouseKey:
		m_inputMessage.rightMouseKey = p_value;
		break;
	case middleMouseKey:
		m_inputMessage.middleMouseKey = p_value;
		break;
	case upArrow:
		m_inputMessage.upArrow = p_value;
		break;
	case downArrow:
		m_inputMessage.downArrow = p_value;
		break;
	case leftArrow:
		m_inputMessage.leftArrow = p_value;
		break;
	case rightArrow:
		m_inputMessage.rightArrow = p_value;
		break;
	case spacebarKey:
		m_inputMessage.spacebarKey = p_value;
		break;
	case zKey:
		m_inputMessage.zKey = p_value;
		break;
	case xKey:
		m_inputMessage.xKey = p_value;
		break;
	case escKey:
		m_inputMessage.escKey = p_value;
		break;
	}

	Notify();
}

// Change position of the mouse pointer
void BOPublisher::Notify(int2 p_mousePosition)
{
	m_inputMessage.mouseX = p_mousePosition.x;
	m_inputMessage.mouseY = p_mousePosition.y;

	Notify();
}

void BOPublisher::AddSubscriber(BOSubscriber* p_subscriber)
{
	m_subscribers.push_back(p_subscriber);
}

void BOPublisher::Unsubscribe(BOSubscriber* p_subscriber)
{
	for (unsigned int i = 0; i < m_subscribers.size(); i++)
	{
		if (m_subscribers[i] == p_subscriber)
		{
			m_subscribers.erase(m_subscribers.begin() + i);
			break;
		}
	}
}