#ifndef BOSYSTEM_H_
#define BOSYSTEM_H_

#include "BOComponent.h"
#include "BOWindow.h"
#include "BOInput.h"
#include "BOObjectManager.h"
#include "BOGraphicInterface.h"
#include "BOTimer.h"
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
	int windowWidth, windowHeight;

	std::string m_string;
	Uint32 m_deltaTime;
	float m_totalTime;

	float FPScounter(Uint32 p_deltaTime);
	float m_currentFPS;
	float m_averageFPS;
	int m_FPS;
};
#endif