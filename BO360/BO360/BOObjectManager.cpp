#include "BOObjectManager.h"


BOObjectManager::BOObjectManager()
{
}


BOObjectManager::~BOObjectManager()
{
}

bool BOObjectManager::Initialize(int p_windowWidth, int p_windowHeight)
{
	bool result;
	
	int2 tempBlackHoleSize = int2(100, 100);
	// Set middle as position
	float2 tempBlackHolePos = float2((p_windowWidth / 2.0f) - (tempBlackHoleSize.x / 2), (p_windowHeight / 2.0f)-(tempBlackHoleSize.x / 2));
	
	result = m_blackHole.Initialize(tempBlackHolePos, tempBlackHoleSize, "..\BO360\Bilder\placeholderBlackhole.png");
	if (!result)
	{
		return false;
	}

	return true;
}

void BOObjectManager::Shutdown()
{

}

void BOObjectManager::Update()
{
	m_blackHole.Update();
}

void BOObjectManager::Draw()
{
	m_blackHole.Draw();
}