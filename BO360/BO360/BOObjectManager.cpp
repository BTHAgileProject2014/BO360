#include "BOObjectManager.h"

BOObjectManager::BOObjectManager()
{

}

BOObjectManager::~BOObjectManager()
{

}

bool BOObjectManager::Initialize(int p_windowWidth, int p_windowHeight, int p_LevelIndex)
{
	m_life = 4;
	BOHUDManager::SetLives(m_life);
    m_continue = false;

	// Initialize the map loader.
	bool result;
	result = m_mapLoader.Initialize();
	if (!result)
	{
		ThrowInitError("BOMapLoader");
		return false;
	}

	// Initialize the background.
	result = m_background.Initialize(float2(p_windowWidth / 2.0f, p_windowHeight / 2.0f), int2(p_windowWidth, p_windowHeight), BOTextureManager::GetTexture(TEXBACKGROUND));
	if (!result)
	{
		ThrowInitError("BOBackground");
		return false;
	}

	// Initialize the black hole.
	result = m_blackHole.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(200, 200), BOTextureManager::GetTexture(TEXBLACKHOLE));
	if (!result)
	{
		ThrowInitError("BOBlackHole");
		return false;
	}

	// Initialize the pad.
    result = m_paddle.Initialize(float2((p_windowWidth / 2.0f), (p_windowHeight / 2.0f)), int2(208, 208), int2(208, 208), 0, 4, 0.075, false, BOTextureManager::GetTexture(TEXPADSEG));
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

	// Initialize the key manager
	result = m_keyManager.Initialize();
	if (!result)
	{
		std::cout << "Initialize key manager failed!" << std::endl;

		return false;
	}

	// Add an initial ball
	AddNewBall();

	// The first ball is a subscriber for debug purposes (space to control ball)
	BOPublisher::AddSubscriber(m_ballList[0]); 

	// Load the map
	LoadBlocksFromMap(p_LevelIndex);

	// Add subscriber so the object manager knows when a power up activates
	BOPowerUpManager::AddSubscriber(this);
	BOPublisher::AddSubscriber(this);


	m_Shield.Initialize(int2(200, 200), BOTextureManager::GetTexture(TEXSHIELD), BOGraphicInterface::GetWindowSize());

    // Add the shockwave
    m_shockwave = BOShockwave();
    result = m_shockwave.Initialize();
    if (!result)
    {
        std::cout << "Initialize shockwave failed" << std::endl;

        return false;
    }

    // Initialize SlowTime powerup functionality
    result = m_slowTime.Initialize();
    if (!result)
    {
        std::cout << "Initialize slow time failed" << std::endl;

        return false;
    }

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
	std::vector<BOBall*>().swap(m_ballList);


	// Clear the blocks
	for (unsigned int i = 0; i < m_blockList.size(); i++)
	{
		m_blockList[i]->Shutdown();
		delete m_blockList[i];
	}

	m_blockList.clear();
	//std::vector<BOBlock*>().swap(m_blockList);

	// Call all the shutdowns
	m_mapLoader.Shutdown();
	m_background.Shutdown();
	m_blackHole.Shutdown();
	BOPublisher::Unsubscribe(&m_paddle);
	BOPublisher::Unsubscribe(this);
	m_paddle.Shutdown();
	m_keyManager.Shutdown();
    m_shockwave.Shutdown();
    m_slowTime.Shutdown();
}

