#include "BOObjectManager.h"

BOObjectManager::BOObjectManager()
{
}


BOObjectManager::~BOObjectManager()
{
}

bool BOObjectManager::Initialize(int p_windowWidth, int p_windowHeight)
{
	m_releaseBall = false;
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
	result = m_background.Initialize(float2(p_windowWidth / 2.0f, p_windowHeight / 2.0f), int2(p_windowWidth, p_windowHeight), "Bilder/Background.png");
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
	result = m_paddle.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(220, 220), "Bilder/placeholderPadSegment3.png");
	if (!result)
	{
		return false;
	}

	// Initialize the particle system.
	m_SecondsPerParticle = 0.0f;
	result = m_particleSystem.Initialize(MAXPARTICLES);
	if (!result)
	{
		return false;
	}

	// Initialize primary ball.
	m_ballSize = int2(15, 15);
	m_ballSpeed = 500.0f;
	AddNewBall();

	BOPublisher::AddSubscriber(m_ballList[0]);

	// Load a map.
	m_mapLoader.LoadMap("Demo.bom");
	m_loadedBlocks = m_mapLoader.GetLoadedBlocks();

	float x = 0;
	float y = 0;
	float l_blockHeightDifference = 19;

	// Load blocks.
	for (unsigned int i = 0; i < m_loadedBlocks.size(); i++)
	{
		BOBlock* l_block;

		// If block should be an iron block
		// l_block = new BOBlockIron();
		// Else
		x = (32 * m_loadedBlocks[i].m_position.x) + 60;
		y = (37 * m_loadedBlocks[i].m_position.y) + 50;

		if ((int)m_loadedBlocks[i].m_position.x % 2 == 0)
		{
			y += l_blockHeightDifference;
		}

		int score = m_loadedBlocks[i].m_worth;

		switch (m_loadedBlocks[i].m_type)
		{
			case(REGULAR) :
			{
				l_block = new BOBlock();
		// Create block.
		if (i%100 == 1)
		{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagonPU2.png", PUShield, score);
		}
		else if (i%100 == 33)
		{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagonPU1.png", PUExtraBall, score);
		}
		else if (i%100 == 66)
		{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagonPU3.png", PUBiggerPad, score);
				}
				else
				{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagon40x40.png", PUNone, score);
				}
				if (!result)
				{
					return false;
				}
				break;
			}

			case(DUBBLEHP) :
			{
				l_block = new BOBlockMultiTexture();
				// Create block.
				/*
				if (i % 100 == 1)
				{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagonPU2.png", PUShield);
				}
				else if (i % 100 == 33)
				{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagonPU1.png", PUExtraBall);
				}
				else if (i % 100 == 66)
				{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagonPU3.png", PUBiggerPad);
				}
				else
				*/
				{
					result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagon40x40red1.png", 3, PUNone, score);
				}

				if (!result)
				{
					return false;
				}

				((BOBlockMultiTexture*)l_block)->AddTextureForHPAbove("Bilder/placeholderHexagon40x40red2.png", 1);
				((BOBlockMultiTexture*)l_block)->AddTextureForHPAbove("Bilder/placeholderHexagon40x40red3.png", 2);

				break;
			}

			case(INDESTRUCTIBLE) :
			{
				l_block = new BOBlockIron();
				result = l_block->Initialize(float2(x, y), int2(40, 40), "Bilder/placeholderHexagon40x40gray.png", PUNone, score);
				break;
			}

			default :
			{
				break;
			}
		}

		m_blockList.push_back(l_block);
	}

	// Add subscriber so the object manager knows when a power up activates
	BOPowerUpManager::AddSubscriber(this);

	BOPublisher::AddSubscriber(this);

	m_Shield.Initialize(int2(200, 200), "Bilder/placeholderSheild.png", m_windowsSize);

	return true;
}

