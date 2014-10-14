#ifndef BOBLOCKMANAGER_H_
#define BOBLOCKMANAGER_H_

#include <vector>
#include "BOComponent.h"
#include "BOBlock.h"

class BOBlockManager : public BOComponent
{
public:
    BOBlockManager();
    ~BOBlockManager();

    // BOBlockManager takes responsibilty over these blocks and should delete them when done
    bool Initialize(std::vector<BOBlock*> p_blockList);
    void Shutdown();

private:
    std::vector<BOBlock*> m_blockList;
};

#endif