void BOObjectManager::Update(double p_deltaTime)
{
    // First, check if we've catched all the keys
    if (m_keyManager.AllKeysCatched() && m_continue)
    {
        // In that case, start blowing all existing blocks up!
        PewPewPew();
    }

    // Update SlowTime before the objects
    m_slowTime.Update(p_deltaTime);
    m_blackHole.Update(p_deltaTime * 100);
	m_paddle.Update(p_deltaTime);
    m_shockwave.Update(p_deltaTime);
    m_shockwave.UpdateWave(p_deltaTime);

	// Update blocks
	for (unsigned int i = 0; i < m_blockList.size(); i++)
	{
        m_blockList[i]->Update(p_deltaTime);
	}

	// Update balls
	for (unsigned int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i]->Update(p_deltaTime, m_blackHole.GetBoundingSphere(), WonGame());

		if (m_ballList[i]->IsStuckToPad())
		{
            if (m_paddle.GetStickyState() && m_ballList[i]->IsSpawned())
            {
                //Calculate position of ball based on position of ball    
                m_ballList[i]->SetPosition(m_paddle.GetBallStuckPosition(m_ballList[i]->GetStuckAngle()));
				m_ballList[i]->SetDirection(float2(m_ballList[i]->GetPosition().x - m_blackHole.GetPosition().x, m_ballList[i]->GetPosition().y - m_blackHole.GetPosition().y));
            }
            else
            {
			    m_ballList[i]->SetPosition(m_paddle.GetBallSpawnPosition());
		    }
        }

		else	// Ball is NOT stuck to pad
		{
            // Check if the ball is newly launched
			BallNewlyLaunched(m_ballList[i]);
            
			BallBlockCollision(m_ballList[i]);            
			BallPadCollision(m_ballList[i]);

            if (!WonGame())
            {
		    CheckBallOutOfBounds(i);
            }

			CheckBallToBall(i);

			if (BallDied(m_ballList[i]))
			{
				m_ballList[i]->Shutdown();
				delete m_ballList[i];
				m_ballList.erase(m_ballList.begin() + i);
				i--;
				continue;
		    }
		
		    // Bounce on shield
            m_Shield.Update(p_deltaTime, *m_ballList[i]);

		    // Check collision between ball and keys
		    m_keyManager.Update(*m_ballList[i]);
	    }
	}

	for (unsigned int i = 0; i < m_ballList.size(); i++)
	{
		m_ballList[i]->SetBallCollidedWithBall(false);
	}

    // m_boss->Update(p_deltaTime);

	UpdateParticles(p_deltaTime);
}

void BOObjectManager::Draw()
{
	m_background.Draw();
    m_shockwave.DrawWave();
	m_blackHole.DrawRotating();
	m_keyManager.Draw();

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
        m_ballList[i]->DrawBallWithTail();
	}

    //m_boss->Draw();
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
			if (m_Shield.GetActive())
			{
				if (BOTechTreeEffects::PUEffects.stackableShield)
				{
					if (m_Shield.GetLifes() < BOTechTreeEffects::PUEffects.maxStackShield)
					{
						m_Shield.AddLife(1);
				}
			}
			}
			else
			{
			m_Shield.SetActive(true);
		}
		}
		break;
	case PUExtraBall:
		if (p_activated)
		{
			AddNewBall();
			int randomNr;
			randomNr = rand() % 100 + 1; // random nr from 1-100;
			if (randomNr <= (100 * BOTechTreeEffects::PUEffects.multiBallMultiplyChance))
			{
				AddNewBall();
		}
		}
		break;
	case PUFireBall:
		if (p_activated)
		{
			for (unsigned int i = 0; i < m_ballList.size(); i++)
			{
				m_ballList[i]->SetBallOnFire(true);
			}			
		}
		break;
    case PUSlowTime:
        if (p_activated)
        {
            m_slowTime.AddCharges(1);
        }
        break;
    case PUStickyPad:
        if (p_activated)
        {
            m_paddle.SetStickyState(true);
        }
        break;
	}
}

void BOObjectManager::Handle(InputMessages p_inputMessage)
{
    // Don't update objects if a key is pressed while paused
    if (BOGlobals::GAME_STATE == PAUSED)
    {
        return;
    }

	if (p_inputMessage.spacebarKey)
	{
		for (unsigned int i = 0; i < m_ballList.size(); i++)
		{
			if (m_ballList[i]->IsStuckToPad())
			{
			m_ballList[i]->SetStuckToPad(false);
				//m_ballList[i]->SetDirection(float2(m_ballList[i]->GetPosition().x - m_blackHole.GetPosition().x, m_ballList[i]->GetPosition().y - m_blackHole.GetPosition().y));
	}
}
}

    if (p_inputMessage.fKey && m_shockwave.Activate())
    {
        ActivateShockwave();
    }

	if (p_inputMessage.gKey)
	{
		ActivateMegaPad();
	}
    // Activate Slow time
    if (p_inputMessage.downArrow)
    {
        m_slowTime.Activate();
    }

    // Check for if the player wants to continue to the next level when all keys are catched
    if (p_inputMessage.enterKey && m_keyManager.AllKeysCatched())
    {
        m_continue = true;
    }
}

