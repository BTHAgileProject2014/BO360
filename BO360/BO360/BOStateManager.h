#ifndef BOSTATEMANAGER_H_
#define BOSTATEMANAGER_H_

#include "BOComponent.h"
#include "BOState.h"

class BOStateManager : public BOComponent
{
public:
	BOStateManager();
	~BOStateManager();

	bool Initialize(GameState p_beginningState, int2 p_screenSize);
	void Shutdown();
	void SetGameState(GameState p_state);
	GameState GetGameState();
	void Update();
	void Draw();

private:
	void HandleActions(int p_action);

	BOState m_menu;
	BOState m_paused;
	BOState m_endScreen;
	GameState m_gameState;
};
#endif