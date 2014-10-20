#include "BOBossInvader.h"

BOBossInvader::BOBossInvader()
{
}


BOBossInvader::~BOBossInvader()
{
}


void BOBossInvader::BuildBoss()
{
    float blockHeightDifference = 19; // The indentation of every other column
    int hexagonWidth = 32;
    int hexagonHeight = 37;

    m_mainSegment.LoadSegmentFromFile("Bosses/testboss.bom");
    std::vector<BOBlock*> underlyingBlockList = m_mainSegment.GetBlockManagerRef().GetUnderlyingBlockList();
    for (unsigned int i = 0; i < underlyingBlockList.size(); i++)
    {
        if (underlyingBlockList[i]->GetHp() == 2)
        {
            m_keyBlocks.push_back(underlyingBlockList[i]);
        }
    }

    BuildDrones();
}

bool BOBossInvader::Initialize()
{
    bool result;
    m_liveDrones = 6;
    BuildBoss();
    m_direction = float2(1.0f, 0.0f);
    m_speed = 100;
    m_deg = 0.0;
    result =  BOBoss::Initialize();
    m_position = float2(450, 0);
    m_removedKeyBlocks = 0;
    return result;
}
void BOBossInvader::Update(double p_dt)
{
    m_deg += p_dt;

    // Only move, etc. if we are alive
    if (!IsDead())
    {
        // Change direction at edges
        if (m_position.x < 150)
        {
            m_direction.x = 1;
        }
        else if (m_position.x > BOGraphicInterface::GetWindowSize().x - 450)
        {
            m_direction.x = -1;
        }

        // Move
        m_position.y = -40 + 10 * sinf((float)m_deg);


        // Update blocks to respawn
        for (unsigned int i = 0; i < m_blocksToRespawn.size(); i++)
        {
            m_blocksToRespawn[i].timeLeft -= p_dt;
            if (m_blocksToRespawn[i].timeLeft < 0)
            {
                m_blocksToRespawn[i].block->Revive();
                m_blocksToRespawn.erase(m_blocksToRespawn.begin() + i);
                i--;
            }
        }
    }
    
    UpdateDrones(p_dt);
    BOBoss::Update(p_dt);
}

bool BOBossInvader::KillBlockInSegment(BOBlock* p_block, BOBossSegment* p_segment)
{
    bool result = false;
    // This boss does not actually kill blocks, it just hides them to be able to regenerate

    result = p_segment->HideBlock(p_block);

    return result;
}

bool BOBossInvader::KillBlock(BOBlock* p_block)
{
    bool result = KillBlockInSegment(p_block, &m_mainSegment);

    if (result)
    {
        if (BlockIsKeyBlock(p_block))
        {
            m_removedKeyBlocks++;
        }
        else if (m_liveDrones > 0)
        {
            // If the block was not a key block and we haven't cleared the drones
            // Add the block to the respawn queue
            m_blocksToRespawn.push_back(BlockTimer(p_block, 5.0));
            m_direction = m_direction * -1;
        }
    }

    for (unsigned int i = 0; i < m_drones.size(); i++)
    {
        result = KillBlockInSegment(p_block, &m_drones[i]);
        if (result)
        {
            std::vector<BOBlock*> blockList = m_drones[i].GetBlockManagerRef().GetUnderlyingBlockList();
            if (blockList.size() > 0)
            {
                if (blockList[0]->GetDead())
                {
                    m_liveDrones--;
                    
                    // If this was the last drone, clear the respawn queue
                    if (m_liveDrones < 1)
                    {
                        m_blocksToRespawn.clear();
                    }
                }   
            }
            break;
        }
    }

    return result;
}

void BOBossInvader::Draw()
{

    BOGraphicInterface::Offset(m_position);

    for (unsigned int i = 0; i < m_drones.size(); i++)
    {
        m_drones[i].Draw();
    }

    BOGraphicInterface::Offset(-m_position);
    BOBoss::Draw();
}
bool BOBossInvader::CheckCollisions(BOBall* const p_ball, float2& p_newDirOut, BOBlock*& p_hitBlockOut)
{
    if (BOBoss::CheckCollisions(p_ball, p_newDirOut, p_hitBlockOut))
    {
        return true;
    }

    for (unsigned int i = 0; i < m_drones.size(); i++)
    {
        if (m_drones[i].CheckCollisions(p_ball, m_position, p_newDirOut, p_hitBlockOut))
        {
            m_latestHitSegment = &m_drones[i];
            return true;
        }
    }

    return false;
}

void BOBossInvader::BuildDrones()
{
    for (int i = 0; i < m_liveDrones; i++)
    {
        std::vector<BOBlock*> droneBlocks;
        BOBlock* core = new BOBlock();
        core->Initialize(float2(0, 0), int2(46, 42), BOTextureManager::GetTexture(TEXHEXSTANDARD), PUNone, 0);
        core->AddGlow(float2(0, 0), int2(46, 42), int2(46, 42), 3, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWINDES));
        droneBlocks.push_back(core);
        BOBossSegment segment;
        segment.InitializeWithBlocklist(droneBlocks);
        float2 segmentPos = float2((float)i * 100, 500);
        segment.SetPosition(segmentPos);
        m_drones.push_back(segment);
        droneBlocks.clear();
    }
}

void BOBossInvader::UpdateDrones(double p_dt)
{
    int droneSize = m_drones.size();
    if (IsDead())
    {
        // If the boss is dead, drones should not rotate, just update animation
        for (int i = 0; i < droneSize; i++)
        {
            m_drones[i].Update(p_dt);
        }
    }
    else
    {
        float2 basePos = float2((float)BOGraphicInterface::GetWindowSize().x / 2, (float)BOGraphicInterface::GetWindowSize().y / 2);
        double offset = (2 * PI) / droneSize;
        for (int i = 0; i < droneSize; i++)
        {
            double myRotation = (i * offset) + m_deg / 10;
            float2 pos = basePos + float2(500 * cosf((float)myRotation), 400 * sinf((float)myRotation)) - m_position;
            m_drones[i].SetPosition(pos);
            m_drones[i].Update(p_dt);
        }
    }
}

bool BOBossInvader::BlockIsKeyBlock(BOBlock* p_block)
{
    bool result = false;
    for (unsigned int i = 0; i < m_keyBlocks.size(); i++)
    {
        if (m_keyBlocks[i] == p_block)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool BOBossInvader::IsDead() const
{
    for (unsigned int i = 0; i < m_keyBlocks.size(); i++)
    {
        // If any live key blocks are found, return false
        if (!m_keyBlocks[i]->GetDead())
        {
            return false;
        }
    }
    // If no live key blocks were found, return true
    return true;
}