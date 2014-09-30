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

BOHUDManager::BOHUDManager()
{
}


BOHUDManager::~BOHUDManager()
{
}

bool BOHUDManager::Initialize()
{
	m_levelEnabled = true;
	m_scoreEnabled = true;
	m_livesEnabled = true;
	m_noLives = 0;
	
	// Setting anchors
	int2 bounds = BOGraphicInterface::GetWindowSize();
	m_levelAnchor = float2(10, 0);
	m_livesAnchor = float2(bounds.x / 2.0f, 0);
	m_scoreAnchor = float2((float)bounds.x, 0);

	m_level.Initialize(m_levelAnchor, "Level: ", int3(255, 255, 255), 30, 0);
	int2 tempSize = m_level.GetSize();
	m_level.SetPosition(float2(m_levelAnchor.x + (tempSize.x / 2), m_levelAnchor.y + (tempSize.y / 2)));

	m_lives.Initialize(m_livesAnchor, "Lives: ", int3(255, 255, 255), 30, 0);
	m_life.Initialize(float2(0, 0), int2(20, 20), "Bilder/placeholderLife.png"); // Always relative to m_lives position
	int2 tempSizeText = m_lives.GetSize();
	int2 tempSizeSprite = m_life.GetSize();
	int compundSizeX = tempSizeText.x + (tempSizeSprite.x + 2)*m_noLives; // Total size of the life component (text + (sprite+padding)*nosprites)
	m_lives.SetPosition(float2(m_livesAnchor.x - compundSizeX / 2, m_livesAnchor.y + (tempSizeText.y / 2)));
	m_life.SetPosition(float2(m_livesAnchor.x - (compundSizeX / 2 - tempSizeText.x) - tempSizeSprite.x, m_livesAnchor.y + (tempSizeSprite.y / 2)));

	m_score.Initialize(m_scoreAnchor, "Score: ", int3(255, 255, 255), 30, 0);
	tempSize = m_score.GetSize();
	m_score.SetPosition(float2(m_scoreAnchor.x + (tempSize.x / 2) - tempSize.x - 10, m_scoreAnchor.y + (tempSize.y / 2)));

	return true;
}

void BOHUDManager::Shutdown()
{
	m_life.Shutdown();
	m_level.Shutdown();
	m_lives.Shutdown();
	m_score.Shutdown();
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
}

void BOHUDManager::ModifyState(bool p_lives, bool p_score, bool p_level)
{
	m_livesEnabled = p_lives;
	m_scoreEnabled = p_score;
	m_levelEnabled = p_level;
}

void BOHUDManager::SetLives(int p_lives)
{
	// Relative to the center of the anchor
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
	// Relative to the left of the anchor
	std::string temp = "Score: ";
	temp.append(std::to_string(p_score));
	m_score.SetText(temp, int3(255, 255, 255),0);
	int2 tempSize = m_score.GetSize();
	m_score.SetPosition(float2(m_scoreAnchor.x + (tempSize.x / 2) - tempSize.x - 10, m_scoreAnchor.y + (tempSize.y / 2)));
}

void BOHUDManager::SetLevel(int p_level)
{
	// Relative to the right of the anchor
	std::string temp = "Level: ";
	temp.append(std::to_string(p_level));
	m_level.SetText(temp, int3(255, 255, 255),0);
	int2 tempSize = m_level.GetSize();
	m_level.SetPosition(float2(m_levelAnchor.x + (tempSize.x/2), m_levelAnchor.y + (tempSize.y/2)));
}