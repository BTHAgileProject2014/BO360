#include "BOSoundManager.h"

BOSoundManager::~BOSoundManager()
{
}

bool BOSoundManager::Initialize()
{
	GetInstance().m_music = NULL;
	GetInstance().m_popHex = NULL;
	GetInstance().m_dying = NULL;
	GetInstance().m_powerup = NULL;
	GetInstance().m_teleport = NULL;
	GetInstance().m_bounceOnPad = NULL;

	// Initialize SDL MIxer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		// Failed initialize
		return false;
	}

	// Load music
	GetInstance().m_music = Mix_LoadMUS("Sound/themeModified.wav");
	if (GetInstance().m_music == NULL)
	{
		return false;
	}

	// Load sound effects
	GetInstance().m_popHex = Mix_LoadWAV("Sound/ballCollisionHexagon.wav");
	if (GetInstance().m_popHex == NULL)
	{
		return false;
	}

	GetInstance().m_dying = Mix_LoadWAV("Sound/dying.wav");
	if (GetInstance().m_dying == NULL)
	{
		return false;
	}

	GetInstance().m_powerup = Mix_LoadWAV("Sound/powerup.wav");
	if (GetInstance().m_powerup == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
		return false;
	}

	GetInstance().m_teleport = Mix_LoadWAV("Sound/teleport.wav");
	if (GetInstance().m_teleport == NULL)
	{
		return false;
	}

	GetInstance().m_bounceOnPad = Mix_LoadWAV("Sound/bounceOnPad.wav");
	if (GetInstance().m_bounceOnPad == NULL)
	{
		return false;
	}

	Mix_PlayMusic(GetInstance().m_music, -1);

	return true;
}

void BOSoundManager::Shutdown()
{
	// Free sound effects
	Mix_FreeChunk(GetInstance().m_popHex);
	Mix_FreeChunk(GetInstance().m_dying);
	Mix_FreeChunk(GetInstance().m_powerup);
	Mix_FreeChunk(GetInstance().m_teleport);
	GetInstance().m_popHex = NULL;
	GetInstance().m_dying = NULL;
	GetInstance().m_powerup = NULL;
	GetInstance().m_teleport = NULL;
	
	// Free the music
	Mix_FreeMusic(GetInstance().m_music);
	GetInstance().m_music = NULL;

	Mix_Quit();
}

void BOSoundManager::Update()
{

}

void BOSoundManager::PlaySound(Sound p_sound)
{
	switch (p_sound)
	{
	case SOUND_POP:
		// Play in channel 0 so pop sound resets every time it plays
		Mix_PlayChannel(0, GetInstance().m_popHex, 0);
		break;
	case SOUND_DIE:
		Mix_PlayChannel(-1, GetInstance().m_dying, 0);	// Channel -1 is nearest avaiable channel
		break;
	case SOUND_POWERUP:
		Mix_PlayChannel(-1, GetInstance().m_powerup, 0);
		break;
	case SOUND_TELEPORT:
		Mix_PlayChannel(-1, GetInstance().m_teleport, 0);
		break;
	case SOUND_BOUNCEONPAD:
		Mix_PlayChannel(-1, GetInstance().m_bounceOnPad, 0);
		break;
	}
}

BOSoundManager& BOSoundManager::GetInstance()
{
	static BOSoundManager instance;
	return instance;
}