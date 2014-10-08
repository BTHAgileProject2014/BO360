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
	float2 menuPosition = float2(50, 50);
    result = m_menu.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, menuPosition, "MAIN MENU", BOTextureManager::GetTexture(TEXMENUBG));
    m_menu.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "STORY MODE", STORY, "         Play arcade.");
	m_menu.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "SELECT LEVEL", LEVELSELECT, "         Select level to play.");
    m_menu.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "HIGHSCORE", HIGHSCORE, "         View highscore.");
    m_menu.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "EXIT", EXIT, "         Exit the game and return to desktop.\n\nWill you really abandon your ship and its crew in their hour of need?");
	if (!result) return false;

	// Setup pause menu.
	menuPosition = float2(50, 50);
    result = m_paused.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, menuPosition, "PAUSE MENU", BOTextureManager::GetTexture(TEXMENUBG));
    m_paused.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "RESUME", RESUME, "         Resume the game.");
    m_paused.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "MENU", QUIT, "         Quit your current game and return to the main menu.");
    m_paused.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "EXIT", EXIT, "         Exit the game and return to desktop.");
	if (!result) return false;

	// Setup end screen menus.
	menuPosition = float2(50, 50);
    result = m_victory.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, menuPosition, "VICTORY", BOTextureManager::GetTexture(TEXMENUBG));
    m_victory.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "NEXT LEVEL", NEXT, "         Play the next level.");
    m_victory.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "MENU", QUIT, "         Quit your current game and return to the main menu.");
    m_victory.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "EXIT", EXIT, "         Exit the game and return to desktop.");
	if (!result) return false;

	menuPosition = float2(50, 50);
    result = m_defeat.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, menuPosition, "DEFEAT", BOTextureManager::GetTexture(TEXMENUBG));
    m_defeat.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "RETRY", RETRY, "         Retry your current level.");
    m_defeat.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "MENU", QUIT, "         Quit your current game and return to the main menu.");
    m_defeat.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 75), menuPosition, BOTextureManager::GetTexture(TEXMENUBUTTON), "EXIT", EXIT, "         Exit the game and return to desktop.");
	if (!result) return false;

	result = InitializeLevelSelect(p_screenSize);
	
	return result;
}

bool BOStateManager::InitializeLevelSelect(int2 p_screenSize)
{
	bool result = false;
	float2 menuPosition = float2(50, 50);
	result = m_levelSelect.Initialize(float2(p_screenSize.x / 2.0f, p_screenSize.y / 2.0f), p_screenSize, menuPosition, "Level Selector", BOTextureManager::GetTexture(TEXMENUBG));
	for (int i = nrOfLevels + 1; i < texNR+13; i++)
	{
		if (i % 4 == ((nrOfLevels + 1) % 4) && i != (nrOfLevels + 1))
		{
			menuPosition.y += 175;
			menuPosition.x -= 250 * 4;
		}
		if (i >= texNR)
		{
			m_levelSelect.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 175), menuPosition, BOTextureManager::GetTextureInt(TEXBUTTONDEAFAULTMAP),
				std::string("LEVEL " + std::to_string(i - nrOfLevels)), LEVEL, "");
		}
		else
		{
			m_levelSelect.AddButton(float2(menuPosition.x, menuPosition.y + 70), int2(250, 175), menuPosition, BOTextureManager::GetTextureInt(i),
				std::string("LEVEL " + std::to_string(i - nrOfLevels)), LEVEL, "");
		}
	}

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
		case(LEVELSELECTOR) :
		{
			action = m_levelSelect.Update();

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

		case(LEVELSELECTOR) :
		{
			m_levelSelect.Draw();

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
	m_levelSelect.Shutdown();
}

int BOStateManager::GetLevelIndex()
{
	return m_levelSelect.GetLevelIndex();
}