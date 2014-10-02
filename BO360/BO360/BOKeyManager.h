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

	bool Initialize();
	void Shutdown();
	void Update(double p_deltaTime);
	void Update(BOBall p_ball);
	void Draw();

    void AddKey(float2 p_position, int2 p_size, float p_scale, SDL_Texture* p_sprite);
	bool AllKeysCatched();

private:
	std::vector<BOObject> m_keys;
	int m_keysCatched;
	int m_keysNeeded;

	void KeyCatched();
};
#endif