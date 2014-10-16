#include "BOTestBoss.h"

BOTestBoss::BOTestBoss()
{
}


BOTestBoss::~BOTestBoss()
{
}


void BOTestBoss::BuildBoss()
{
    float blockHeightDifference = 19; // The indentation of every other column
    int hexagonWidth = 32;
    int hexagonHeight = 37;

    float2 pos = float2(0, 0);
    BOBlock* block;
    for (int i = 0; i < 5; i++) // row of 6
    {
        bool indent = (i % 2 == 0);
        if (indent)
        {
            pos.y += blockHeightDifference;
        }
        block = new BOBlockMultiTexture();
        block->InitializeAnimated(pos, int2(46, 42), int2(46, 42), 0, 5, 0, true, BOTextureManager::GetTexture(TEXHEXARMORED), 5, PUNone, 10);
        block->AddGlow(pos, int2(46, 42), int2(46, 42), 3, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWARMORED));
        m_blockManager.AddBlock(block);
        pos.x += hexagonWidth;
        if (indent)
        {
            pos.y -= blockHeightDifference;
        }
    }

    pos.x = hexagonWidth;
    pos.y += hexagonHeight  + blockHeightDifference;

    for (int i = 0; i < 3; i++) // row of 6
    {
        bool indent = (i % 2 == 0);
        if (indent)
        {
            pos.y -= blockHeightDifference;
        }
        block = new BOBlockMultiTexture();
        block->InitializeAnimated(pos, int2(46, 42), int2(46, 42), 0, 2, 0, true, BOTextureManager::GetTexture(TEXHEXDOUBLE), 2, PUNone, 10);
        block->AddGlow(pos, int2(46, 42), int2(46, 42), 3, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWDOUBLE));
        m_blockManager.AddBlock(block);
        pos.x += hexagonWidth;
        if (indent)
        {
            pos.y += blockHeightDifference;
        }
    }

    m_specialBlockOrigin = float2(hexagonWidth * 2, 120);
    m_specialBlock = new BOBlockIron();
    m_specialBlock->Initialize(m_specialBlockOrigin, int2(46, 42), BOTextureManager::GetTexture(TEXHEXINDES), PUNone, 0);
    m_specialBlock->AddGlow(m_specialBlockOrigin, int2(46, 42), int2(46, 42), 3, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWINDES));
}

bool BOTestBoss::Initialize()
{
    BuildBoss();
    m_direction = float2(1.0f, 0.0f);
    m_speed = 100;
    m_deg = 0.0;
    return BOBoss::Initialize();
}
void BOTestBoss::Update(double p_dt)
{
    m_deg += p_dt;

    // Change direction at edges
    if (m_position.x < 50)
    {
        m_direction.x = 1;
    }
    else if (m_position.x > BOGraphicInterface::GetWindowSize().x - 150)
    {
        m_direction.x = -1;
    }

    // Move
    m_position.x = m_position.x + m_direction.x * p_dt * m_speed;
    m_position.y = 150 + 100 * sin(m_deg);

    // Move special block
    float2 specialPos = m_specialBlockOrigin + float2(10 * sin(m_deg), 10 * cos(m_deg));
    m_specialBlock->SetPosition(specialPos);
    
    // Update for animation
    m_specialBlock->Update(p_dt);

    BOBoss::Update(p_dt);
}

bool BOTestBoss::KillBlock(BOBlock* p_block)
{
    bool result = m_blockManager.RemoveBlock(p_block);
    if (!result && p_block == m_specialBlock)
    {
        result = false;
    }

    if (result)
    {
        m_direction = m_direction * -1;
    }
    return result;
}

void BOTestBoss::Draw()
{
    BOBoss::Draw();

    BOGraphicInterface::Offset(m_position);
    m_specialBlock->Draw();
    BOGraphicInterface::Offset(float2(-m_position.x, -m_position.y));
}
bool BOTestBoss::CheckCollisions(BOBall* const p_ball, float2& p_newDirOut, BOBlock*& p_hitBlockOut)
{
    if (BOBoss::CheckCollisions(p_ball, p_newDirOut, p_hitBlockOut))
    {
        return true;
    }
    if (m_blockManager.CheckCollisionAgainstBlock(p_ball, m_position, m_specialBlock, p_newDirOut))
    {
        p_hitBlockOut = m_specialBlock;
        return true;
    }
    return false;
    
}