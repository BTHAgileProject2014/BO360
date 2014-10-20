#ifndef BOMAPLOADER_H_
#define BOMAPLOADER_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "BOBlock.h"
#include "BOBlockMultiTexture.h"
#include "BOBlockIron.h"

class BOMapLoader : public BOComponent
{
public:
	BOMapLoader();
	~BOMapLoader();

	bool Initialize();
	bool LoadMap(int p_index);
    bool LoadMapFromFile(std::string p_filename);
	int2 GetMapSize();
	std::vector<Block> GetLoadedBlocks();
    std::vector<BOBlock*> GetLoadedBOBlocks();

private:
	int2 m_mapSize;
	std::vector<Block> m_blocks;

    void DetermineAction(int p_type, int p_powerUp, float x, float y);
};
#endif