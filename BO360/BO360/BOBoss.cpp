#include "BOBoss.h"


BOBoss::BOBoss()
{

}


BOBoss::~BOBoss()
{
}

bool BOBoss::Initialize()
{
    m_position = float2(0.0f, 250.0f);
    return true;
}

void BOBoss::Shutdown()
{
    m_blockManager.Shutdown();
}

void BOBoss::Draw()
{
    float2 negativePos = float2(-m_position.x, -m_position.y);
    BOGraphicInterface::Offset(m_position);
    m_blockManager.Draw();
    BOGraphicInterface::Offset(negativePos);
}

void BOBoss::Update(double p_dt)
{
    m_blockManager.Update(p_dt);
}


bool BOBoss::CheckCollisions(BOBall*const p_ball, float2& p_newDirOut, BOBlock*& p_hitBlockOut)
{
    return m_blockManager.CheckCollisions(p_ball, m_position, p_newDirOut, p_hitBlockOut);
}

bool BOBoss::KillBlock(BOBlock* p_block)
{
    return m_blockManager.RemoveBlock(p_block);
}

float2 BOBoss::GetPosition() const
{
    return m_position;
}