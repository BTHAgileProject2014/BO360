#ifndef BOTECHTREEMANAGER_H_
#define BOTECHTREEMANAGER_H_
#include "BOTechTreeNode.h"
#include "BOUtility.h"

#include <vector>

class BOTechTreeManager
{
public:
    BOTechTreeManager();
    ~BOTechTreeManager();

    bool Initialize(int2 p_windowDimension);
    void Update();
    void Shutdown();
    void Draw();


private:
    BOTechTreeNode* CreateNode(float2 p_pos, int p_layer, int p_price, int p_effect);


    int2 m_windowSize;

    std::vector<BOTechTreeNode*> m_nodeList;
    BOTechTreeNode* m_startNode;


};
#endif
