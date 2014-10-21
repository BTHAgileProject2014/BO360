#ifndef BO_BOSS_SEGMENT_
#define BO_BOSS_SEGMENT_

#include "BOUtility.h"
#include "BOBlockManager.h"
#include "BOMapLoader.h"

class BOBossSegment : public BOComponent
{
public:
    BOBossSegment();
    ~BOBossSegment();

    void SetPosition(const float2 p_position);
    float2 GetPosition() const;
    bool Initialize();
    void Update(double p_dt);
    void Draw();
    void Draw(float2 p_offset);
    void Shutdown();
    bool CheckCollisions(const BOBall* const p_ball, const float2 p_offset, float2& p_newDirOut, BOBlock*& p_hitBlockOut);
    bool InitializeWithBlocklist(std::vector<BOBlock*> p_blocks);
    bool KillBlock(BOBlock* p_block);
    bool HideBlock(BOBlock* p_block);
    bool LoadSegmentFromFile(std::string p_filename);
    BOBlockManager& GetBlockManagerRef();
    bool IsEmpty() const;

    private:
    float2 m_position;
    BOBlockManager m_blockManager;
};

#endif