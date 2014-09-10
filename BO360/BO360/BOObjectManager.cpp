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
	
	// Initialize black hole.
	int2 blackHoleSize = int2(220, 220);
	float2 blackHolePosition = float2((p_windowWidth / 2.0f) - (blackHoleSize.x / 2), (p_windowHeight / 2.0f) - (blackHoleSize.y / 2));

	result = m_blackHole.Initialize(blackHolePosition, blackHoleSize, "Bilder/placeholderBlackhole.png");

	if (!result)
	{
		return false;
	}

	// Initialize primary ball.
	int2 ballSize = int2(40, 40);
	float2 ballPosition = float2(10, 10);

	BOBall ball;
	result = ball.Initialize(ballPosition, ballSize, "Bilder/placeholderBoll.png");
	m_ballList.push_back(ball);

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

	for (int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i].Update();
	}
}

void BOObjectManager::Draw()
{
	m_blackHole.Draw();

	for (int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i].Draw();
	}

}