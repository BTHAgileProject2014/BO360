#ifndef BOTECHTREEMANAGER_H_
#define BOTECHTREEMANAGER_H_
#include "BOTechTreeNode.h"
#include "BOTechTreeEffects.h"
#include "BOUtility.h"
#include "BOButton.h"
#include "BOSubscriber.h"
#include "BOPublisher.h"
#include "BODrawableText.h"
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
    void Reset();

private:
    void HandleUpgrades(BOTechTreeNode* p_node);
    BOTechTreeNode* CreateNode(float2 p_pos,int2 p_size, std::string p_tooltip);
    void MapNodes();
    void SetLPE();//Set layer, price and effect
    void SetNodeLPE(BOTechTreeNode* p_node, int p_layer, int p_price, int p_effect);
    void FixAdjacent();
    
    void SetAdjacentNodes(BOTechTreeNode* p_node);


    int2 m_windowSize;
    BOButton m_resetButton;
    BODrawableText m_techPointsText;
    int m_maxTechPoints;
    int m_techPointsLeft;
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
