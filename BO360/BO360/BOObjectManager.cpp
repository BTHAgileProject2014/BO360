#include "BOObjectManager.h"

BOObjectManager::BOObjectManager()
{
}


BOObjectManager::~BOObjectManager()
{
}

bool BOObjectManager::Initialize(int p_windowWidth, int p_windowHeight)
{
	int2 windowSize;
	windowSize.x = p_windowWidth;
	windowSize.y = p_windowHeight;
	bool result;
	m_hasColided = false;

	// Initialize the background.
	result = m_background.Initialize(float2(p_windowWidth / 2, p_windowHeight / 2), int2(p_windowWidth, p_windowHeight), "Bilder/background.png");
	if (!result)
	{
		return false;
	}

	// Initialize the black hole.
	result = m_blackHole.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(200, 200), "Bilder/placeholderBlackhole110x110.png");
	if (!result)
	{
		return false;
	}

	// Initialize the pad.
	result = m_paddle.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(240, 240), "Bilder/placeholderPad2.png");
	if (!result)
	{
		return false;
	}

	// Initialize primary ball.
	int2 ballSize = int2(15, 15);

	float2 ballPosition = float2(30, 30);
	float ballSpeed = 0.1f;
	float2 ballDirection = float2(10, 10);

	BOBall ball;
	result = ball.Initialize(ballPosition, ballSize, "Bilder/placeholderBoll10x10.png", ballSpeed, ballDirection, windowSize);
	if (!result)
	{
		return false;
	}

	m_ballList.push_back(ball);
	BOPublisher::AddSubscriber(&m_ballList[0]);

	float diff = 17;
	for (int i = 0; i < 38; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			BOBlock block;
			float x = (32 * i) + 60;
			float y = (35 * j) + 45;
			if (i % 2 == 0)
			{
				y += diff;
			}
			result = block.Initialize(float2(x, y), int2(40,40), "Bilder/placeholderHexagon40x40.png");
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


	if (m_ballList[0].CanColide())
	{
		
		int bounceTest = BOPhysics::CheckCollisioPadSphere(m_ballList[0].GetBoundingSphere(), m_ballList[0].GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() - 15, 30);
		if (bounceTest > 0)
		{
			m_ballList[0].BouncedOnPad();
		}
		BallDirectionChange(bounceTest);
	/*	if (BOPhysics::MattiasBallPadCollision(m_ballList[0].GetBoundingSphere(), m_ballList[0].GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() - 20, 40))
		{*/
			//sphere changedSphere = m_paddle.GetBoundingSphere();
			//changedSphere.radius -= 1;
			//if (!BOPhysics::CheckCollisionSpheres(m_ballList[0].GetBoundingSphere(), changedSphere))
			//{
			//	std::cout << "Colided!";
			//	float2 newDir = m_ballList[0].GetDirection();
			//	newDir.x *= -1.0f;
			//	newDir.y *= -1.0f;
			//	newDir = newDir.normalized();
			//	m_ballList[0].SetDirection(newDir);
			//	m_ballList[0].BouncedOnPad();
			//}

		//}
	}
}

void BOObjectManager::Draw()
{
	m_background.Draw();

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
		//std::cout << "Krock" << std::endl;
	}
	else//Straight right and left corner
	{
		ballDir.x *= (-1);
		//std::cout << "Krock" << std::endl;
	}
	m_ballList[0].SetDirection(ballDir);
}