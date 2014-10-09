#include "BOTechTreeEffects.h"

TechTreeBallEffects BOTechTreeEffects::BallEffects;
TechTreeLevelEffects BOTechTreeEffects::LevelEffects;
TechTreePaddleEffects BOTechTreeEffects::PaddleEffects;
TechTreePUEffects BOTechTreeEffects::PUEffects;
TechTreeUtilityEffects BOTechTreeEffects::UtilityEffects;

BOTechTreeEffects::BOTechTreeEffects()
{
}


BOTechTreeEffects::~BOTechTreeEffects()
{
}

bool BOTechTreeEffects::Initialize()
{
    BallEffects = TechTreeBallEffects();
    LevelEffects = TechTreeLevelEffects();
    PaddleEffects = TechTreePaddleEffects();
    PUEffects = TechTreePUEffects();
    UtilityEffects = TechTreeUtilityEffects();
    return true;
}

void BOTechTreeEffects::Shutdown()
{

}