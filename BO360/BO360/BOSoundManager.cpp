#include "BOSoundManager.h"

BOSoundManager::~BOSoundManager()
{

}

bool BOSoundManager::Initialize()
{
    GetInstance().m_runningMusic = NULL;
    GetInstance().m_menuMusic = NULL;
	GetInstance().m_popHex = NULL;
	GetInstance().m_dying = NULL;
	GetInstance().m_powerup = NULL;
	GetInstance().m_teleport = NULL;
	GetInstance().m_bounceOnPad = NULL;
    GetInstance().m_charge = NULL;
    GetInstance().m_shockwave = NULL;
    GetInstance().m_slowDown = NULL;
    GetInstance().m_slowUp = NULL;
    GetInstance().m_thruster = NULL;
    GetInstance().m_bump = NULL;

	// Initialize SDL MIxer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		// Failed initialize
		return false;
	}

	// Load music
    GetInstance().m_runningMusic = Mix_LoadMUS("Sounds/themeModified.wav");
    if (GetInstance().m_runningMusic == NULL)
	{
		return false;
	}

    GetInstance().m_menuMusic = Mix_LoadMUS("Sounds/menuTheme.wav");
    if (GetInstance().m_menuMusic == NULL)
    {
        return false;
    }

	// Load sound effects
	GetInstance().m_popHex = Mix_LoadWAV("Sounds/ballCollisionHexagon.wav");
	if (GetInstance().m_popHex == NULL)
	{
		return false;
	}

	GetInstance().m_dying = Mix_LoadWAV("Sounds/dying.wav");
	if (GetInstance().m_dying == NULL)
	{
		return false;
	}

	GetInstance().m_powerup = Mix_LoadWAV("Sounds/PickUp.wav");
	if (GetInstance().m_powerup == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
		return false;
	}

	GetInstance().m_teleport = Mix_LoadWAV("Sounds/teleport.wav");
	if (GetInstance().m_teleport == NULL)
	{
		return false;
	}

	GetInstance().m_bounceOnPad = Mix_LoadWAV("Sounds/PadBounce.wav");
	if (GetInstance().m_bounceOnPad == NULL)
	{
		return false;
	}

    GetInstance().m_charge = Mix_LoadWAV("Sounds/Charge.wav");
    if (GetInstance().m_charge == NULL)
    {
        return false;
    }

    GetInstance().m_shockwave = Mix_LoadWAV("Sounds/Shockwave.wav");
    if (GetInstance().m_shockwave == NULL)
    {
        return false;
    }

    GetInstance().m_slowDown = Mix_LoadWAV("Sounds/SlowDown.wav");
    if (GetInstance().m_slowDown == NULL)
    {
        return false;
    }

    GetInstance().m_slowUp = Mix_LoadWAV("Sounds/SlowUp.wav");
    if (GetInstance().m_slowUp == NULL)
    {
        return false;
    }

    GetInstance().m_thruster = Mix_LoadWAV("Sounds/Thruster.wav");
    if (GetInstance().m_thruster == NULL)
    {
        return false;
    }

    GetInstance().m_bump = Mix_LoadWAV("Sounds/Bump.wav");
    if (GetInstance().m_bump == NULL)
    {
        return false;
    }

	return true;
}

void BOSoundManager::Shutdown()
{
	// Free sound effects
	Mix_FreeChunk(GetInstance().m_popHex);
	Mix_FreeChunk(GetInstance().m_dying);
	Mix_FreeChunk(GetInstance().m_powerup);
	Mix_FreeChunk(GetInstance().m_teleport);
    Mix_FreeChunk(GetInstance().m_bounceOnPad);
    Mix_FreeChunk(GetInstance().m_charge);
    Mix_FreeChunk(GetInstance().m_shockwave);
    Mix_FreeChunk(GetInstance().m_slowDown);
    Mix_FreeChunk(GetInstance().m_slowUp);
    Mix_FreeChunk(GetInstance().m_thruster);
    Mix_FreeChunk(GetInstance().m_bump);
    GetInstance().m_popHex = NULL;
    GetInstance().m_dying = NULL;
    GetInstance().m_powerup = NULL;
    GetInstance().m_teleport = NULL;
    GetInstance().m_bounceOnPad = NULL;
    GetInstance().m_charge = NULL;
    GetInstance().m_shockwave = NULL;
    GetInstance().m_slowDown = NULL;
    GetInstance().m_slowUp = NULL;
    GetInstance().m_thruster = NULL;
    GetInstance().m_bump = NULL;
	
	// Free the music
    Mix_FreeMusic(GetInstance().m_runningMusic);
	GetInstance().m_runningMusic = NULL;

    Mix_FreeMusic(GetInstance().m_menuMusic);
    GetInstance().m_menuMusic = NULL;

	Mix_Quit();
}

void BOSoundManager::Update()
{

}

void BOSoundManager::PlaySound(Sound p_sound)
{
	switch (p_sound)
	{
    case SOUND_MUSIC:
        Mix_PlayMusic(GetInstance().m_runningMusic, -1);
        break;
    case SOUND_MUSIC2:
        Mix_PlayMusic(GetInstance().m_menuMusic, -1);
        break;
	case SOUND_POP:
		// Play in channel 0 so pop sound resets every time it plays
		Mix_PlayChannel(0, GetInstance().m_popHex, 0);
		break;
	case SOUND_DIE:
		Mix_PlayChannel(1, GetInstance().m_dying, 0);	// Channel -1 is nearest avaiable channel
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
    case SOUND_CHARGE:
        Mix_PlayChannel(2, GetInstance().m_charge, 0);
        break;
    case SOUND_SHOCKWAVE:
        Mix_PlayChannel(-1, GetInstance().m_shockwave, 0);
        break;
    case SOUND_SLOWDOWN:
        Mix_PlayChannel(3, GetInstance().m_slowDown, 0);
        break;
    case SOUND_SLOWUP:
        Mix_PlayChannel(3, GetInstance().m_slowUp, 0);
        break;
    case SOUND_THRUSTER:
        Mix_PlayChannel(4, GetInstance().m_thruster, 0);
        break;
    case SOUND_FUEL:
        Mix_PlayChannel(4, GetInstance().m_thruster, 3);
        break;
    case SOUND_BUMP:
        Mix_PlayChannel(-1, GetInstance().m_bump, 0);
        break;
	}
}

BOSoundManager& BOSoundManager::GetInstance()
{
	static BOSoundManager instance;
	return instance;
}