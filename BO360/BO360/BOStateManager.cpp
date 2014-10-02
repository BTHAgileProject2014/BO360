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
	float2 l_menuPosition = float2(50, 50);
	result = m_menu.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, l_menuPosition, "MAIN MENU", "Sprites/Menu/MainMenuBackground.png");
	m_menu.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "STORY MODE", STORY, "         Play arcade.");
	m_menu.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "HIGHSCORE", HIGHSCORE, "         View highscore.");
	m_menu.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "EXIT", EXIT, "         Exit the game and return to desktop.\n\nWill you really abandon your ship and its crew in their hour of need?");

	// Setup pause menu.
	l_menuPosition = float2(50, 50);
	result = m_paused.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, l_menuPosition, "PAUSE MENU", "Sprites/Menu/MainMenuBackground.png");
	m_paused.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "RESUME", RESUME, "         Resume the game.");
	m_paused.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "MENU", QUIT, "         Quit your current game and return to the main menu.");
	m_paused.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "EXIT", EXIT, "         Exit the game and return to desktop.");

	// Setup end screen menus.
	l_menuPosition = float2(50, 50);
	result = m_victory.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, l_menuPosition, "VICTORY", "Sprites/Menu/MainMenuBackground.png");
	m_victory.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "NEXT", NEXT, "         Play the next level.");
	m_victory.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "MENU", QUIT, "         Quit your current game and return to the main menu.");
	m_victory.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "EXIT", EXIT, "         Exit the game and return to desktop.");

	l_menuPosition = float2(50, 50);
	result = m_defeat.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, l_menuPosition, "DEFEAT", "Sprites/Menu/MainMenuBackground.png");
	m_defeat.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "RETRY", RETRY, "         Retry your current level.");
	m_defeat.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "MENU", QUIT, "         Quit your current game and return to the main menu.");
	m_defeat.AddButton(float2(l_menuPosition.x, l_menuPosition.y + 70), int2(250, 75), l_menuPosition, "Sprites/Menu/Button", "EXIT", EXIT, "         Exit the game and return to desktop.");

	return result;
}

ButtonAction BOStateManager::Update(GameState p_state)
{
	ButtonAction action = NOACTION;

	switch (p_state)
	{
		case(MENU) :
		{
			action = m_menu.Update();

			break;
		}

		case(PAUSED) :
		{
			action = m_paused.Update();

			break;
		}

		case(VICTORY) :
		{
			action = m_victory.Update();

			break;
		}

		case(DEFEAT) :
		{
			action = m_defeat.Update();

			break;
		}

		default:
		{
			break;
		}
	}

	return action;
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