#ifndef BOTECHTREENODE_H_
#define BOTECHTREENODE_H_
#include "BOObject.h"
#include "BOUtility.h"

class BOTechTreeNode: public BOObject
{
public:
    BOTechTreeNode();
    ~BOTechTreeNode();

    bool Initialize(float2 p_pos, int2 p_size, int p_layer, int p_price, int p_effect);
    void Update();
    void Shutdown();
    void Draw();

    bool GetActive()const;
    void SetActive(bool p_active);

    void InitializeAdjacentNodes(BOTechTreeNode* p_up, BOTechTreeNode* p_upLeft, BOTechTreeNode* p_upRight, BOTechTreeNode* p_down, BOTechTreeNode* p_downLeft, BOTechTreeNode* p_downRight);
    float2 GetPosition()const;

    BOTechTreeNode* GetUpNode();
    void SetUpNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetUpLeftNode();
    void SetUpLeftNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetUpRightNode();
    void SetUpRightNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetDownNode();
    void SetDownNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetDownLeftNode();
    void SetDownLeftNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetDownRightNode();
    void SetDownRightNode(BOTechTreeNode* p_Node);
    

private:
    void SetEffect();
    void ResetEffect();


    SDL_Texture* m_active;
    SDL_Texture* m_inactive;
    SDL_Texture* m_adjacentActive;


    BOTechTreeNode* m_up;
    BOTechTreeNode* m_upLeft;
    BOTechTreeNode* m_upRight;
    BOTechTreeNode* m_down;
    BOTechTreeNode* m_downLeft;
    BOTechTreeNode* m_downRight;

    bool m_isActive;
    bool m_isAdjacentActive;
    int m_layer;
    int m_price;
    int m_effect;
    

};

#endif