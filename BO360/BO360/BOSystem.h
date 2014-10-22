#ifndef BOSYSTEM_H_
#define BOSYSTEM_H_
#define DEBUG

#include "BOGlobals.h"
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
#include "BOSubscriber.h"
#include "BOScore.h"
#include "BOTextureManager.h"
#include "BOTechTreeManager.h"
#include "BOLevelManager.h"
#include <iostream>
#include "BOCutScene.h"
//#include <vld.h>

class BOSystem : BOComponent, public BOSubscriber
{
public:
	BOSystem();
	~BOSystem();

	bool Initialize();
	void Shutdown();
	bool Run();
	void Handle(InputMessages p_inputMessages);

private:
	bool InitializeMap();
	bool InitializeMap(int p_levelIndex);
	void HandleAction(ButtonAction p_action);
	void ShutdownMap();

	BOTimer m_timer;
	BOInput m_input;
	BOObjectManager m_objectManager;
	BOPowerUpManager m_powerUpManager;
	BOStateManager m_stateManager;
	BOLevelManager m_levelManager;
    BOCutScene m_cutsceneManager;

	bool m_quit;
	int m_windowWidth, m_windowHeight;

	std::string m_string;
	double m_deltaTime;
	double m_totalTime;
	int m_FPS;

	Uint32 m_timePassedMS;

	BOTechTreeEffects m_techTreeEffects;

    BOTechTreeManager m_techTreeManager;
};
#endif