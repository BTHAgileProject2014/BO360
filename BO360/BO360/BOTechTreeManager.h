#ifndef BOTECHTREEMANAGER_H_
#define BOTECHTREEMANAGER_H_
#include "BOTechTreeNode.h"
#include "BOUtility.h"
#include "BOButton.h"
#include "BOSubscriber.h"
#include "BOPublisher.h"
#include <vector>

class BOTechTreeManager: public BOSubscriber 
{
public:
    BOTechTreeManager();
    ~BOTechTreeManager();

    bool Initialize(int2 p_windowDimension);
    void Update();
    void Shutdown();
    void Draw();
    void Handle(InputMessages p_inputMessages);

private:
    BOTechTreeNode* CreateNode(float2 p_pos,int2 p_size);
    void MapNodes();
    void SetLPE();//Set layer, price and effect
    void SetNodeLPE(BOTechTreeNode* p_node, int p_layer, int p_price, int p_effect);
    void FixAdjacent();
    void Reset();


    int2 m_windowSize;
    BOButton m_resetButton;
    std::vector<BOTechTreeNode*> m_nodeList;
    BOTechTreeNode* m_startNode;
    SDL_Texture* m_grid;

    int2 m_mousePosition;
    int2 m_mousePositionPrev;
    bool m_mouseDown;
    bool m_mousePrev;
    bool m_clicked;
    bool m_clickedPrev;
};
#endif
