#include "BOObjectManager.h"

BOObjectManager::BOObjectManager()
{
}


BOObjectManager::~BOObjectManager()
{
}

bool BOObjectManager::Initialize(int p_windowWidth, int p_windowHeight)
{
	m_windowsSize = int2(p_windowWidth, p_windowHeight);
	bool result;
	m_hasColided = false;
	m_life = 4;
	BOHUDManager::SetLives(m_life);

	// Initialize the map loader.
	result = m_mapLoader.Initialize();
	if (!result)
	{
		return false;
	}

	// Initialize the background.
	result = m_background.Initialize(float2(p_windowWidth / 2, p_windowHeight / 2), int2(p_windowWidth, p_windowHeight), "Bilder/Background.png");
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
	result = m_paddle.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(220, 220), "Bilder/placeholderPadBIG.png");
	if (!result)
	{
		return false;
	}

	// Initialize primary ball.
	int2 ballSize = int2(15, 15);

	float2 ballPosition = float2(20, 20);
	float ballSpeed = 0.25f;
	float2 ballDirection = float2(20, 10).normalized();

	BOBall* ball = new BOBall();
	result = ball->Initialize(ballPosition, ballSize, "Bilder/placeholderBoll10x10.png", ballSpeed, ballDirection, m_windowsSize);
	if (!result)
	{
		return false;
	}

	m_ballList.push_back(ball);
	BOPublisher::AddSubscriber(m_ballList[0]);

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
		if (i != 0)
		{
			result = l_block.Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagon40x40.png", PUNone);
			if (!result)
			{
				return false;
			}
		}
		else if (i == 0)
		{
			result = l_block.Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagon40x40.png", PUShield);
		}
		

		m_blockList.push_back(l_block);
	}

	// Add subscriber so the object manager knows when a power up activates
	BOPowerUpManager::AddSubscriber(this);

	m_Shield.Initialize(int2(200, 200), "Bilder/placeholderSheild.png", m_windowsSize);
	return true;
}

void BOObjectManager::Shutdown()
{
	m_Shield.Shutdown();
}

