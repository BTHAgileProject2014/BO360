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

bool BOMapLoader::LoadMap(std::string p_fileName)
{
	int l_type;
	std::string l_fileName = "Maps/";
	l_fileName.append(p_fileName);

	// Open and read map file.
	std::ifstream l_file;
	l_file.open(l_fileName);
	
	// Check to see if we found the file.
	if (!l_file.is_open())
	{
		std::cout << "Failed to load map file. Check if missing or corrupted" << std::endl;
		return false;
	}

	// Read map size data.
	if (l_file.good())
	{
		l_file >> m_mapSize.x >> m_mapSize.y;
	}

	// Read grid until last line.
	for (int y = 0; y < m_mapSize.y - 1; y++)
	{
		for (int x = 0; x < m_mapSize.x; x++)
		{
			l_file >> l_type;

			DetermineAction(l_type, (float)x, (float)y);
		}
	}

	for (int x = 0; x < m_mapSize.x; x++)
	{
		if (x%2 != 0)
		{
			l_file >> l_type;

			DetermineAction(l_type, (float)x, (float)(m_mapSize.y - 1));
		}
	}

	l_file.close();

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

void BOMapLoader::DetermineAction(int p_type, float x, float y)
{
	// The tile is empty, do nothing.
	if (!p_type == 0)
	{
		// Add blocks at 1 tiles. 
		if (p_type == 1)
		{
			Block l_block;

			l_block.m_position = float2(x, y);
			l_block.m_type = REGULAR;
			l_block.m_worth = 10;

			m_blocks.push_back(l_block);
		}

		// Add dubble HP blocks at 2 tiles. 
		if (p_type == 2)
		{
			Block l_block;

			l_block.m_position = float2(x, y);
			l_block.m_type = DUBBLEHP;
			l_block.m_worth = 30;

			m_blocks.push_back(l_block);
		}

		// Add indistructible blocks at 9 tiles. 
		if (p_type == 9)
		{
			Block l_block;

			l_block.m_position = float2(x, y);
			l_block.m_type = INDESTRUCTIBLE;
			l_block.m_worth = 30;

			m_blocks.push_back(l_block);
		}
	}
}