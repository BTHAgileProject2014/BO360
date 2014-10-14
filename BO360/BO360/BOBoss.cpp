#include "BOBoss.h"


BOBoss::BOBoss()
{

}


BOBoss::~BOBoss()
{
}

void BOBoss::Shutdown()
{
    m_blockManager.Shutdown();
}