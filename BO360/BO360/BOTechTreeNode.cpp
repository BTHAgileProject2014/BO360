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

bool BOTechTreeNode::Initialize(float2 p_pos, int2 p_size)
{
    m_position = p_pos;
    m_size = p_size;

    m_active = false;
    m_isAdjacentActive = false;
    m_layer = 0;
    m_price = 0;
    m_effect = 0;

    m_active = BOTextureManager::GetTexture(TEXHEXPU1);
    m_inactive = BOTextureManager::GetTexture(TEXHEXPUSHOCKWAVE);
    m_adjacentActive = BOTextureManager::GetTexture(TEXLIFE);

    m_sprite = m_inactive;

    return BOObject::Initialize(m_position, m_size, m_sprite);
}

void BOTechTreeNode::Update()
{
    //if (m_layer == 3)
    //{
    //    m_sprite = m_active;
    //    
    //}
    //else if (m_layer == 1)
    //{
    //    m_sprite = m_adjacentActive;
    //}
    //else
    //{
    //    m_sprite = m_inactive;
    //}

    //if (m_isActive)
    //{
    //    m_sprite = m_active;
    //    
    //}
    //else if (m_adjacentActive)
    //{
    //    m_sprite = m_adjacentActive;
    //}
    //else
    //{
    //    m_sprite = m_inactive;
    //}

    if (m_down != NULL)
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
float2 BOTechTreeNode::GetPosition()const
{
    return m_position;
}

BOTechTreeNode* BOTechTreeNode::GetUpNode()
{
    return m_up;
}
void BOTechTreeNode::SetUpNode(BOTechTreeNode* p_node)
{
    m_up = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetUpLeftNode()
{
    return m_upLeft;
}
void BOTechTreeNode::SetUpLeftNode(BOTechTreeNode* p_node)
{
    m_upLeft = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetUpRightNode()
{
    return m_upRight;
}
void BOTechTreeNode::SetUpRightNode(BOTechTreeNode* p_node)
{
    m_upRight = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetDownNode()
{
    return m_down;
}
void BOTechTreeNode::SetDownNode(BOTechTreeNode* p_node)
{
    m_down = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetDownLeftNode()
{
    return m_downLeft;
}
void BOTechTreeNode::SetDownLeftNode(BOTechTreeNode* p_node)
{
    m_downLeft = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetDownRightNode()
{
    return m_downRight;
}
void BOTechTreeNode::SetDownRightNode(BOTechTreeNode* p_node)
{
    m_downRight = p_node;
}
int BOTechTreeNode::GetLayer()
{
    return m_layer;
}
void BOTechTreeNode::SetLayer(int p_layer)
{
    m_layer = p_layer;
}

int BOTechTreeNode::GetPrice()
{
    return m_price;
}
void BOTechTreeNode::SetPrice(int p_price)
{
    m_price = m_price;
}

int BOTechTreeNode::GetEffect()
{
    return m_effect;
}
void BOTechTreeNode::SetEffect(int p_effect)
{
    m_effect = p_effect;
}