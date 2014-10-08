#include "BOTechTreeEffects.h"


BOTechTreeEffects::BOTechTreeEffects()
{
}


BOTechTreeEffects::~BOTechTreeEffects()
{
}

bool BOTechTreeEffects::Initialize()
{
    m_ballEffects = TechTreeBallEffects();
    m_levelEffects = TechTreeLevelEffects();
    m_paddleEffects = TechTreePaddleEffects();
    m_PUEffects = TechTreePUEffects();
    m_utilityEffects = TechTreeUtilityEffects();
    return true;
}

void BOTechTreeEffects::Shutdown()
{

}

TechTreeBallEffects BOTechTreeEffects::GetBallEffects()const
{
    return m_ballEffects;
}

TechTreeLevelEffects BOTechTreeEffects::GetLevelEffects()const
{
    return m_levelEffects;
}

TechTreePaddleEffects BOTechTreeEffects::GetPaddleEffects()const
{
    return m_paddleEffects;
}

TechTreePUEffects BOTechTreeEffects::GetPUEffects()const
{
    return m_PUEffects;
}

TechTreeUtilityEffects BOTechTreeEffects::GetUtilityEffects()const
{
    return m_utilityEffects;
}