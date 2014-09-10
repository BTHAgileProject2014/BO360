#include "BOPublisher.h"


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
	m_inputMessage.upArrow = false;;
	m_inputMessage.downArrow = false;
	m_inputMessage.leftArrow = false;
	m_inputMessage.rightArrow = false;

	return true;
}

void BOPublisher::Shutdown()
{
	for (unsigned int i = 0; i < m_subscribers.size(); i++)
	{
		delete m_subscribers[i];
	}
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
	}

	Notify();
}

// Change position of the mouse pointer
void BOPublisher::Notify(int p_x, int p_y)
{
	m_inputMessage.mouseX = p_x;
	m_inputMessage.mouseY = p_y;

	Notify();
}

void BOPublisher::AddSubscriber(BOSubscriber* p_subscriber)
{
	m_subscribers.push_back(p_subscriber);
}