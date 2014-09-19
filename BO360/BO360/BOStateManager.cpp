#include "BOStateManager.h"

BOStateManager::BOStateManager()
{

}

BOStateManager::~BOStateManager()
{

}

bool BOStateManager::Initialize(int2 p_screenSize)
{
	bool result = true;

	// Setup main menu.
	float2 l_menuPosition = float2(100, 400);
	result = m_menu.Initialize(float2(p_screenSize.x / 2, p_screenSize.y / 2), p_screenSize, l_menuPosition, "MAIN MENU", "Bilder/Menu/MainMenuBackground.png");
	m_menu.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "PLAY STORY MODE", 1);
	m_menu.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "PLAY ENDLESS MODE", 2);
	m_menu.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "PLAY HARDCORE MODE", 3);
	m_menu.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "EXIT", -1);

	// Setup pause menu.
	l_menuPosition = float2(50, 400);
	result = m_paused.Initialize(float2(0, 0), p_screenSize, l_menuPosition, "PAUSE MENU", "Bilder/Menu/MainMenuBackground.png");
	m_paused.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "RESUME", 4);
	m_paused.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "QUIT", -2);
	m_paused.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "EXIT", -1);

	// Setup end screen menus.
	l_menuPosition = float2(50, 400);
	result = m_victory.Initialize(float2(0, 0), p_screenSize, l_menuPosition, "VICTORY", "Bilder/Menu/MainMenuBackground.png");
	m_victory.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "NEXT", 5);
	m_victory.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "QUIT", -2);
	m_victory.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "EXIT", -1);

	l_menuPosition = float2(50, 400);
	result = m_defeat.Initialize(float2(0, 0), p_screenSize, l_menuPosition, "DEFEAT", "Bilder/Menu/MainMenuBackground.png");
	m_defeat.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "RETRY", 6);
	m_defeat.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "QUIT", -2);
	m_defeat.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), "Bilder/Menu/Button", "EXIT", -1);

	return result;
}

int BOStateManager::Update(GameState p_state)
{
	int l_action = 0;

	switch (p_state)
	{
		case(MENU) :
		{
			l_action = m_menu.Update();

			break;
		}

		case(PAUSED) :
		{
			l_action = m_paused.Update();

			break;
		}

		case(VICTORY) :
		{
			l_action = m_victory.Update();

			break;
		}

		case(DEFEAT) :
		{
			l_action = m_defeat.Update();

			break;
		}

		default:
		{
			break;
		}
	}

	return l_action;
}

void BOStateManager::Draw(GameState p_state)
{
	switch (p_state)
	{
		case(MENU) :
		{
			m_menu.Draw();

			break;
		}

		case(PAUSED) :
		{
			m_paused.Draw();

			break;
		}

		case(VICTORY) :
		{
			m_victory.Draw();

			break;
		}

		case(DEFEAT) :
		{
			m_defeat.Draw();

			break;
		}

		default:
		{
			break;
		}
	}
}

void BOStateManager::Shutdown()
{
	m_menu.Shutdown();
	m_paused.Shutdown();
	m_victory.Shutdown();
	m_defeat.Shutdown();
}