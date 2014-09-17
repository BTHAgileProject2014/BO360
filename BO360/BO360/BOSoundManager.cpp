#include "BOSoundManager.h"


BOSoundManager::BOSoundManager()
{
	m_music = NULL;
	m_popHex = NULL;
	m_dying = NULL;
	m_powerup = NULL;
	m_teleport = NULL;
}


BOSoundManager::~BOSoundManager()
{
}

bool BOSoundManager::Initialize()
{
	// Initialize SDL MIxer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		// Failed initialize
		return false;
	}

	// Load music
	m_music = Mix_LoadMUS("Sound/theme.wav");
	if (m_music == NULL)
	{
		return false;
	}

	// Load sound effects
	m_popHex = Mix_LoadWAV("Sound/ballCollisionHexagon.wav");
	if (m_popHex == NULL)
	{
		return false;
	}

	m_dying = Mix_LoadWAV("Sound/dying.wav");
	if (m_dying == NULL)
	{
		return false;
	}

	/*m_powerup = Mix_LoadWAV("Sound/powerup.wav");
	if (m_powerup == NULL)
	{
		return false;
	}*/

	m_teleport = Mix_LoadWAV("Sound/teleport.wav");
	if (m_teleport == NULL)
	{
		return false;
	}

	Mix_PlayMusic(m_music, -1);

	return true;
}

void BOSoundManager::Shutdown()
{
	// Free sound effects
	Mix_FreeChunk(m_popHex);
	Mix_FreeChunk(m_dying);
	Mix_FreeChunk(m_powerup);
	Mix_FreeChunk(m_teleport);
	m_popHex = NULL;
	m_dying = NULL;
	m_powerup = NULL;
	m_teleport = NULL;
	
	// Free the music
	Mix_FreeMusic(m_music);
	m_music = NULL;

	Mix_Quit();
}

void BOSoundManager::Update()
{

}

void BOSoundManager::PlayPopSound()
{
	// Play in channel 0, so if repeated first pop is stopeed
	Mix_PlayChannel( 0, m_popHex, 0);
}