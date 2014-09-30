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
	m_life = 4;
	BOHUDManager::SetLives(m_life);

	// Initialize the map loader.
	bool result;
	result = m_mapLoader.Initialize();
	if (!result)
	{
		ThrowInitError("BOMapLoader");
		return false;
	}

	// Initialize the background.
	result = m_background.Initialize(float2(p_windowWidth / 2.0f, p_windowHeight / 2.0f), int2(p_windowWidth, p_windowHeight), "Sprites/PlaceHolderPNG/Background.png");
	if (!result)
	{
		ThrowInitError("BOBackground");
		return false;
	}

	// Initialize the black hole.
	result = m_blackHole.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(200, 200), "Sprites/PlaceHolderPNG/placeholderBlackhole110x110.png");
	if (!result)
	{
		ThrowInitError("BOBlackHole");
		return false;
	}

	// Initialize the pad.
	result = m_paddle.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(208, 208), "Sprites/PlaceHolderPNG/placeholderPadSegment5.png");
	if (!result)
	{
		ThrowInitError("BOPaddle");
		return false;
	}

	// Initialize the particle system.
	m_SecondsPerParticle = 0.0f;
	result = m_particleSystem.Initialize(MAXPARTICLES);
	if (!result)
	{
		ThrowInitError("BOParticleSystem");
		return false;
	}

	// Add an initial ball
	AddNewBall();

	// The first ball is a subscriber for debug purposes (space to control ball)
	BOPublisher::AddSubscriber(m_ballList[0]); 

	// Load the map
	LoadBlocksFromMap("Demo.bom");

	// Add subscriber so the object manager knows when a power up activates
	BOPowerUpManager::AddSubscriber(this);
	BOPublisher::AddSubscriber(this);

	m_Shield.Initialize(int2(200, 200), "Sprites/PlaceHolderPNG/Powerups/placeholderSheild.png", BOGraphicInterface::GetWindowSize());

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
	bool result;
	
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
		float2 pos = m_paddle.GetBallSpawnPosition();

		int2 windowSize = BOGraphicInterface::GetWindowSize();
		float2 ballDir = pos - float2((windowSize.x * 0.5f), (windowSize.y *0.5f));
		ballDir.normalize();
		pos.x += ballDir.x * 8;
		pos.y += ballDir.y * 8;
		m_ballList[0]->SetDirection(ballDir);
		m_ballList[0]->SetPosition(pos);
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
				float2 normal;

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
					BOSoundManager::PlaySound(SOUND_POP);
					//std::cout << "Ball bounced on [" << i << "]" << std::endl;

					if (m_blockList[i]->Hit(m_ballList[j]->GetDamage()))
					{
						// Create explosion.
						m_particleSystem.RegularBlockExplosion(m_blockList[i]->GetPosition());

						// Spawn powerup if there is one
						BOPowerUpManager::AddPowerUp(m_blockList[i]->GetPowerUp(), m_blockList[i]->GetPosition(), BOGraphicInterface::GetWindowSize(), &m_paddle, m_blackHole.GetPosition());

						// Add score
						BOScore::AddScore(m_blockList[i]->GetScore());

						m_blockList.erase(m_blockList.begin() + i);

					}
				}
			}
		}		
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
			//Beräkna bränsle
			m_ballList[i]->SetFuel(BOPhysics::CalculateBallFuel(m_ballList[i]->GetFuel(), p_deltaTime));
		}
		//Updaterar skölden
		float2 newdir = m_Shield.Update(p_deltaTime, m_ballList[i]->GetBoundingSphere(), m_ballList[i]->GetDirection());
		m_ballList[i]->SetDirection(newdir);
	}
	}
	}

	// Balls should be responsible for calculating when they want to spawn particles
	// This should be added after m_ballList[i]->Update()
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
			if (m_ballList[i]->GetFuel() > 0.0f)
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
			ball2->Initialize(m_ballList[0]->GetPosition(), int2(15, 15), "Sprites/PlaceHolderPNG/placeholderBoll10x10.png", m_ballList[0]->GetSpeed(), float2(m_ballList[0]->GetDirection().x * -1, m_ballList[0]->GetDirection().y * -1), int2(1300, 900));
			m_ballList.push_back(ball2);
		}
		break;
	}
}
void BOObjectManager::Handle(InputMessages p_inputMessage)
{
	if (p_inputMessage.spacebarKey)
	{
		m_releaseBall = true;

	}
}
bool BOObjectManager::AddNewBall()
{
	BOBall* ball = new BOBall();

	float2 ballPos = m_paddle.GetBallSpawnPosition();
	int2 windowSize = BOGraphicInterface::GetWindowSize();

	// Set the direction outwards from the screen center
	float2 ballDir = ballPos - float2(windowSize.x * 0.5f, windowSize.y * 0.5f);
	ballDir.normalize();
	ballPos.x += ballDir.x * 10;
	ballPos.y += ballDir.y * 10;

	if (!ball->Initialize(ballPos, int2(15,15), "Sprites/PlaceHolderPNG/placeholderBoll10x10.png", 400.0f, ballDir, windowSize))
	{
		ThrowInitError("BOBall");
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
	int2 windowSize = BOGraphicInterface::GetWindowSize();

	if (ballPos.x >= windowSize.x - checkPixelsInwards)//If out of bounds to the right
	{
		ballPos.x = windowSize.x - changePosToo;
	}
	if (ballPos.x <= checkPixelsInwards)//If out of bounds to the left
	{
		ballPos.x = changePosToo;
	}

	if (ballPos.y >= windowSize.y - checkPixelsInwards)//If out of bounds down
	{
		ballPos.y = windowSize.y - changePosToo;
	}
	if (ballPos.y <= checkPixelsInwards)//If out of bounds up
	{
		ballPos.y = changePosToo;
	}

	m_ballList[p_index]->SetPosition(ballPos);
}

bool BOObjectManager::LoadBlocksFromMap(std::string p_filename)
{
	// Load block descriptions from a map file
	m_mapLoader.LoadMap(p_filename);
	std::vector<Block> blockDescriptions = m_mapLoader.GetLoadedBlocks();
	
	float x = 0;
	float y = 0;
	bool result = false;

	// Hard coded constants for 40x40 hexagons
	static const float blockHeightDifference = 19; // The indentation of every other column
	static const int hexagonWidth = 32;
	static const int hexagonHeight = 37;
	static const int marginX = 60;
	static const int marginY = 50;

	for (int i = 0; i < blockDescriptions.size(); i++)
	{
		BOBlock* block;
		
		x = (hexagonWidth * blockDescriptions[i].m_position.x) + marginX;
		y = (hexagonHeight * blockDescriptions[i].m_position.y) + marginY;

		if ((int)blockDescriptions[i].m_position.x % 2 == 0) // Every other row
		{
			y += blockHeightDifference;
		}

		int score = blockDescriptions[i].m_worth;
		
		switch (blockDescriptions[i].m_type)
		{
			case(REGULAR) :
			{
				block = new BOBlock();

				// This fat chunk of code is to be removed when the map loader loads power ups
				if (i % 100 == 1)
				{
					result = block->Initialize(float2(x, y), int2(40, 40), "Sprites/PlaceholderPNG/Hexagons/placeholderHexagonPU2.png", PUShield, score);
				}
				else if (i % 100 == 33)
				{
					result = block->Initialize(float2(x, y), int2(40, 40), "Sprites/PlaceholderPNG/Hexagons/placeholderHexagonPU1.png", PUExtraBall, score);
				}
				else if (i % 100 == 66)
				{
					result = block->Initialize(float2(x, y), int2(40, 40), "Sprites/PlaceholderPNG/Hexagons/placeholderHexagonPU3.png", PUBiggerPad, score);
				}
				else
				{
					result = block->Initialize(float2(x, y), int2(40, 40), "Sprites/PlaceholderPNG/Hexagons/placeholderHexagon40x40.png", PUNone, score);
				}
				if (!result)
				{
					ThrowInitError("BOBlock");
					return false;
				}
				break;
			}

			case(DUBBLEHP) :
			{
				block = new BOBlockMultiTexture();
				result = block->Initialize(float2(x, y), int2(40, 40), "Sprites/PlaceholderPNG/Hexagons/placeholderHexagon40x40red1.png", 3, PUNone, score);
				if (!result)
				{
					ThrowInitError("BOBlockMultiTexture");
					return false;
				}
				
				dynamic_cast<BOBlockMultiTexture*>(block)->AddTextureForHPAbove("Sprites/PlaceholderPNG/Hexagons/placeholderHexagon40x40red2.png", 1);
				dynamic_cast<BOBlockMultiTexture*>(block)->AddTextureForHPAbove("Sprites/PlaceholderPNG/Hexagons/placeholderHexagon40x40red3.png", 2);
				break;
			}
	
			case(INDESTRUCTIBLE) :
			{
				block = new BOBlockIron();
				result = block->Initialize(float2(x, y), int2(40, 40), "Sprites/PlaceholderPNG/Hexagons/placeholderHexagon40x40gray.png", PUNone, score);
				if (!result)
				{
					ThrowInitError("BOBlockIron");
					return false;
				}
				break;
			}
			default:
			{
				std::cout << "Unknown block type in BOObjectManager::LoadBlocksFromMap" << std::endl;
				return false;
				break;
			}
		}
		m_blockList.push_back(block);
	}
	return true;
}