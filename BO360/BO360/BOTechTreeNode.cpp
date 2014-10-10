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

bool BOTechTreeNode::Initialize(float2 p_pos, int2 p_size, std::string p_tooltip)
{
    m_position = p_pos;
    m_size = p_size;

    m_isActive = false;
    m_isAdjacentActive = false;
    m_hoveringOver = false;
    m_layer = 0;
    m_price = 0;
    m_effect = 0;

    m_active = BOTextureManager::GetTexture(TEXTTACTIVE);
    m_inactive = BOTextureManager::GetTexture(TEXTTINACTIVE);
    m_adjacentActive = BOTextureManager::GetTexture(TEXTTADJACENTACTIVE);
    m_highlighted = BOTextureManager::GetTexture(TEXTTHIGHLIGHTED);

    m_sprite = m_inactive;

    return BOObject::Initialize(m_position, m_size, m_sprite);
}

void BOTechTreeNode::Update()
{
    if (m_isActive)
    {
        m_sprite = m_active;
        
    }
    else if (m_hoveringOver)
    {
        m_sprite = m_highlighted;
    }
    else if (m_isAdjacentActive)
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
    m_tooltip.Shutdown();
    BOObject::Shutdown();
}

void BOTechTreeNode::Draw()
{
    BOObject::Draw();
    m_tooltip.Draw();
}
float2 BOTechTreeNode::GetPosition()const
{
    return m_position;
}

void BOTechTreeNode::SetActive(bool p_active)
{
    m_isActive = p_active;
}
bool BOTechTreeNode::GetActive()const
{
    return m_isActive;
}

BOTechTreeNode* BOTechTreeNode::GetUpNode()const
{
    return m_up;
}
void BOTechTreeNode::SetUpNode(BOTechTreeNode* p_node)
{
    m_up = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetUpLeftNode()const
{
    return m_upLeft;
}
void BOTechTreeNode::SetUpLeftNode(BOTechTreeNode* p_node)
{
    m_upLeft = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetUpRightNode()const
{
    return m_upRight;
}
void BOTechTreeNode::SetUpRightNode(BOTechTreeNode* p_node)
{
    m_upRight = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetDownNode()const
{
    return m_down;
}
void BOTechTreeNode::SetDownNode(BOTechTreeNode* p_node)
{
    m_down = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetDownLeftNode()const
{
    return m_downLeft;
}
void BOTechTreeNode::SetDownLeftNode(BOTechTreeNode* p_node)
{
    m_downLeft = p_node;
}
BOTechTreeNode* BOTechTreeNode::GetDownRightNode()const
{
    return m_downRight;
}
void BOTechTreeNode::SetDownRightNode(BOTechTreeNode* p_node)
{
    m_downRight = p_node;
}
int BOTechTreeNode::GetLayer()const
{
    return m_layer;
}
void BOTechTreeNode::SetLayer(int p_layer)
{
    m_layer = p_layer;
}

int BOTechTreeNode::GetPrice()const
{
    return m_price;
}
void BOTechTreeNode::SetPrice(int p_price)
{
    m_price = p_price;
}

int BOTechTreeNode::GetEffect()const
{
    return m_effect;
}
void BOTechTreeNode::SetEffect(int p_effect, std::string p_tooltip)
{
    m_effect = p_effect;
    m_tooltip.Initialize(m_position, p_tooltip, int3(255, 255, 255), 30, 0);
}
void BOTechTreeNode::SetEffect(int p_effect)
{
    m_effect = p_effect;
    m_tooltip.Initialize(m_position, " ", int3(255, 255, 255), 30, 0);
}
void BOTechTreeNode::Reset()
{
    m_isActive = false;
    m_isAdjacentActive = false;
}
bool BOTechTreeNode::Intersects(int2 p_mousePosition)
{
    // Intersection test.
    if (BOPhysics::CheckCollisionSphereToSphere(sphere(float2((float)p_mousePosition.x, (float)p_mousePosition.y), 1), sphere(m_position, m_size.x / 2)))
    {
        return true;
    }
    return false;
}

bool BOTechTreeNode::GetAdjacentActive()const
{
    return m_isAdjacentActive;
}
void BOTechTreeNode::SetAdjacentActive(bool p_active)
{
    m_isAdjacentActive = p_active;
}
void BOTechTreeNode::SetHover(bool p_active)
{
    m_hoveringOver = p_active;
}