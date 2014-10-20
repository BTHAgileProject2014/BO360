#include "BOBoss.h"


BOBoss::BOBoss()
{
    m_latestHitSegment = &m_mainSegment;
}


BOBoss::~BOBoss()
{
}

bool BOBoss::Initialize()
{
    m_position = float2(0.0f, 0.0f);
    return true;
}

void BOBoss::Shutdown()
{
    m_mainSegment.Shutdown();
}

void BOBoss::Draw()
{
   BOGraphicInterface::Offset(m_position);
    m_mainSegment.Draw();
   BOGraphicInterface::Offset(-m_position);
}

void BOBoss::Update(double p_dt)
{
    m_mainSegment.Update(p_dt);
}


bool BOBoss::CheckCollisions(BOBall*const p_ball, float2& p_newDirOut, BOBlock*& p_hitBlockOut)
{
    bool result = m_mainSegment.CheckCollisions(p_ball, m_position, p_newDirOut, p_hitBlockOut);
    if (result)
    {
        m_latestHitSegment = &m_mainSegment;
    }
    return result;
}

bool BOBoss::KillBlock(BOBlock* p_block)
{
    return m_mainSegment.KillBlock(p_block);
}

float2 BOBoss::GetPosition() const
{
    return m_position;
}

float2 BOBoss::GetLatestHitOffset() const
{
    float2 latestHitPos = m_latestHitSegment->GetPosition();
    return latestHitPos + m_position;
}

bool BOBoss::IsDead() const
{
    // Bosses should override this to determine their win condition
    return false;
}