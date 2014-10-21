#pragma once
#include "BOBoss.h"
#include "BOUtility.h"
#include "BOBlockMultiTexture.h"
#include "BOBlockIron.h"

class BOBossInvader :
    public BOBoss
{
private:
    struct BlockTimer
    {
        BOBlock* block;
        double timeLeft;
        BlockTimer() {}
        BlockTimer(BOBlock* p_block, double p_timeLeft) : block(p_block), timeLeft(p_timeLeft) {}
    };

public:
    BOBossInvader();
    ~BOBossInvader();
    bool Initialize();
    void Update(double p_dt);
    bool KillBlock(BOBlock* p_block);
    bool CheckCollisions(BOBall* const p_ball, float2& p_newDirOut, BOBlock*& p_hitBlockOut);
    void Draw();
    void ReviveBlock(BOBlock* p_block);
    bool IsDead() const;

private:
    bool KillBlockInSegment(BOBlock* p_block, BOBossSegment* p_segment);
    void BuildBoss();
    void BuildDrones();
    void UpdateDrones(double p_deg);
    bool BlockIsKeyBlock(BOBlock* p_block);
    std::vector<BlockTimer> m_blocksToRespawn;
    float2 m_direction;
    double m_deg;
    int m_speed;
    int m_removedKeyBlocks;
    int m_liveDrones; 
    float2 m_specialBlockOrigin;
    std::vector<BOBossSegment> m_drones;
    std::vector<BOBlock*> m_keyBlocks;
    
};