bool BOObjectManager::AddNewBall()
{
	BOBall* ball = new BOBall();

	float2 ballPos = m_paddle.GetBallSpawnPosition();
	int2 windowSize = BOGraphicInterface::GetWindowSize();

	// Set the direction outwards from the screen center
	float2 ballDir = float2(0, 0);

	if (!ball->Initialize(ballPos, int2(15,15), BOTextureManager::GetTexture(TEXBALL), 500.0f, ballDir, windowSize))
	{
		ThrowInitError("BOBall");
		return false;
	}
    
    ball->BouncedOnPad();

	m_ballList.push_back(ball);
	return true;
}

bool BOObjectManager::LostGame()
{
	return m_life == 0;
}

bool BOObjectManager::WonGame()
{
    bool didWin = m_keyManager.AllKeysCatched()
        && m_continue;
	return didWin;
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

bool BOObjectManager::LoadBlocksFromMap(int p_index)
{
	// Load block descriptions from a map file
	m_mapLoader.LoadMap(p_index);
	std::vector<Block> blockDescriptions = m_mapLoader.GetLoadedBlocks();
	
	float x = 0;
	float y = 0;
	bool result = false;

	// Hard coded constants for 40x40 hexagons
	static const float blockHeightDifference = 19; // The indentation of every other column
	static const int hexagonWidth = 32;
    static const int hexagonHeight = 37;
	static const int marginX = 40;
	static const int marginY = 50;

	for (unsigned int i = 0; i < blockDescriptions.size(); i++)
	{
		BOBlock* block;
		
		x = (hexagonWidth * blockDescriptions[i].m_position.x) + marginX;
		y = (hexagonHeight * blockDescriptions[i].m_position.y) + marginY;

		// Every other row shall be offset to tile the hexagons correctly.
		if ((int)blockDescriptions[i].m_position.x % 2 == 0) 
		{
			y += blockHeightDifference;
		}

		int score = blockDescriptions[i].m_worth;
		
		switch (blockDescriptions[i].m_type)
		{
			case(REGULAR) :
			{
				block = new BOBlock();

                if (blockDescriptions[i].m_powerUpType == PUNone)
                {
                    result = block->Initialize(float2(x, y), int2(46, 42), BOTextureManager::GetTexture(TEXHEXSTANDARD), PUNone, score);
                    block->AddGlow(float2(x, y), int2(46, 42), int2(46, 42), 0, 5, 0.12f, false, BOTextureManager::GetTexture(TEXGLOWSTANDARD));
                }

				else
				{
                    result = block->Initialize(float2(x, y), int2(46, 42), BOTextureManager::GetTexture(GetTexture(blockDescriptions[i].m_powerUpType)), blockDescriptions[i].m_powerUpType, score);
                    block->AddGlow(float2(x, y), int2(46, 42), int2(46, 42), 1, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWSTANDARD));
				}

				if (!result)
				{
					ThrowInitError("BOBlock");
					return false;
				}

				m_blockList.push_back(block);

				break;
			}

			case(DOUBLE) :
			{
				block = new BOBlockMultiTexture();
                result = block->InitializeAnimated(float2(x, y), int2(46, 42), int2(46, 42), 0, 2, 0, true, BOTextureManager::GetTexture(TEXHEXDOUBLE), 2, blockDescriptions[i].m_powerUpType, score);
                block->AddGlow(float2(x, y), int2(46, 42), int2(46, 42), 2, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWDOUBLE));
				if (!result)
				{
					ThrowInitError("BOBlockDouble");
					return false;
				}
				
				m_blockList.push_back(block);

				break;
			}

            case(ARMORED) :
            {
                block = new BOBlockMultiTexture();
                result = block->InitializeAnimated(float2(x, y), int2(46, 42), int2(46, 42), 0, 5, 0, true, BOTextureManager::GetTexture(TEXHEXARMORED), 5, blockDescriptions[i].m_powerUpType, score);
                block->AddGlow(float2(x, y), int2(46, 42), int2(46, 42), 3, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWARMORED));
                if (!result)
                {
                    ThrowInitError("BOBlockArmored");
                    return false;
                }

                m_blockList.push_back(block);

                break;
            }
	
			case(INDESTRUCTIBLE) :
			{
				block = new BOBlockIron();
				result = block->Initialize(float2(x, y), int2(46, 42), BOTextureManager::GetTexture(TEXHEXINDES), PUNone, score);
                block->AddGlow(float2(x, y), int2(46, 42), int2(46, 42), 4, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWINDES));
				if (!result)
				{
					ThrowInitError("BOBlockIron");
					return false;
				}

				m_blockList.push_back(block);

				break;
			}

			case(KEY) :
			{
                m_keyManager.AddKey(float2(x, y), int2(46, 42), 1.0f, BOTextureManager::GetTexture(TEXKEY));
				break;
			}

			default:
			{
				std::cout << "Unknown block type in BOObjectManager::LoadBlocksFromMap" << std::endl;
				return false;
				break;
			}
		}
	}


    m_boss = new BOTestBoss();
    m_boss->Initialize();

	return true;
}

