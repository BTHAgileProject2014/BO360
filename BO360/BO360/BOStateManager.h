#ifndef BOSTATEMANAGER_H_
#define BOSTATEMANAGER_H_

#include "BOComponent.h"
#include "BOState.h"

class BOStateManager : public BOComponent
{
public:
	BOStateManager();
	~BOStateManager();

	bool Initialize(int2 p_screenSize);
	void Shutdown();
	ButtonAction Update(GameState p_state);
	void Draw(GameState p_state);
	int GetLevelIndex();

private:
	bool InitializeLevelSelect(int2 p_screenSize);
private:
	BOState m_menu;
	BOState m_paused;
	BOState m_victory;
	BOState m_defeat;
	BOState m_levelSelect;
};
#endif