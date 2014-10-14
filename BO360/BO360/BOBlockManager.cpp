#include "BOBlockManager.h"


BOBlockManager::BOBlockManager()
{
}


BOBlockManager::~BOBlockManager()
{
}

bool BOBlockManager::Initialize(std::vector<BOBlock*> p_blockList)
{
    for (int i = 0; i < p_blockList.size(); i++)
    {
        m_blockList.push_back(p_blockList[i]);
    }
    return true;
}

void BOBlockManager::Shutdown()
{
    for (int i = 0; i < m_blockList.size(); i++)
    {
        m_blockList[i]->Shutdown();
        delete m_blockList[i];
    }
    m_blockList.clear();
}