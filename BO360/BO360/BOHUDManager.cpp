#include "BOHUDManager.h"

bool BOHUDManager::m_livesEnabled;
bool BOHUDManager::m_scoreEnabled;
bool BOHUDManager::m_levelEnabled;
BODrawableText BOHUDManager::m_lives;
BODrawableText BOHUDManager::m_score;
BODrawableText BOHUDManager::m_level;
BOObject BOHUDManager::m_life;
int BOHUDManager::m_noLives;
float2 BOHUDManager::m_livesAnchor;
float2 BOHUDManager::m_scoreAnchor;
float2 BOHUDManager::m_levelAnchor;

float2 BOHUDManager::m_keyAnchor;
BOObject BOHUDManager::m_keySprite;
BODrawableText BOHUDManager::m_keyText;
bool BOHUDManager::m_keyEnabled;

float2 BOHUDManager::m_shockwaveAnchor;
BOObject BOHUDManager::m_shockwaveSprite;
bool BOHUDManager::m_shockwaveEnabled;


BOHUDManager::BOHUDManager()
{

}

BOHUDManager::~BOHUDManager()
{

}

bool BOHUDManager::Initialize()
{
	// Enable elements
	m_levelEnabled = true;
	m_scoreEnabled = true;
	m_livesEnabled = true;
	m_keyEnabled = true;
    m_shockwaveEnabled = false;
	m_noLives = 0;
	
	// Setting anchors
	int2 bounds = BOGraphicInterface::GetWindowSize();
	m_levelAnchor = float2(5, 0);
	m_livesAnchor = float2(bounds.x / 2.0f, 0);
	m_scoreAnchor = float2((float)bounds.x, 0);
	m_keyAnchor = float2(5, (float)bounds.y);
    m_shockwaveAnchor = float2(bounds.x / 2.0f, (float)bounds.y);

	// Initialize level
	m_level.Initialize(m_levelAnchor, "Level: ", int3(255, 255, 255), 30, 0);
	int2 tempSize = m_level.GetSize();
	m_level.SetPosition(float2(m_levelAnchor.x + (tempSize.x / 2), m_levelAnchor.y + (tempSize.y / 2)));

	//Initialize lives
	m_lives.Initialize(m_livesAnchor, "Lives: ", int3(255, 255, 255), 30, 0);
	m_life.Initialize(float2(0, 0), int2(20, 20), BOTextureManager::GetTexture(TEXLIFE)); // Always relative to m_lives position
	int2 tempSizeText = m_lives.GetSize();
	int2 tempSizeSprite = m_life.GetSize();

	int compundSizeX = tempSizeText.x + (tempSizeSprite.x + 2)*m_noLives; // Total size of the life component (text + (sprite+padding)*nosprites)
	m_lives.SetPosition(float2(m_livesAnchor.x - compundSizeX / 2.0f, m_livesAnchor.y + (tempSizeText.y / 2.0f)));
	m_life.SetPosition(float2(m_livesAnchor.x - (compundSizeX / 2.0f - tempSizeText.x) - tempSizeSprite.x, m_livesAnchor.y + (tempSizeSprite.y / 2.0f)));

	// Initialize score
	m_score.Initialize(m_scoreAnchor, "Score: ", int3(255, 255, 255), 30, 0);
	tempSize = m_score.GetSize();
	m_score.SetPosition(float2(m_scoreAnchor.x + (tempSize.x / 2.0f) - tempSize.x - 10.0f, m_scoreAnchor.y + (tempSize.y / 2.0f)));

	// Initialize keys
	m_keySprite.Initialize(float2(0, 0), int2(80, 80), 0.25f, BOTextureManager::GetTexture(TEXKEY));
	m_keyText.Initialize(float2(0, 0), "x 0 / 0", int3(255, 255, 255), 30, 0);
	tempSize = m_keySprite.GetSize();
	tempSizeText = m_keyText.GetSize();
	m_keySprite.SetPosition(float2(m_keyAnchor.x + tempSize.x / 2.0f, m_keyAnchor.y - tempSize.y / 2.0f));
	float2 tempPosition = m_keySprite.GetPosition();
	m_keyText.SetPosition(float2(5 + tempPosition.x + tempSizeSprite.x / 2.0f + tempSizeText.x / 2.0f, tempPosition.y));

    // Initialize shockwave
    m_shockwaveSprite.Initialize(float2(0, 0), int2(80, 80), 0.4f, BOTextureManager::GetTexture(TEXPUSHOCKWAVE));
    tempSize = m_shockwaveSprite.GetSize();
    m_shockwaveSprite.SetPosition(float2(m_shockwaveAnchor.x + tempSize.x / 2.0f, m_shockwaveAnchor.y - tempSize.y / 2.0f));

	return true;
}

