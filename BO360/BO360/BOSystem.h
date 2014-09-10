#ifndef BOSYSTEM_H_
#define BOSYSTEM_H_

#include "BOComponent.h"
#include "BOWindow.h"
#include "BOInput.h"
#include "BOObjectManager.h"
#include "BOGraphicInterface.h"


class BOSystem : BOComponent
{
public:
	BOSystem();
	~BOSystem();

	bool Initialize();
	void Shutdown();
	bool Run();
private:

	BOInput m_input;
	BOObjectManager m_objectManager;
	int windowWidth, windowHeight;

};
#endif