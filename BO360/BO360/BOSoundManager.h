#ifndef BOSOUNDMANAGER_H_
#define BOSOUNDMANAGER_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "BOUtility.h"
#include <iostream>

class BOSoundManager
{
public:
	~BOSoundManager();
	static bool Initialize();
	static void Shutdown();
	static void Update();
	static void PlayPopSound();
	static void PlaySound(Sound p_sound);

private:
	BOSoundManager() {};
	BOSoundManager(BOSoundManager const &);
	void operator=(BOSoundManager const&);
	static BOSoundManager& GetInstance();

	Mix_Music *m_runningMusic;
    Mix_Music *m_menuMusic;
	Mix_Chunk *m_popHex;
	Mix_Chunk *m_dying;
	Mix_Chunk *m_powerup;
	Mix_Chunk *m_teleport;
	Mix_Chunk *m_bounceOnPad;
    Mix_Chunk *m_charge;
    Mix_Chunk *m_shockwave;
    Mix_Chunk *m_slowDown;
    Mix_Chunk *m_slowUp;
    Mix_Chunk *m_thruster;
};

#endif 