void BOObjectManager::Shutdown()
{
	// Shut down the particle system.
	m_particleSystem.Shutdown();
	m_Shield.Shutdown();
	// Remove all balls
	for (unsigned int i = 0; i < m_ballList.size(); i++)
	{
		BOPublisher::Unsubscribe(m_ballList[i]); // Temp for cheat
		m_ballList[i]->Shutdown();
		delete m_ballList[i];
	}
	m_ballList.clear();

	// Clear the blocks
	m_loadedBlocks.clear();
	m_blockList.clear();

	// Call all the shutdowns
	m_mapLoader.Shutdown();
	m_background.Shutdown();
	m_blackHole.Shutdown();
	BOPublisher::Unsubscribe(&m_paddle);
	BOPublisher::Unsubscribe(this);
	m_paddle.Shutdown();
}

void BOObjectManager::Update(double p_deltaTime)
{
	float2 normal;
	
	m_blackHole.Update();

	m_paddle.Update(p_deltaTime);

	if (m_releaseBall)
	{
		for (unsigned int i = 0; i < m_ballList.size(); i++)
		{
			m_ballList[i]->Update(p_deltaTime);
		}
	}
	else
	{
		m_ballList[0]->SetPosition(ChangeBallPosAtStart());
	}

	for (unsigned int i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i]->Update();
	}

	for (unsigned int j = 0; j < m_ballList.size(); j++)
	{
		for (unsigned int i = 0; i < m_blockList.size(); i++)
		{
			box testBox = m_blockList[i]->GetBoundingBox();
			testBox.left -= 10; testBox.top -= 10; testBox.bottom += 10; testBox.right += 10;
			if (BOPhysics::CheckCollisionBoxToBox(m_ballList[j]->GetBoundingBox(), testBox))//m_blockList[i].GetBoundingBox()))
			{
				if (BOPhysics::CheckCollisionSphereToHexagon(m_ballList[j]->GetBoundingSphere(), m_blockList[i]->GetBoundingHexagon(), normal))
				{
					float angleBallNormal;
					float2 ballDir = m_ballList[j]->GetDirection();
					angleBallNormal = ballDir.dot(normal);
					if (angleBallNormal > -1 && angleBallNormal < 0)
					{
						// Block dead, dead = true, stop checking collision and drawing block.
						//m_blockList[i].SetDead();


						// Collision with hexagon.
						m_ballList[j]->SetDirection(BOPhysics::ReflectBallAroundNormal(m_ballList[j]->GetDirection(), normal));
						m_ballList[j]->BouncedOnHexagon();
						m_ballList[j]->SetFuel(0.0f);
						//std::cout << "Ball bounced on [" << i << "]" << std::endl;

						if (m_blockList[i]->Hit(m_ballList[j]->GetDamage()))
						{
							// Create explosion.
							m_particleSystem.RegularBlockExplosion(m_blockList[i]->GetPosition());

							// Spawn powerup if there is one
							if (m_blockList[i]->GetPowerUp() == PUExtraBall)
							{
								BOMultiballs* extraBall = new BOMultiballs();
								extraBall->Initialize(m_blockList[i]->GetPosition(), int2(40, 40), "Bilder/placeholderPowerupMultBall.png", 500.0f, m_windowsSize);
								extraBall->SetActive(true);
								BOPowerUpManager::AddPowerUp(extraBall);
							}

							else if (m_blockList[i]->GetPowerUp() == PUShield)
							{
								BOShieldPU* shield = new BOShieldPU();
								shield->Initialize(m_blockList[i]->GetPosition(), int2(30, 30), "Bilder/placeholderPowerup2.png", 500.0f, m_windowsSize);
								BOPowerUpManager::AddPowerUp(shield);
							}
							else if (m_blockList[i]->GetPowerUp() == PUBiggerPad)
							{
								BOPUPadSize* biggerPad = new BOPUPadSize();
								biggerPad->Initialize(m_blockList[i]->GetPosition(), int2(30, 30), "Bilder/placeholderPowerup3.png", 500.0f, m_windowsSize);
								BOPowerUpManager::AddPowerUp(biggerPad);
							}

							// Collision therfore play popsound

							BOSoundManager::PlaySound(SOUND_POP);

							// Add score
							BOScore::AddScore(m_blockList[i]->GetScore());

							m_blockList.erase(m_blockList.begin() + i);

						}
					}
				}
			}
		}
	}		
	// Tillf�llig powerup kollision kod f�r att testa 
	// Checks powerup "ball" against the pad, if colliding with pad do powerup effect and remove powerup"ball"
	for (int i = 0; i < BOPowerUpManager::GetPowerUpSize(); i++)
	{
		float2 result = BOPhysics::BallPadCollision(BOPowerUpManager::GetPowerUp(i)->GetBoundingSphere(), BOPowerUpManager::GetPowerUp(i)->GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() - 10.6, m_paddle.GetDegrees());
		if (!(result.x == 0 && result.y == 0))
		{
			// Play sound for PowerUp catched
			BOSoundManager::PlaySound(SOUND_POWERUP);

			BOPowerUp* pu = BOPowerUpManager::GetPowerUp(i);
			BOShieldPU* puShield;
			BOMultiballs* puBall;
			BOPUPadSize* puPad;

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
			case PUBiggerPad:
				puPad = (BOPUPadSize*)pu;
				puPad->Activate();
				break;
			}

			BOPowerUpManager::RemovePowerUp(i);
		}		

		else if (BOPhysics::CheckCollisionSpheres(BOPowerUpManager::GetPowerUp(i)->GetBoundingSphere(), sphere(m_blackHole.GetPosition(), 1)))
		{
			BOPowerUpManager::RemovePowerUp(i);
		}
	}
	if (m_releaseBall)
	{
		for (unsigned int i = 0; i < m_ballList.size(); i++)
		{
			CheckBallOutOfBounds(i);
			bool ballDied = false;
			if (m_ballList[i]->CanColide())
			{
				float2 result = BOPhysics::BallPadCollision(m_ballList[i]->GetBoundingSphere(), m_ballList[i]->GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() -10.5, m_paddle.GetDegrees());
				if (!(result.x == 0 && result.y == 0))
				{
					m_ballList[i]->SetDirection(result);
					m_ballList[i]->BouncedOnPad();

					// Play sound for bounce on pad
					BOSoundManager::PlaySound(SOUND_BOUNCEONPAD);
				}

				// Check if ball has entered the black hole and should die
			
				if (BOPhysics::CollisionRadiusRadius(m_ballList[i]->GetPosition(), m_ballList[i]->GetSize().x / 2.0f, m_blackHole.GetPosition(), m_blackHole.GetSize().x / 4.0f))
				{
					// Remove the current ball
					BOPublisher::Unsubscribe(m_ballList[i]); // Temporary for cheat with first ball
					m_ballList[i]->Shutdown();
					delete m_ballList[i];
					m_ballList.erase(m_ballList.begin() + i);
					ballDied = true;

					// If no more ball in list then loose a life
					if (m_ballList.size() == 0)
					{
						m_life--;
						BOHUDManager::SetLives(m_life);
						if (m_life > 0)
						{
							AddNewBall();
						}
					}
				}
			}
		
			if (ballDied)
			{
				i--;
			}
			else
			{
				if (m_ballList[i]->GetFuel() <= 0)
				{
					//Runs tha gravity... lawl... Rotates the direction depending on distance
					m_ballList[i]->SetDirection(BOPhysics::BlackHoleGravity(m_ballList[i]->GetBoundingSphere(), m_ballList[i]->GetDirection(), m_ballList[i]->GetSpeed(), m_blackHole.GetBoundingSphere(), p_deltaTime));
				}
				else
				{
					//Ber�kna br�nsle
					m_ballList[i]->SetFuel(BOPhysics::CalculateBallFuel(m_ballList[i]->GetFuel(), p_deltaTime));
				}
			//Updaterar sk�lden
			m_ballList[i]->SetDirection((m_Shield.Update(p_deltaTime, m_ballList[i]->GetBoundingSphere(), m_ballList[i]->GetDirection())));
			}
		}
	}

	// Increment time passed.
	m_SecondsPerParticle -= p_deltaTime;

	if (BALLDEBUGTRAIL == 1 && m_SecondsPerParticle < 0.0f)
	{
		for (unsigned int i = 0; i < m_ballList.size(); i++)
		{
			m_particleSystem.BallDebugTrail(m_ballList[i]->GetPosition());
		}

		m_SecondsPerParticle = 0.002f;
	}
	
	else if (m_releaseBall && m_SecondsPerParticle < 0.0f)
	{
		for (unsigned int i = 0; i < m_ballList.size(); i++)
		{
			if (m_ballList[i]->GetFuel() > 0)
			{
				m_particleSystem.BallTrail(m_ballList[i]->GetPosition());
			}
		}

		m_SecondsPerParticle = 0.025f;
	}

	m_particleSystem.Update(p_deltaTime);
}

