#include "BOBlockManager.h"


BOBlockManager::BOBlockManager()
{
}


BOBlockManager::~BOBlockManager()
{
}

bool BOBlockManager::Initialize(std::vector<BOBlock*> p_blockList)
{
    m_blockList.clear();
    for (unsigned int i = 0; i < p_blockList.size(); i++)
    {
        m_blockList.push_back(p_blockList[i]);
    }
    return true;
}

void BOBlockManager::Shutdown()
{
    for (unsigned int i = 0; i < m_blockList.size(); i++)
    {
        m_blockList[i]->Shutdown();
        delete m_blockList[i];
    }
    m_blockList.clear();
}

void BOBlockManager::AddBlock(BOBlock* p_blockPtr)
{
    m_blockList.push_back(p_blockPtr);
}

void BOBlockManager::Update(float p_dt)
{
    for (unsigned int i = 0; i < m_blockList.size(); i++)
    {
        m_blockList[i]->Update(p_dt);
    }
}

bool BOBlockManager::CheckCollisionAgainstBlock(const BOBall* const p_ball, const float2 p_offset, const BOBlock* const p_block, float2& p_newDirOut)
{
    // Get bounds for block and ball
    box blockBounds = p_block->GetBoundingBox();
    box ballBounds = p_ball->GetBoundingBox();

    // Move to "boss space"
    ballBounds = box(ballBounds.pos - p_offset, ballBounds.size);

    // Cheap collision test		
    bool result = BOPhysics::CheckCollisionBoxToBox(ballBounds, blockBounds);
    if (!result)
    {
        return false;
    }

    // Normal collision test
    sphere ballSphere = p_ball->GetBoundingSphere();
    ballSphere.pos = ballSphere.pos - p_offset;
    float2 normal;
    if (!BOPhysics::CheckCollisionSphereToHexagon(ballSphere, p_block->GetBoundingHexagon(), normal))
    {
        return false;
    }

    // Make sure that we haven't already turned away from the hexagon
    float2 ballDir = p_ball->GetDirection();
    float2 newDir = BOPhysics::ReflectBallAroundNormal(p_ball->GetDirection(), normal);
    if (newDir.x != ballDir.x || newDir.y != ballDir.y)
    {
        p_newDirOut = newDir;
        return true;
    }
    return false;
}

bool BOBlockManager::CheckCollisions(const BOBall* const p_ball, const float2 p_offset, float2& p_newDirOut, BOBlock*& p_hitBlockOut)
{
    // Loop over all blocks
    for (unsigned int i = 0; i < m_blockList.size(); i++)
    {
        if (!m_blockList[i]->GetDead() && CheckCollisionAgainstBlock(p_ball, p_offset, m_blockList[i], p_newDirOut))
        {
            p_hitBlockOut = m_blockList[i];
            return true;
        }
    }
    return false;
}

void BOBlockManager::Draw()
{
    for (unsigned int i = 0; i < m_blockList.size(); i++)
    {
        m_blockList[i]->Draw();
    }
}

bool BOBlockManager::RemoveBlock(BOBlock* p_block)
{
    bool result = false;
    for (unsigned int i = 0; i < m_blockList.size(); i++)
    {
        if (m_blockList[i] == p_block)
        {
            m_blockList[i]->Shutdown();
            delete m_blockList[i];
            m_blockList.erase(m_blockList.begin() + i);
            i--;
            result = true;
        }
    }
    return result;
}

bool BOBlockManager::HideBlock(BOBlock* p_block)
{
    bool result = false;
    for (unsigned int i = 0; i < m_blockList.size(); i++)
    {
        if (m_blockList[i] == p_block)
        {
            m_blockList[i]->SetDead();
            result = true;
            break;
        }
    }
    return result;
}

std::vector<BOBlock*> BOBlockManager::GetUnderlyingBlockList()
{
    return m_blockList;
}

bool BOBlockManager::IsEmpty() const
{
    return m_blockList.size() < 1;
}