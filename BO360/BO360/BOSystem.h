#ifndef BOSYSTEM_H_
#define BOSYSTEM_H_
#define DEBUG

#include "BOComponent.h"
#include "BOWindow.h"
#include "BOInput.h"
#include "BOObjectManager.h"
#include "BOGraphicInterface.h"
#include "BOTimer.h"
#include "BOPowerUpManager.h"
#include "BOSoundManager.h"
#include "BOTextManager.h"
#include "BOHUDManager.h"
#include "BOStateManager.h"
#include <iostream>

class BOSystem : BOComponent
{
public:
	BOSystem();
	~BOSystem();

	bool Initialize();
	void Shutdown();
	bool Run();

private:
	bool InitializeMap();
	void HandleAction(ButtonAction p_action);

	BOTimer m_timer;
	BOInput m_input;
	BOObjectManager m_objectManager;
	BOPowerUpManager m_powerUpManager;
	BOStateManager m_stateManager;
	GameState m_gameState;
	bool m_quit;
	int m_windowWidth, m_windowHeight;

	std::string m_string;
	Uint32 m_deltaTime;
	float m_totalTime;
	int m_FPS;

	Uint32 m_timePassedMS;
};
#endif