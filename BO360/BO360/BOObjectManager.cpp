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
	m_hasColided = false;
	
	// Initialize black hole.
	int2 blackHoleSize = int2(220, 220);
	float2 blackHolePosition = float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f));

	result = m_blackHole.Initialize(blackHolePosition, blackHoleSize, "Bilder/placeholderBlackhole.png");
	if (!result)
	{
		return false;
	}
	result = m_paddle.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(220, 220), "Bilder/placeholderPad.png");
	if (!result)
	{
		return false;
	}

	// Initialize primary ball.
	int2 ballSize = int2(40, 40);
	float2 ballPosition = float2(30, 30);
	float ballSpeed = 0.1f;
	float2 ballDirection = float2(10, 15);
	BOBall ball;
	result = ball.Initialize(ballPosition, ballSize, "Bilder/placeholderBoll.png", ballSpeed, ballDirection);
	if (!result)
	{
		return false;
	}

	m_ballList.push_back(ball);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			BOBlock block;
			result = block.Initialize(float2(((85*i) + 60), (45+(510*j))), int2(80,80), "Bilder/placeholderHexagon.png");
			if (!result)
			{
				return false;
			}
			m_blockList.push_back(block);
		}
	}

	return true;
}

void BOObjectManager::Shutdown()
{

}

void BOObjectManager::Update()
{
	bool result;
	m_blackHole.Update();

	m_paddle.Update();

	for (int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i].Update();
	}
	for (int i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i].Update();
	}

	for (int i = 0; i < m_blockList.size(); i++)
	{
		if (BOPhysics::CheckCollisionBoxToBox(m_ballList[0].GetBoundingBox(), m_blockList[i].GetBoundingBox()))
		{
			if (BOPhysics::CheckCollisionSphereToHexagon(m_ballList[0].GetBoundingSphere(), m_blockList[i].GetBoundingHexagon()))
			{
				m_blockList[i].SetDead();
			}
		}		
	}

	if (!BOPhysics::CheckCollisionSpheres(m_ballList[0].GetBoundingSphere(), m_blackHole.GetBoundingSphere()))
	{
		m_hasColided = false;
	}
	
	if (!m_hasColided)
	{
		int bounceCorner = BOPhysics::CheckCollisioPadSphere(m_blackHole.GetBoundingSphere().pos, m_blackHole.GetBoundingSphere().radius, 0.0f, m_ballList[0].GetBoundingSphere().pos, m_ballList[0].GetBoundingSphere().radius);
		BallDirectionChange(bounceCorner);
	}
}

void BOObjectManager::Draw()
{
	m_blackHole.Draw();

	for (int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i].Draw();
	}
	for (int i = 0; i < m_blockList.size(); i++)
	{
		if (!m_blockList[i].GetDead())
		{
			m_blockList[i].Draw();
		}
		
	}

	m_paddle.Draw();

}
void BOObjectManager::BallDirectionChange(int p_bounceCorner)
{
	if (p_bounceCorner == 0)
		return;
	m_hasColided = true;

	float2 ballDir = m_ballList[0].GetDirection();
	if (p_bounceCorner == 1 || p_bounceCorner == 2)//Straight up and down corner
	{
		ballDir.y *= (-1);
	}
	else//Straight right and left corner
	{
		ballDir.x *= (-1);
	}
	m_ballList[0].SetDirection(ballDir);
}