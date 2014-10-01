#ifndef BOKEYMANAGER_H_
#define BOKEYMANAGER_H_

#include "BOComponent.h"
#include "BOHUDManager.h"

class BOKeyManager : public BOComponent
{
public:
	BOKeyManager();
	~BOKeyManager();

	bool Initialize();
	void Shutdown();
	void Update(double p_deltaTime);
	void Draw();

	int GetKeysLeft();
	bool Won();

private:
	int m_keysLeft;
};

#endif