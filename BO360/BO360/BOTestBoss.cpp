#include "BOTestBoss.h"


BOTestBoss::BOTestBoss()
{
}


BOTestBoss::~BOTestBoss()
{
}

bool BOTestBoss::Initialize()
{
    float2 pos = float2(20, 20);

    BOBlock* block = new BOBlock(); 
    block->InitializeAnimated(pos, int2(46, 42), int2(46, 42), 0, 5, 0, true, BOTextureManager::GetTexture(TEXHEXARMORED), 5, PUNone, 10);
    block->AddGlow(pos, int2(46, 42), int2(46, 42), 3, 5, 0.12, false, BOTextureManager::GetTexture(TEXGLOWARMORED));
    return true;
}