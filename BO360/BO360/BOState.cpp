#include "BOState.h"

BOState::BOState()
{

}

BOState::~BOState()
{

}

bool BOState::Initialize(float2 p_position, int2 p_size, float2 p_menuPosition, std::string p_name, SDL_Texture* p_sprite)
{
	m_name = p_name;
	m_position = p_position;
	m_screenSize = p_size;
	m_buttonList.empty();

	BOPublisher::AddSubscriber(this);

	// Load background.
	if (!m_background.Initialize(p_position, p_size, p_sprite))
	{
		std::cout << "Failed to load background for " << m_name << "!" << std::endl;
		return false;
	}

	// Load the menu bars first edge.
	BOObject l_firstEdge;
	if (!l_firstEdge.Initialize(float2(p_menuPosition.x + 2.5f, p_menuPosition.y + 35), int2(5, 70), BOTextureManager::GetTexture(TEXMENUEDGE)))
	{
		std::cout << "Failed to load first edge of menu" << m_name << "!" << std::endl;
		return false;
	}

	m_menuBar.push_back(firstEdge);

	// Load the menu bar.
	BOObject l_menuBar;
	if (!l_menuBar.Initialize(float2(p_menuPosition.x + 125, p_menuPosition.y + 35), int2(240, 70), BOTextureManager::GetTexture(TEXMENUBAR)))
	{
		std::cout << "Failed to load last edge of menu" << m_name << "!" << std::endl;
		return false;
	}

	m_menuBar.push_back(menuBar);

	// Load the last edge of the menu bars.
	BOObject l_lastEdge;
	if (!l_lastEdge.Initialize(float2(p_menuPosition.x + 247.5f, p_menuPosition.y + 35), int2(5, 70), BOTextureManager::GetTexture(TEXMENUEDGE)))
	{
		std::cout << "Failed to load last edge of menu" << m_name << "!" << std::endl;
		return false;
	}

	m_menuBar.push_back(lastEdge);

	// Load menu text
	if (!m_menuText.Initialize(float2(0,0), m_name, int3(255, 255, 255), 72, 0))
	{
		std::cout << "Failed to create menu text in " << m_name << "!" << std::endl;
		return false;
	}

	// Calculate menu text position
	int2 tempSize = m_menuText.GetSize();
	float2 tempPos = float2(25.0f + p_menuPosition.x + tempSize.x / 2, 13 + p_menuPosition.y + tempSize.y / 2);
	m_menuText.SetPosition(tempPos);

	return true;
}

void BOState::AddButton(float2 p_position, int2 p_size, float2 p_menuPosition, SDL_Texture* p_sprite, std::string p_name, ButtonAction p_action, std::string p_tooltip)
{
	BOButton l_button;
	if (!l_button.Initialize(float2(p_position.x + (250 * m_buttonList.size()), p_position.y), p_size, p_sprite, p_name, p_action, p_tooltip))
	{
		std::cout << "Failed to load button for texture " << p_sprite << "!" << std::endl;
	}
	m_buttonList.push_back(button);

	// Change position and size of the menu bar
	m_menuBar[1].SetSize(int2(240 * m_buttonList.size() + 10 * (m_buttonList.size() - 1), 70));
	m_menuBar[1].SetPosition(float2((p_menuPosition.x + 125) + 120 * (m_buttonList.size() - 1) + 5 * (m_buttonList.size() - 1), p_menuPosition.y + 35));
	m_menuBar[2].SetPosition(float2((p_menuPosition.x + 7.5f) + m_menuBar[1].GetSize().x, p_menuPosition.y + 35));
}

void BOState::Handle(InputMessages p_inputMessages)
{
	m_mousePosition = int2(p_inputMessages.mouseX, p_inputMessages.mouseY);
	m_mouseDown = p_inputMessages.leftMouseKey;
}

ButtonAction BOState::Update()
{
	for (unsigned int i = 0; i < m_buttonList.size(); i++)
	{
		if (m_buttonList[i].Intersects(m_mousePosition))
		{
			if (m_mouseDown)
			{
				return m_buttonList[i].GetAction();
			}
		}
	}

	return NOACTION;
}

void BOState::Draw()
{
	// Draw background.
	m_background.Draw();

	// Draw menu bar.
	for (unsigned int i = 0; i < m_menuBar.size(); i++)
	{
		m_menuBar[i].Draw();
	}

	// Draw Buttons.
	for (unsigned int i = 0; i < m_buttonList.size(); i++)
	{
		m_buttonList[i].Draw();
	}

	m_menuText.Draw();
}

void BOState::SetName(std::string p_name)
{
	m_name = p_name;
}

void BOState::SetBackground(Textures p_spriteIndex)
{
	m_background.SetSprite(p_spriteIndex);
}

void BOState::Shutdown()
{
	for (unsigned int i = 0; i < m_buttonList.size(); i++)
	{
		m_buttonList[i].Shutdown();
	}

	m_buttonList.empty();
	m_menuText.Shutdown();
}