void BOObjectManager::BallBlockCollision(BOBall* p_ball)
{
	for (unsigned int i = 0; i < m_blockList.size(); i++)
	{
		// Cheap collision test		
		bool result = BOPhysics::CheckCollisionSphereToSphere(p_ball->GetBoundingSphere(), m_blockList[i]->GetBoundingSphere());
		if (!result)
		{
			continue;
		}

		float2 normal;
		if (!BOPhysics::CheckCollisionSphereToHexagon(p_ball->GetBoundingSphere(), m_blockList[i]->GetBoundingHexagon(), normal))
		{
			continue;
		}
		
		// Make sure that we haven't already turned away from the hexagon
		float2 ballDir = p_ball->GetDirection();
		float2 newDir = BOPhysics::ReflectBallAroundNormal(p_ball->GetDirection(), normal);
		if (newDir.x == ballDir.x && newDir.y == ballDir.y)
		{
			// boll träffa från fel håll.
		}
		else
		{
			BOSoundManager::PlaySound(SOUND_POP);
			//std::cout << "Ball bounced on [" << i << "]" << std::endl;

			if (m_blockList[i]->Hit(p_ball->GetDamage()))
			{
				// Create explosion.
				m_particleSystem.BlockExplosion(m_blockList[i]->GetPosition());

				// Spawn powerup if there is one
				BOPowerUpManager::AddPowerUp(m_blockList[i]->GetPowerUp(), m_blockList[i]->GetPosition(), &m_paddle, m_blackHole.GetPosition());

				// Add score
				BOScore::AddScore(m_blockList[i]->GetScore());
                
                delete m_blockList[i];
				m_blockList.erase(m_blockList.begin() + i);

				if (p_ball->IsOnFire())
				{
					continue;
				}

			}

			p_ball->SetDirection(newDir);
			p_ball->BouncedOnHexagon();
			//p_ball->SetFuel(0.0f);
		}
	}

    float2 newDir;
    BOBlock* hitBlock = NULL;

    // Please leave this block of commented code!
    // It handles collision against boss blocks, but the boss is currently not feeling so well. :(
    //if (m_boss->CheckCollisions(p_ball, newDir, hitBlock))
    //{
    //    BOSoundManager::PlaySound(SOUND_POP);
    //    //std::cout << "Ball bounced on [" << i << "]" << std::endl;

    //    bool blockWasKilled = hitBlock->Hit(p_ball->GetDamage());
    //    if (blockWasKilled)
    //    {
    //        // Create explosion.
    //        m_particleSystem.BlockExplosion(hitBlock->GetPosition() + m_boss->GetPosition());

    //        // Spawn powerup if there is one
    //        BOPowerUpManager::AddPowerUp(hitBlock->GetPowerUp(), hitBlock->GetPosition(), &m_paddle, m_blackHole.GetPosition());

    //        // Add score
    //        BOScore::AddScore(hitBlock->GetScore());

    //        // Delete the block
    //        if (!m_boss->KillBlock(hitBlock))
    //        {
    //            std::cout << "Warning! Failed to kill a block" << std::endl;
    //        }
    //    }

    //    // This if probably looks a bit ugly, so I guess I'll have to explain the logic
    //    // If a block is killed while the ball is on fire, we don't want to change the direction
    //    // Thus we only change the direction if the above statement is false
    //    if (!(blockWasKilled && p_ball->IsOnFire()))
    //    {
    //        p_ball->SetDirection(newDir);
    //    }
    //    p_ball->BouncedOnHexagon();
    //    //p_ball->SetFuel(0.0f);
    //}

}

