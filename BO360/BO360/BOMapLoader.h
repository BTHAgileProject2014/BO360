#ifndef BOMAPLOADER_H_
#define BOMAPLOADER_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "BOBlock.h"

class BOMapLoader : public BOComponent
{
public:
	BOMapLoader();
	~BOMapLoader();

	bool Initialize();
	bool LoadMap(std::string p_fileName);
	int2 GetMapSize();
	std::vector<float2> GetBlockPositions();

private:
	int2 m_mapSize;
	std::vector<float2> m_blockPositions;

	void DetermineAction(int p_type, float x, float y);
};
#endif