void BOHUDManager::Shutdown()
{
	m_level.Shutdown();

	m_life.Shutdown();
	m_lives.Shutdown();

	m_score.Shutdown();

	m_keySprite.Shutdown();
	m_keyText.Shutdown();
}

void BOHUDManager::Draw()
{
	if (m_scoreEnabled)
	{
		m_score.Draw();
	}

	if (m_levelEnabled)
	{
		m_level.Draw();
	}

	if (m_livesEnabled)
	{
		m_lives.Draw();
		// Draw a life sprite for every life
		float2 tempPos = m_life.GetPosition();
		for (int i = 1; i < m_noLives+1; i++)
		{
			m_life.Draw();
			m_life.SetPosition(float2(tempPos.x + (m_life.GetSize().x+2)*i, tempPos.y));
		}
		m_life.SetPosition(tempPos);
	}

	if (m_keyEnabled)
	{
		m_keyText.Draw();
		m_keySprite.Draw();
	}

    if (m_shockwaveEnabled)
    {
        m_shockwaveSprite.Draw();
    }
}

void BOHUDManager::ModifyState(bool p_lives, bool p_score, bool p_level, bool p_keys, bool p_shockwave)
{
	m_livesEnabled = p_lives;
	m_scoreEnabled = p_score;
	m_levelEnabled = p_level;
	m_keyEnabled = p_keys;
    m_shockwaveEnabled = p_shockwave;
}

void BOHUDManager::SetLives(int p_lives)
{
	// Relative to the bottom of the anchor
	m_noLives = p_lives;
	std::string temp = "Lives: ";
	int2 tempSizeText = m_lives.GetSize();
	int2 tempSizeSprite = m_life.GetSize();
	int compundSizeX = tempSizeText.x + (tempSizeSprite.x+2)*m_noLives; // Total size of the life component (text + (sprite+padding)*nosprites)

	m_lives.SetPosition(float2(m_livesAnchor.x-compundSizeX/2, m_livesAnchor.y + (tempSizeText.y/2)));
	m_life.SetPosition(float2(m_livesAnchor.x - (compundSizeX/2-tempSizeText.x)-tempSizeSprite.x, m_livesAnchor.y + (tempSizeSprite.y / 2)));
}

void BOHUDManager::SetScore(int p_score)
{
	// Relative to the bottom-left of the anchor
	std::string temp = "Score: ";
	temp.append(std::to_string(p_score));
	m_score.SetText(temp, int3(255, 255, 255),0);

	int2 tempSize = m_score.GetSize();
	m_score.SetPosition(float2(m_scoreAnchor.x + (tempSize.x / 2) - tempSize.x - 10, m_scoreAnchor.y + (tempSize.y / 2)));
}

void BOHUDManager::SetLevel(int p_level)
{
	// Relative to the bottom-right of the anchor
	std::string temp = "Level: ";
	temp.append(std::to_string(p_level));
	m_level.SetText(temp, int3(255, 255, 255),0);
	int2 tempSize = m_level.GetSize();
	m_level.SetPosition(float2(m_levelAnchor.x + (tempSize.x/2), m_levelAnchor.y + (tempSize.y/2)));
}

void BOHUDManager::SetKeys(int p_keys, int p_maxKeys)
{
	// Relative to the top-right of the anchor

	// The sprite is already at the correct place

	// Set the text
	std::string tempString = "x ";
	tempString.append(std::to_string(p_keys));
	tempString.append(" / ");
	tempString.append(std::to_string(p_maxKeys));
	m_keyText.SetText(tempString, int3(255, 255, 255), 0);
	int2 tempTextSize = m_keyText.GetSize();
	int2 tempSizeSprite = m_keySprite.GetSize();
	float2 tempPosition = m_keySprite.GetPosition();
	m_keyText.SetPosition(float2(5+tempPosition.x + tempSizeSprite.x / 2.0f + tempTextSize.x / 2.0f, tempPosition.y));
}

void BOHUDManager::SetShockwave(bool p_active)
{
    m_shockwaveEnabled = p_active;
}