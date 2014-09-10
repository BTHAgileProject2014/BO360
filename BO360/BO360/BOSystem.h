#ifndef BOSYSTEM_H_
#define BOSYSTEM_H_

#include "BOComponent.h"
#include "BOWindow.h"
#include "BOObjectManager.h"

class BOSystem : BOComponent
{
public:
	BOSystem();
	~BOSystem();

	bool Initialize();
	void Shutdown();
	bool Run();
private:
	BOWindow m_window;
	BOObjectManager m_objectManager;
	int windowWidth, windowHeight;
};
#endif