void BOObjectManager::Update(Uint32 p_deltaTime)
{
	bool result;
	float2 normal;
	
	m_blackHole.Update();

	m_paddle.Update(p_deltaTime);

	for (int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i]->Update(p_deltaTime);
	}
	for (int i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i].Update();
	}

	for (int i = 0; i < m_blockList.size(); i++)
	{
		if (!m_blockList[i].GetDead())
		{
			for (int j = 0; j < m_ballList.size(); j++)
			{
				if (BOPhysics::CheckCollisionSpheres(m_ballList[j]->GetBoundingSphere(), m_blockList[i].GetBoundingSphere()))
				{
					if (BOPhysics::CheckCollisionSphereToHexagon(m_ballList[j]->GetBoundingSphere(), m_blockList[i].GetBoundingHexagon(), normal))
					{
						// Block dead, dead = true, stop checking collision and drawing block
						m_blockList[i].SetDead();
						//Collision with hexagon
						m_ballList[j]->SetDirection(BOPhysics::ReflectBallAroundNormal(m_ballList[j]->GetDirection(), normal));
						m_ballList[j]->BouncedOnHexagon();
						m_ballList[j]->SetFuel(0.0f);
					
						// Spawn powerup if there is one
						if (m_blockList[i].GetPowerUp() == PUExtraBall)
						{
							BOMultiballs* extraBall = new BOMultiballs();
							extraBall->Initialize(m_blockList[i].GetPosition(), int2(40, 40), "Bilder/placeholderPowerupMultBall.png", 0.5f, m_windowsSize);
							extraBall->SetActive(true);
							BOPowerUpManager::AddPowerUp(extraBall);
						}
						else if (m_blockList[i].GetPowerUp() == PUShield)
						{
							BOShieldPU* shield = new BOShieldPU();
							shield->Initialize(m_blockList[i].GetPosition(), int2(40, 40), "Bilder/placeholderSheildPowerUp1.png", 0.5f, m_windowsSize);
							BOPowerUpManager::AddPowerUp(shield);
						}

						// Collision therfore play popsound
						BOSoundManager::PlaySound(sound_pop);
						break;
					}
				}
			}
			
		}		
	}
	
	// Tillfällig powerup kollision kod för att testa 
	// Checks powerup "ball" against the pad, if colliding with pad do powerup effect and remove powerup"ball"
	for (int i = 0; i < BOPowerUpManager::GetPowerUpSize(); i++)
	{
		float2 result = BOPhysics::BallPadCollision(BOPowerUpManager::GetPowerUp(i)->GetBoundingSphere(), BOPowerUpManager::GetPowerUp(i)->GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() - 15, 30);
		if (!(result.x == 0 && result.y == 0))
		{
			BOPowerUp* pu = BOPowerUpManager::GetPowerUp(i);
			BOShieldPU* puShield;
			BOMultiballs* puBall;
			switch (pu->GetType())
			{
			case PUShield:
				puShield = (BOShieldPU*)pu;
				puShield->Activate();
				break;
			case PUExtraBall:
				puBall = (BOMultiballs*)pu;
				puBall->Activate();
				break;
			}
			BOPowerUpManager::RemovePowerUp(i);
		}		
		else if (BOPhysics::CheckCollisionSpheres(BOPowerUpManager::GetPowerUp(i)->GetBoundingSphere(), sphere(m_blackHole.GetPosition(), 1)))
		{
			BOPowerUpManager::RemovePowerUp(i);
	}
	}



 	for (int i = 0; i < m_ballList.size(); i++)
	{
		if (m_ballList[i]->CanColide())
		{
			// Check for collison between ball and pad
			float2 result = BOPhysics::BallPadCollision(m_ballList[i]->GetBoundingSphere(), m_ballList[i]->GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() -45, 90);
			if (!(result.x == 0 && result.y == 0))
			{
				m_ballList[i]->SetDirection(result);
				m_ballList[i]->BouncedOnPad();
			}

			// Check if ball has entered the black hole and should die
			if (BOPhysics::CollisionRadiusRadius(m_ballList[i]->GetPosition(), m_ballList[i]->GetSize().x / 2.0f, m_blackHole.GetPosition(), m_blackHole.GetSize().x / 4.0f))
			{
				int a = 0;
			}
		}
		
		if (m_ballList[i]->GetFuel() <= 0)
		{
			//Runs tha gravity... lawl... Rotates the direction depending on distance
			m_ballList[i]->SetDirection(BOPhysics::BlackHoleGravity(m_ballList[i]->GetBoundingSphere(), m_ballList[i]->GetDirection(), m_ballList[i]->GetSpeed(), m_blackHole.GetBoundingSphere()));
		}
		else
		{
			//Beräkna bränsle
			m_ballList[i]->SetFuel(BOPhysics::CalculateBallFuel(m_ballList[i]->GetFuel()));

		}
		//Updaterar skölden
		BallDirectionChange(m_Shield.Update(p_deltaTime, m_ballList[i]->GetBoundingSphere()), i);
	}

	
}

void BOObjectManager::Draw()
{
	m_background.Draw();

	m_blackHole.Draw();

	for (int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i]->Draw();
	}
	for (int i = 0; i < m_blockList.size(); i++)
	{
		if (!m_blockList[i].GetDead())
		{
			m_blockList[i].Draw();
		}
		
	}

	m_paddle.Draw();
	m_Shield.Draw();
}
void BOObjectManager::BallDirectionChange(int p_bounceCorner, int p_Index)
{
	if (p_bounceCorner == 0)
		return;
	m_hasColided = true;

	float2 ballDir = m_ballList[p_Index]->GetDirection();
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
	m_ballList[p_Index]->SetDirection(ballDir);
}

void BOObjectManager::Handle(PowerUpTypes p_type, bool p_activated)
{
	switch (p_type)
	{
	case PUShield:
		if (p_activated)
		{
			m_Shield.SetActive(true);
		}
		break;
	case PUExtraBall:
		if (p_activated)
		{
			BOBall* ball2 = new BOBall();
			ball2->Initialize(m_ballList[0]->GetPosition(), int2(15, 15), "Bilder/placeholderBoll10x10.png", m_ballList[0]->GetSpeed(), float2(m_ballList[0]->GetDirection().x * -1, m_ballList[0]->GetDirection().y * -1), int2(1300, 900));
			m_ballList.push_back(ball2);
		}
		break;
	}
}