#ifndef BOBOSS_H_
#define BOBOSS_H_

#include "BOBlockManager.h"

class BOBoss : BOComponent
{
public:
    BOBoss();
    ~BOBoss();

    virtual bool Initialize() = 0;
    void Shutdown();
    virtual void Draw();
    virtual void Update(double p_dt);
    virtual bool CheckCollisions(BOBall* const p_ball, float2& p_newDirOut, BOBlock*& p_hitBlockOut);
    virtual bool KillBlock(BOBlock* p_block);
    float2 GetPosition() const;
protected:
    BOBlockManager m_blockManager;
    float2 m_position;
};

#endif
