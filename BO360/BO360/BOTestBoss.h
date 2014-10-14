#pragma once
#include "BOBoss.h"
#include "BOUtility.h"
#include "BOBlockMultiTexture.h"
#include "BOBlockIron.h"

class BOTestBoss :
    public BOBoss
{
public:
    BOTestBoss();
    ~BOTestBoss();
    bool Initialize();
    void Update(double p_dt);
    bool KillBlock(BOBlock* p_block);
    bool CheckCollisions(BOBall* const p_ball, float2& p_newDirOut, BOBlock*& p_hitBlockOut);
    void Draw();
private:
    void BuildBoss();

    float2 m_direction;
    double m_deg;
    int m_speed;
   
    BOBlock* m_specialBlock;
    float2 m_specialBlockOrigin;
};

