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

	BOTimer m_timer;
	BOInput m_input;
	BOObjectManager m_objectManager;
	BOPowerUpManager m_powerUpManager;
	BOSoundManager m_soundManager;
	int windowWidth, windowHeight;

	std::string m_string;
	Uint32 m_deltaTime;
	float m_totalTime;
	int m_FPS;

	Uint32 m_timePassedMS;
};
#endif