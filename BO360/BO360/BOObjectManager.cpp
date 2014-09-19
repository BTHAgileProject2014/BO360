#include "BOObjectManager.h"

BOObjectManager::BOObjectManager()
{
	m_GravityIsOn = true;
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

	// Initialize the map loader.
	result = m_mapLoader.Initialize();
	if (!result)
	{
		return false;
	}

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

	float2 ballPosition = float2(100, 300);
	float ballSpeed = 0.5f;
	float2 ballDirection = float2(20, 10);
	
	BOBall ball;
	result = ball.Initialize(ballPosition, ballSize, "Bilder/placeholderBoll10x10.png", ballSpeed, ballDirection, windowSize);
	if (!result)
	{
		return false;
	}

	m_ballList.push_back(ball);
	BOPublisher::AddSubscriber(&m_ballList[0]);

	// Load a map.
	m_mapLoader.LoadMap("Default.bom");
	m_blockPositions = m_mapLoader.GetBlockPositions();

	float x = 0;
	float y = 0;
	float l_blockHeightDifference = 19;

	// Load blocks.
	for (int i = 0; i < m_blockPositions.size();  i++)
	{
		BOBlock l_block;
		x = (32 * m_blockPositions[i].x) + 60;
		y = (37 * m_blockPositions[i].y) + 50;

		if ((int)m_blockPositions[i].x % 2 == 0)
		{
			y += l_blockHeightDifference;
		}

		// Create block.
		result = l_block.Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagon40x40.png");
		if (!result)
		{
			return false;
		}
		m_blockList.push_back(l_block);
	}
	/*float2 test = m_ballList[0].GetDirection();
	test = float2(10,10);*/
	return true;
}

void BOObjectManager::Shutdown()
{

}

void BOObjectManager::Update(Uint32 p_deltaTime)
{
	bool result;
	float2 normal;
	float2 newBallDirection;
	float vDotN;
	float2 nMinusV;
	float angleBallDirectionVsNormal;
	m_blackHole.Update();

	m_paddle.Update(p_deltaTime);

	for (int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i].Update(p_deltaTime);
	}
	for (int i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i].Update();
	}

	for (int i = 0; i < m_blockList.size(); i++)
	{
		if (!m_blockList[i].GetDead())
		{
			if (BOPhysics::CheckCollisionSpheres(m_ballList[0].GetBoundingSphere(), m_blockList[i].GetBoundingSphere()))
			{
				if (BOPhysics::CheckCollisionSphereToHexagon(m_ballList[0].GetBoundingSphere(), m_blockList[i].GetBoundingHexagon(), normal))
				{
					// Block dead, dead = true, stop checking collision and drawing block
					m_blockList[i].SetDead();
					//Collision with hexagon
					m_ballList[0].SetDirection(BOPhysics::ReflectBallAroundNormal(m_ballList[0].GetDirection(), normal));
					m_ballList[0].BouncedOnHexa();
					//Changes the gravity to true so it can be pulled into the middle
					m_GravityIsOn = true;
					
					// Collision therfore play popsound
					BOSoundManager::PlaySound(sound_pop);
					break;
				}
			}
		}
	}


	if (m_ballList[0].CanColide())
	{
		
		int bounceTest = BOPhysics::CheckCollisioPadSphere(m_ballList[0].GetBoundingSphere(), m_ballList[0].GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() - 15, 30);
		if (bounceTest > 0)
		{
			m_ballList[0].BouncedOnPad();
			m_GravityIsOn = false;//Changes the gravity to false so it doesn't stuck fuck
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
	//Runs tha gravity... lawl... Rotates the direction depending on distance
	m_ballList[0].SetDirection(BOPhysics::BlackHoleGravity(m_ballList[0].GetBoundingSphere(), m_ballList[0].GetDirection(), m_ballList[0].GetSpeed(), m_blackHole.GetBoundingSphere(), m_GravityIsOn));


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

void BOObjectManager::Handle(PowerUpTypes p_type, bool p_activated)
{
	switch (p_type)
	{
	case PUShield:
		// Add shield??
		break;
	case PUExtraBall:
		// Add ball to the vector
		break;
	}
}