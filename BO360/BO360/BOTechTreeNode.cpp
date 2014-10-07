#include "BOTechTreeNode.h"


BOTechTreeNode::BOTechTreeNode()
{
    m_layer = 0;
    m_price = 0;
    m_effect = 0;
    m_up = NULL;
    m_upLeft = NULL;
    m_upRight = NULL;
    m_down = NULL;
    m_downLeft = NULL;
    m_downRight = NULL;
}

BOTechTreeNode::~BOTechTreeNode()
{
}

bool BOTechTreeNode::Initialize(float2 p_pos, int2 p_size, int p_layer, int p_price, int p_effect)
{
    m_position = p_pos;
    m_size = p_size;

    m_active = false;
    m_adjacentActive = false;
    m_layer = p_layer;
    m_price = p_price;
    m_effect = p_effect;

    m_active = BOTextureManager::GetTexture(TEXHEXPU1);
    m_inactive = BOTextureManager::GetTexture(TEXHEXPU2);
    m_adjacentActive = BOTextureManager::GetTexture(TEXHEXPU3);

    //m_sprite = m_inactive;

    return BOObject::Initialize(m_position, m_size, m_inactive);
}

void BOTechTreeNode::Update()
{
    if (m_active)
    {
        m_sprite = m_active;
        
    }
    else if (m_adjacentActive)
    {
        m_sprite = m_adjacentActive;
    }
    else
    {
        m_sprite = m_inactive;
    }
}

void BOTechTreeNode::Shutdown()
{
    BOObject::Shutdown();
}

void BOTechTreeNode::Draw()
{
    BOObject::Draw();
}

void BOTechTreeNode::InitializeAdjacentNodes(BOTechTreeNode* p_up, BOTechTreeNode* p_upLeft, BOTechTreeNode* p_upRight, BOTechTreeNode* p_down, BOTechTreeNode* p_downLeft, BOTechTreeNode* p_downRight)
{
    m_up = p_up;
    m_upLeft = p_upLeft;
    m_upRight = p_upRight;
    m_down = p_down;
    m_downLeft = p_downLeft;
    m_downRight = p_downRight;
}
float2 BOTechTreeNode::GetPosition()const
{
    return m_position;
}