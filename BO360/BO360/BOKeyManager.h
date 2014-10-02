#ifndef BOKEYMANAGER_H_
#define BOKEYMANAGER_H_

#include "BOComponent.h"
#include "BOHUDManager.h"
#include "BOMapLoader.h"
#include "BOBall.h"

class BOKeyManager : public BOComponent
{
public:
	BOKeyManager();
	~BOKeyManager();

	bool Initialize(std::string p_mapFileName);
	void Shutdown();
	void Update(double p_deltaTime);
	void Update(BOBall p_ball);
	void Draw();

	bool AllKeysCatched();

private:
	std::vector<BOObject> m_keys;
	int m_keysCatched;
	int m_keysNeeded;

	void KeyCatched();
	bool LoadKeysFromMap(std::string p_filename);
};
#endif