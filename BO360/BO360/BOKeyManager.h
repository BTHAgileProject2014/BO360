#ifndef BOKEYMANAGER_H_
#define BOKEYMANAGER_H_

#include "BOComponent.h"
#include "BOKey.h"
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
	void KeyCatched();
	bool AllKeysCatched();

private:
	std::vector<BOKey> m_keys;
	int m_keysLeft;
};

#endif