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

bool BOMapLoader::LoadMap(int p_index)
{
	int type;
    int powerUp;

	std::string fileName = "Maps/";
	switch (p_index)
	{
	case(0) :
	{
		fileName.append("NewFormatTest.bom");
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