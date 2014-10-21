#include "BOMapLoader.h"

BOMapLoader::BOMapLoader()
{

}

BOMapLoader::~BOMapLoader()
{

}

bool BOMapLoader::Initialize()
{
	m_mapSize = int2(0, 0);
	m_blocks.clear();

	return true;
}


bool BOMapLoader::LoadMapFromFile(std::string p_filename)
{

    int type;
    int powerUp;

    // Open and read map file.
    std::ifstream file;
    file.open(p_filename);

    // Check to see if we found the file.
    if (!file.is_open())
    {
        std::cout << "Failed to load map file. Check if missing or corrupted (" << p_filename << ")" << std::endl;
        return false;
    }

    // Read map size data.
    if (file.good())
    {
        file >> m_mapSize.x >> m_mapSize.y;
    }

    // Read grid until last line.
    for (int y = 0; y < m_mapSize.y - 1; y++)
    {
        for (int x = 0; x < m_mapSize.x; x++)
        {
            file >> type;
            file >> powerUp;

            DetermineAction(type, powerUp, (float)x, (float)y);
        }
    }

    for (int x = 0; x < m_mapSize.x; x++)
    {
        if (x % 2 != 0)
        {
            file >> type;
            file >> powerUp;

            DetermineAction(type, powerUp, (float)x, (float)(m_mapSize.y - 1));
        }
    }

    file.close();

    return true;
}

bool BOMapLoader::LoadMap(int p_index)
{
	int type;
    int powerUp;

	std::string fileName = "Maps/";
	switch (p_index)
	{
	case(0) :
	{
		fileName.append("map1.bom");
		break;
	}
	case(1) :
	{
		fileName.append("map2.bom");
		break;
	}
    case(2) :
    {
        fileName.append("map3.bom");
        break;
    }
    case(3) :
    {
        fileName.append("map4.bom");
        break;
    }
    case(4) :
    {
        fileName.append("map5.bom");
        break;
    }
    case(5) :
    {
        fileName.append("map6.bom");
        break;
    }
    case(6) :
    {
        fileName.append("map7.bom");
        break;
    }
    case(7) :
    {
        fileName.append("map8.bom");
        break;
    }
    case(8) :
    {
        fileName.append("map9.bom");
        break;
    }
    case(9) :
    {
        fileName.append("map10.bom");
        break;
    }
    case(10) :
    {
        fileName.append("map11.bom");
        break;
    }
    case(11) :
    {
        fileName.append("map12.bom");
        break;
    }
    case(12) :
    {
        fileName.append("map13.bom");
        break;
    }
    case(13) :
    {
        fileName.append("map14.bom");
        break;
    }
    case(14) :
    {
        fileName.append("map15.bom");
        break;
    }
    case(15) :
    {
        fileName.append("Empty.bom");
        break;
    }
	default:
	{
		fileName.append("Demo.bom");
		break;
	}
	}

	// Open and read map file.
	std::ifstream file;
	file.open(fileName);
	
	// Check to see if we found the file.
	if (!file.is_open())
	{
		std::cout << "Failed to load map file. Check if missing or corrupted" << std::endl;
		return false;
	}

	// Read map size data.
	if (file.good())
	{
		file >> m_mapSize.x >> m_mapSize.y;
	}

	// Read grid until last line.
	for (int y = 0; y < m_mapSize.y - 1; y++)
	{
		for (int x = 0; x < m_mapSize.x; x++)
		{
			file >> type;
            file >> powerUp;

            DetermineAction(type, powerUp, (float)x, (float)y);
		}
	}

	for (int x = 0; x < m_mapSize.x; x++)
	{
		if (x%2 != 0)
		{
			file >> type;
            file >> powerUp;

			DetermineAction(type, powerUp, (float)x, (float)(m_mapSize.y - 1));
		}
	}

	file.close();

	return true;
}

std::vector<Block> BOMapLoader::GetLoadedBlocks()
{
	return m_blocks;
}

int2 BOMapLoader::GetMapSize()
{
	return m_mapSize;
}

void BOMapLoader::DetermineAction(int p_type, int p_powerUp, float x, float y)
{
	// The tile is empty, do nothing.
	if (!p_type == 0)
	{
		// Add blocks at 1 tiles. 
		if (p_type == 1)
		{
			Block block;

			block.m_position = float2(x, y);
			block.m_type = REGULAR;
            block.m_powerUpType = (PowerUpTypes)p_powerUp;
			block.m_worth = 10;

			m_blocks.push_back(block);
		}

		// Add double HP blocks at 2 tiles. 
		if (p_type == 2)
		{
			Block block;

			block.m_position = float2(x, y);
			block.m_type = DOUBLE;
            block.m_powerUpType = (PowerUpTypes)p_powerUp;
			block.m_worth = 20;

			m_blocks.push_back(block);
		}

        // Add armored blocks at 3 tiles. 
        if (p_type == 3)
        {
            Block block;

            block.m_position = float2(x, y);
            block.m_type = ARMORED;
            block.m_powerUpType = (PowerUpTypes)p_powerUp;
            block.m_worth = 50;

            m_blocks.push_back(block);
        }

		// Add keys at 8 tiles. 
		if (p_type == 8)
		{
			Block block;

			block.m_position = float2(x, y);
			block.m_type = KEY;
            block.m_powerUpType = PUNone;
			block.m_worth = 10;

			m_blocks.push_back(block);
		}

		// Add indistructible blocks at 9 tiles. 
		if (p_type == 9)
		{
			Block block;

			block.m_position = float2(x, y);
			block.m_type = INDESTRUCTIBLE;
            block.m_powerUpType = PUNone;
			block.m_worth = 30;

			m_blocks.push_back(block);
		}
	}
}

std::vector<BOBlock*> BOMapLoader::GetLoadedBOBlocks()
{
    // Load block descriptions from a map file
	std::vector<Block> blockDescriptions = GetLoadedBlocks();
    std::vector<BOBlock*> boBlocks;

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
                    result = block->Initialize(float2(x, y), int2(46, 42), BOTextureManager::GetTexture(TEXHEXPOWERUP), blockDescriptions[i].m_powerUpType, score);
                    block->AddGlow(float2(x, y), int2(46, 42), int2(46, 42), 1, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWSTANDARD));
				}

				if (!result)
				{
					ThrowInitError("BOBlock");
                    break;
				}
                boBlocks.push_back(block);

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
				}
				
                boBlocks.push_back(block);

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
                    break;
                }
                boBlocks.push_back(block);
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
                    break;
				}
                boBlocks.push_back(block);

				break;
			}

			case(KEY) :
			{
                // We only handle blocks from here
				break;
			}

			default:
			{
				std::cout << "Unknown block type in BOObjectManager::LoadBlocksFromMap" << std::endl;
				break;
			}
		}
	}
    return boBlocks;
}