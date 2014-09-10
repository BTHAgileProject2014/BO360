#ifndef BOSYSTEM_H_
#define BOSYSTEM_H_

#include "BOComponent.h"
#include "BOWindow.h"
#include "BOInput.h"

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
	BOInput m_input;
};
#endif