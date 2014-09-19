#include "BOState.h"

BOState::BOState()
{

}

BOState::~BOState()
{

}

bool BOState::Initialize(float2 p_position, int2 p_size, float2 p_menuPosition, std::string p_name, std::string p_backgroundFile)
{
	m_name = p_name;
	m_position = p_position;
	m_screenSize = p_size;
	m_buttonList.empty();

	BOPublisher::AddSubscriber(this);

	// Load background.
	if (!m_background.Initialize(p_position, p_size, p_backgroundFile))
	{
		std::cout << "Failed to load background for " << m_name << "!" << std::endl;
		return false;
	}

	// Load the menu bars first edge.
	BOObject l_firstEdge;
	if (!l_firstEdge.Initialize(p_menuPosition, int2(5, 75), "Bilder/Menu/MenuEdge.png"))
	{
		std::cout << "Failed to load first edge of menu" << m_name << "!" << std::endl;
		return false;
	}

	m_menuBar.push_back(l_firstEdge);
	l_firstEdge.Shutdown();

	// Load the menu bar.
	BOObject l_menuBar;
	if (!l_menuBar.Initialize(float2(p_menuPosition.x + 5, p_menuPosition.y), int2(240, 75), "Bilder/Menu/MenuBar.png"))
	{
		std::cout << "Failed to load last edge of menu" << m_name << "!" << std::endl;
		return false;
	}

	m_menuBar.push_back(l_menuBar);
	l_menuBar.Shutdown();

	// Load the last edge of the menu bars.
	BOObject l_lastEdge;
	if (!l_lastEdge.Initialize(float2(p_menuPosition.x + 245, p_menuPosition.y), int2(5, 75), "Bilder/Menu/MenuEdge.png"))
	{
		std::cout << "Failed to load last edge of menu" << m_name << "!" << std::endl;
		return false;
	}

	m_menuBar.push_back(l_lastEdge);
	l_lastEdge.Shutdown();

	return true;
}

void BOState::AddButton(float2 p_position, int2 p_size, std::string p_fileName, std::string p_name, int p_action)
{
	BOButton l_button;
	if (!l_button.Initialize(float2(p_position.x + (250 * m_buttonList.size()), p_position.y), p_size, p_fileName, p_name, p_action))
	{
		std::cout << "Failed to load button for texture " << p_fileName << "!" << std::endl;
	}
	m_buttonList.push_back(l_button);
	l_button.Shutdown();

}

void BOState::Handle(InputMessages p_inputMessages)
{
	m_mousePosition = int2(p_inputMessages.mouseX, p_inputMessages.mouseY);
	m_mouseDown = p_inputMessages.leftMouseKey;
}

int BOState::Update()
{
	for (int i = 0; i < m_buttonList.size(); i++)
	{
		if (m_buttonList[i].Intersects(m_mousePosition))
		{
			if (m_mouseDown)
			{
				return m_buttonList[i].GetAction();
			}
		}
	}

	return 0;
}

void BOState::Draw()
{
	// Draw background.
	m_background.Draw();

	// Draw menu bar.
	for (int i = 0; i < m_menuBar.size(); i++)
	{
		m_menuBar[i].Draw();
	}

	// Draw Buttons.
	for (int i = 0; i < m_buttonList.size(); i++)
	{
		m_buttonList[i].Draw();
	}
}

void BOState::SetName(std::string p_name)
{
	m_name = p_name;
}

void BOState::SetBackground(std::string p_fileName)
{
	m_background.SetSprite(p_fileName);
}

void BOState::Shutdown()
{
	for (int i = 0; i < m_buttonList.size(); i++)
	{
		m_buttonList[i].Shutdown();
	}

	m_buttonList.empty();
}