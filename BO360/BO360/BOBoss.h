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

private:
    BOBlockManager m_blockManager;
};

#endif
