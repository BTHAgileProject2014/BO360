#ifndef BOTECHTREENODE_H_
#define BOTECHTREENODE_H_
#include "BOObject.h"
#include "BOUtility.h"
#include "BOPhysics.h"
#include "BODrawableText.h"

#include <string>

class BOTechTreeNode: public BOObject
{
public:
    BOTechTreeNode();
    ~BOTechTreeNode();

    bool Initialize(float2 p_pos, int2 p_size, std::string p_toolTip);
    void Update(int p_techPoints);
    void Shutdown();
    void Draw();


    bool GetActive()const;
    void SetActive(bool p_active);

    bool GetAdjacentActive()const;
    void SetAdjacentActive(bool p_active);

    void SetHover(bool p_active);

    float2 GetPosition()const;

    BOTechTreeNode* GetUpNode()const;
    void SetUpNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetUpLeftNode()const;
    void SetUpLeftNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetUpRightNode()const;
    void SetUpRightNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetDownNode()const;
    void SetDownNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetDownLeftNode()const;
    void SetDownLeftNode(BOTechTreeNode* p_Node);

    BOTechTreeNode* GetDownRightNode()const;
    void SetDownRightNode(BOTechTreeNode* p_Node);

    int GetLayer()const;
    void SetLayer(int p_layer);

    int GetPrice()const;
    void SetPrice(int p_price);

    int GetEffect()const;
    void SetEffect(int p_effect, std::string p_tooltip);
    void SetEffect(int p_effect);

    void Reset();
    bool Intersects(int2 p_mousePosition);

    void SetToolTip(std::string p_toolTip, std::string p_heading);
    void SetTexture(SDL_Texture* p_texture);

private:
    void SetEffect();
    void ResetEffect();

    SDL_Texture* m_icon;
    SDL_Texture* m_active;
    SDL_Texture* m_inactive;
    SDL_Texture* m_adjacentActive;
    SDL_Texture* m_highlighted;

    BOTechTreeNode* m_up;
    BOTechTreeNode* m_upLeft;
    BOTechTreeNode* m_upRight;
    BOTechTreeNode* m_down;
    BOTechTreeNode* m_downLeft;
    BOTechTreeNode* m_downRight;

    bool m_isActive;
    bool m_isAdjacentActive;
    bool m_hoveringOver;
    int m_layer;
    int m_price;
    int m_effect;

    BODrawableText m_tooltipHeading;
    BODrawableText m_tooltipText;
    BODrawableText m_priceText;
    BOObject m_tooltipFrame;
};

#endif