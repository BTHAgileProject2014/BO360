#include "BOBossSegment.h"


BOBossSegment::BOBossSegment()
{
}


BOBossSegment::~BOBossSegment()
{
}

bool BOBossSegment::Initialize()
{
    m_position = float2(0, 0);
    return true;
}

bool BOBossSegment::InitializeWithBlocklist(std::vector<BOBlock*> p_blocks)
{
    Initialize();
    return m_blockManager.Initialize(p_blocks);
}

void BOBossSegment::Update(double p_dt)
{
    m_blockManager.Update(p_dt);
}

void BOBossSegment::SetPosition(const float2 p_position)
{
    m_position = p_position;
}
float2 BOBossSegment::GetPosition() const
{
    return m_position;
}

void BOBossSegment::Draw()
{
    BOGraphicInterface::Offset(m_position);
    m_blockManager.Draw();
    BOGraphicInterface::Offset(-m_position);
}

void BOBossSegment::Draw(float2 p_offset)
{
    BOGraphicInterface::Offset(m_position + p_offset);
    m_blockManager.Draw();
    BOGraphicInterface::Offset(-(m_position + p_offset));
}

void BOBossSegment::Shutdown()
{
    m_blockManager.Shutdown();
}

bool BOBossSegment::CheckCollisions(const BOBall* const p_ball, const float2 p_offset, float2& p_newDirOut, BOBlock*& p_hitBlockOut)
{
    return m_blockManager.CheckCollisions(p_ball, m_position + p_offset, p_newDirOut, p_hitBlockOut);
}

bool BOBossSegment::HideBlock(BOBlock* p_block)
{
    return m_blockManager.HideBlock(p_block);
}

bool BOBossSegment::KillBlock(BOBlock* p_block)
{
    return m_blockManager.RemoveBlock(p_block);
}

bool BOBossSegment::LoadSegmentFromFile(std::string p_filename)
{
    BOMapLoader loader;
    loader.Initialize();
    if (!loader.LoadMapFromFile(p_filename))
    {
        return false;
    }
    std::vector<Block> blocks = loader.GetLoadedBlocks();
    std::vector<BOBlock*> boBlocks = loader.GetLoadedBOBlocks();
    return m_blockManager.Initialize(boBlocks);
}

BOBlockManager& BOBossSegment::GetBlockManagerRef()
{
    return m_blockManager;
}

bool BOBossSegment::IsEmpty() const
{
    return m_blockManager.IsEmpty();
}