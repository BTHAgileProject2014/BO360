#ifndef BOSOUNDMANAGER_H_
#define BOSOUNDMANAGER_H_

#include <SDL.h>
#include <SDL_mixer.h>


class BOSoundManager
{
public:
	BOSoundManager();
	~BOSoundManager();
	bool Initialize();
	void Shutdown();
	void Update();
	void PlayPopSound();
private:
	Mix_Music *m_music;
	Mix_Chunk *m_popHex;
	Mix_Chunk *m_dying;
	Mix_Chunk *m_powerup;
	Mix_Chunk *m_teleport;
};

#endif // !BOSOUNDMANAGER_H_