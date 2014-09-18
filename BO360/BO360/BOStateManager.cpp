#include "BOStateManager.h"

BOStateManager::BOStateManager()
{

}

BOStateManager::~BOStateManager()
{

}

bool BOStateManager::Initialize(GameState p_beginningState, int2 p_screenSize)
{
	bool result = true;

	m_gameState = p_beginningState;

	// Setup main menu.
	result = m_menu.Initialize(float2(0, 0), p_screenSize, "MAIN MENU", "Bilder/Menu/MainMenuBackground.png");


	// Setup pause menu.
	result = m_paused.Initialize(float2(0, 0), p_screenSize, "PAUSE MENU", "Bilder/Menu/PausedBackground.png");


	// Setup end screen menu.
	result = m_endScreen.Initialize(float2(0, 0), p_screenSize, "GAME OVER", "Bilder/Menu/EndScreenBackground.png");


	return result;
}

void BOStateManager::Update()
{
	switch (m_gameState)
	{
		case(MENU) :
		{
			HandleActions(m_menu.Update());

			break;
		}

		case(PAUSED) :
		{
			HandleActions(m_paused.Update());

			break;
		}

		case(ENDSCREEN) :
		{
			HandleActions(m_endScreen.Update());

			break;
		}

		default:
		{
			break;
		}
	}
}

void BOStateManager::Draw()
{
	switch (m_gameState)
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

		case(ENDSCREEN) :
		{
			m_endScreen.Draw();

			break;
		}

		default:
		{
			break;
		}
	}
}

void BOStateManager::SetGameState(GameState p_state)
{
	m_gameState = p_state;
}

GameState BOStateManager::GetGameState()
{
	return m_gameState;
}

void BOStateManager::Shutdown()
{
	m_menu.Shutdown();
	m_paused.Shutdown();
	m_endScreen.Shutdown();
}