void BOObjectManager::Draw()
{
	m_background.Draw();

	m_blackHole.Draw();

	for (unsigned int i = 0; i < m_blockList.size(); i++)
	{
		if (!m_blockList[i]->GetDead())
		{
			m_blockList[i]->Draw();
		}
		
	}
		
	m_particleSystem.DrawParticles();

	for (unsigned int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i]->Draw();
	}

	m_Shield.Draw();
	m_paddle.Draw();
	
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
void BOObjectManager::Handle(InputMessages p_inputMessage)
{
	if (p_inputMessage.upArrow)
	{
		m_releaseBall = true;
	}
}
bool BOObjectManager::AddNewBall()
{
	BOBall* ball = new BOBall();

	m_ballStartPosition = ChangeBallPosAtStart();
	m_ballDirection = float2((m_windowsSize.x * 0.5f), (m_windowsSize.y *0.5f)).normalized();
	if (!ball->Initialize(m_ballStartPosition, m_ballSize, "Bilder/placeholderBoll10x10.png", m_ballSpeed, m_ballDirection, m_windowsSize))
	{
		return false;
	}
	m_releaseBall = false;
	m_ballList.push_back(ball);
	return true;
}

bool BOObjectManager::LostGame()
{
	return m_life == 0;
}
void BOObjectManager::CheckBallOutOfBounds(int p_index)
{
	float changePosToo = 10.0f;
	int checkPixelsInwards = 7;
	float2 ballPos = m_ballList[p_index]->GetPosition();

	if (ballPos.x >= m_windowsSize.x - checkPixelsInwards)//If out of bounds to the right
	{
		ballPos.x = m_windowsSize.x - changePosToo;
	}
	if (ballPos.x <= checkPixelsInwards)//If out of bounds to the left
	{
		ballPos.x = changePosToo;
	}

	if (ballPos.y >= m_windowsSize.y - checkPixelsInwards)//If out of bounds down
	{
		ballPos.y = m_windowsSize.y - changePosToo;
	}
	if (ballPos.y <= checkPixelsInwards)//If out of bounds up
	{
		ballPos.y = changePosToo;
	}

	m_ballList[p_index]->SetPosition(ballPos);
}
float2 BOObjectManager::ChangeBallPosAtStart()
{
	float2 startPos;
	float tempx = m_paddle.GetPosition().x + (m_paddle.GetSize().x * 0.5f) * (float)cos(((-m_paddle.GetRotation() - (21 * (m_paddle.GetSegments() - 1))) * (float)m_PIDiv180) + 2);
	float tempy = m_paddle.GetPosition().y - (m_paddle.GetSize().y * 0.5f) * (float)sin(((-m_paddle.GetRotation() - (21 * (m_paddle.GetSegments() - 1))) * (float)m_PIDiv180) + 2);
	startPos = float2(tempx, tempy);
	
	return startPos;
}