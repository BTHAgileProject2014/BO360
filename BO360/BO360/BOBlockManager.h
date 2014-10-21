#ifndef BOBLOCKMANAGER_H_
#define BOBLOCKMANAGER_H_

#include <vector>
#include "BOComponent.h"
#include "BOBlock.h"
#include "BOBall.h"
#include "BOBlockMultiTexture.h"

class BOBlockManager : public BOComponent
{
public:
    BOBlockManager();
    ~BOBlockManager();

    // BOBlockManager takes responsibilty over these blocks and should delete them when done
    bool Initialize(std::vector<BOBlock*> p_blockList);
    void Shutdown();
    void AddBlock(BOBlock* p_blockPtr);
    void Draw();
    void Update(float p_dt);
    static bool CheckCollisionAgainstBlock(const BOBall* const p_ball, const float2 p_offset, const BOBlock* const p_block, float2& p_newDirOut);
    bool CheckCollisions(const BOBall* const p_ball, const float2 p_offset, float2& p_newDirOut, BOBlock*& p_hitBlockOut);
    bool RemoveBlock(BOBlock* p_block);
    bool HideBlock(BOBlock* p_block);
    bool IsEmpty() const;
    std::vector<BOBlock*> GetUnderlyingBlockList();
private:
    std::vector<BOBlock*> m_blockList;
};

#endif