void BOObjectManager::BallPadCollision(BOBall* p_ball)
{
    float2 newDir;

    if (BOPhysics::BallBouncedOnPad(*p_ball, m_paddle, newDir))
	{
        p_ball->SetDirection(newDir);
        if (m_paddle.GetStickyState())
	    {
            p_ball->SetStuckToPad(true);
            float2 temp = { p_ball->GetPosition().x - m_blackHole.GetPosition().x, p_ball->GetPosition().y - m_blackHole.GetPosition().y };
            float tempAngle = BOPhysics::AngleBetweenDeg(float2( 0, -100 ), temp);
            p_ball->SetStuckAngle((float)(tempAngle - m_paddle.GetRotation()));

        }
		p_ball->BouncedOnPad();

		// Play sound for bounce on pad
		BOSoundManager::PlaySound(SOUND_BOUNCEONPAD);
	}
    /*
	float2 result = BOPhysics::BallPadCollision(p_ball->GetBoundingSphere(), p_ball->GetDirection(), m_paddle.GetBoundingSphere(), m_paddle.GetRotation() - 10.5, m_paddle.GetDegrees());
	if (!(result.x == 0 && result.y == 0))
	{

}
    */
}

bool BOObjectManager::BallDied(BOBall* p_ball)
{
	if (BOPhysics::CollisionRadiusRadius(p_ball->GetPosition(), p_ball->GetSize().x / 2.0f, m_blackHole.GetPosition(), m_blackHole.GetSize().x / 4.0f))
	{
		// Remove the current ball
		BOPublisher::Unsubscribe(p_ball); // Temporary for cheat with first ball
		
		// If no more ball in list then loose a life
		if (m_ballList.size() == 1)
		{
			m_life--;
			BOHUDManager::SetLives(m_life);
            m_paddle.SetStickyState(false);
			if (m_life > 0)
			{
				AddNewBall();
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void BOObjectManager::UpdateParticles(double p_deltaTime)
{
	// Balls should be responsible for calculating when they want to spawn particles
	// This should be added after m_ballList[i]->Update()
	// Increment time passed.
    m_SecondsPerParticle -= p_deltaTime * (double)BOPhysics::GetTimeScale();

	if (BALLDEBUGTRAIL == 1 && m_SecondsPerParticle < 0.0f)
	{
		for (unsigned int i = 0; i < m_ballList.size(); i++)
		{
			m_particleSystem.BallDebugTrail(m_ballList[i]->GetPosition());
		}

		m_SecondsPerParticle = 0.002f;
	}

	else if (m_SecondsPerParticle < 0.0f)
	{
		for (unsigned int i = 0; i < m_ballList.size(); i++)
		{
			if (m_ballList[i]->GetFuel() > 0.0f && !m_ballList[i]->IsStuckToPad())
			{
				m_particleSystem.BallTrail(m_ballList[i]->GetPosition());
			}
		}

		m_SecondsPerParticle = 0.025f;
	}

	m_particleSystem.Update(p_deltaTime);
}

void BOObjectManager::ActivateShockwave()
{
    double durationOfWave = 0.50;
    m_shockwave.BeginDrawingWave(durationOfWave);

    for (unsigned int i = 0; i < m_ballList.size(); i++)
    {
        m_ballList[i]->ActivateShockwave();
        m_particleSystem.Explosion(m_ballList[i]->GetPosition());
    }
}

void BOObjectManager::CheckBallToBall(int i)
{
	if (!m_ballList[i]->HasBallCollidedWithBall())
	{
		for (unsigned int j = 0; j < m_ballList.size(); j++)
		{
			if (i != j && !m_ballList[j]->HasBallCollidedWithBall())
			{
				if (BOPhysics::CheckCollisionSphereToSphere(m_ballList[i]->GetBoundingSphere(), m_ballList[j]->GetBoundingSphere()))
				{
					BOPhysics::BallToBallCollision(*m_ballList[i], *m_ballList[j]);
					m_ballList[j]->SetBallCollidedWithBall(true);
					if (BOTechTreeEffects::UtilityEffects.ballsCollideFuel)
					{
						m_ballList[j]->BouncedOnPad();
					}
				}
			}
		}
	}
}

void BOObjectManager::BallNewlyLaunched(BOBall* p_ball)
{
	if (p_ball->GetNewlyLaunched())
	{
		if (!m_paddle.GetStickyState() && BOTechTreeEffects::UtilityEffects.PUGiftEnabled)
	{
		int spawnPU, powerupType;
		PowerUpTypes PUType = PUNone;
		spawnPU = rand() % 10;
		powerupType = rand() % 7;
		if (spawnPU == 9)
		{
			switch (powerupType)
			{
			case 0:
			{
				PUType = PUExtraBall;
				break;
			}
			case 1:
			{
				PUType = PUBiggerPad;
				break;
			}
			case 2:
			{
				PUType = PUFireBall;
				break;
			}
			case 3:
			{
				PUType = PUShield;
				break;
			}
			case 4:
			{
				PUType = PUShockwave;
				break;
			}
			case 5:
			{
				PUType = PUSlowTime;
				break;
			}
			case 6:
			{
				PUType = PUStickyPad;
				break;
			}
			}
			BOPowerUpManager::AddPowerUp(PUType, float2(BOGraphicInterface::GetWindowSize().x / 2, 50), &m_paddle, m_blackHole.GetPosition());
		}
		p_ball->BouncedOnPad();
    }

		if (m_ballList.size() == 1)
		{
			for (int i = 0; i < BOTechTreeEffects::UtilityEffects.extraBallsFirstLaunch; i++)
			{
				AddNewBall();
			}
		}
    }	
}

void BOObjectManager::PewPewPew()
{
    if (m_blockList.size() > 0)
    {
        int l = rand() % (m_blockList.size() * 5);
        if (l < m_blockList.size())
        {
            m_particleSystem.BlockExplosion(m_blockList[l]->GetPosition());
            delete m_blockList[l];
            m_blockList.erase(m_blockList.begin() + l);
        }
	}
}

void BOObjectManager::ActivateMegaPad()
{
	m_paddle.ActivateMegaPad();
}

Textures BOObjectManager::GetTexture(PowerUpTypes p_type)
{
    switch (p_type)
    {
    case(PUBiggerPad) :
        {
            return TEXHEXPUBIGGERPAD;
        }

        case(PUShield) :
        {
            return TEXHEXPUSHIELD;
        }

        case(PUExtraBall) :
        {
            return TEXHEXPUADDBALL;
        }

        case(PUFireBall) :
        {
            return TEXHEXPUFIREBALL;
        }

        case(PUShockwave) :
        {
            return TEXHEXPUSHOCKWAVE;
        }

        case(PUStickyPad) :
        {
            return TEXHEXPUSTICKYPAD;
        }

        case(PUSlowTime) :
        {
            return TEXHEXPUSLOWTIME;
        }

        default:
        {
            std::cout << "Error in power up block texture resolver!" << std::endl;
        }
    }
}