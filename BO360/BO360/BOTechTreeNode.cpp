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
    m_isActive = false;
    m_isAdjacentActive = false;
    m_hoveringOver = false;
    m_layer = 0;
    m_price = 0;
    m_effect = 0;

    m_icon = BOTextureManager::GetTexture(TEXTTINACTIVE);
    m_active = BOTextureManager::GetTexture(TEXTTCHOSEN);
    m_inactive = BOTextureManager::GetTexture(TEXTTINACTIVE);
    m_adjacentActive = BOTextureManager::GetTexture(TEXTTADJACENTACTIVE);
    m_highlighted = BOTextureManager::GetTexture(TEXTTHIGHLIGHTED);

    // Tooltip
    m_tooltipHeading.Initialize(float2(0, 0), "Heading", int3(255, 255, 255), 40, 0);
    m_tooltipText.Initialize(float2(0,0), " ", int3(255, 255, 255), 30, 0);
    int2 windowBounds = BOGraphicInterface::GetWindowSize();
    m_tooltipFrame.Initialize(float2(0,0), int2(310,210), BOTextureManager::GetTexture(TEXTTTOLTIPFRAME));
    int2 framesSize = m_tooltipFrame.GetSize();
    m_tooltipFrame.SetPosition(float2(windowBounds.x - 50 - framesSize.x*0.5f, framesSize.y*0.5f +50));
    return BOObject::Initialize(p_pos, p_size, m_inactive);
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
    m_tooltipText.Shutdown();
    m_tooltipFrame.Shutdown();
    m_tooltipHeading.Shutdown();
    BOObject::Shutdown();
}

void BOTechTreeNode::Draw()
{
    BOObject::Draw();
    if (m_hoveringOver)
    {
        m_tooltipFrame.Draw();
        m_tooltipText.Draw();
        m_tooltipHeading.Draw();
    }

    int opacity = 255;

    if (!m_isActive && !m_isAdjacentActive && !m_hoveringOver)
    {
        opacity = 150;
    }

    BOGraphicInterface::Draw(m_icon, m_position, m_size, opacity);
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

void BOTechTreeNode::SetToolTip(std::string p_toolTip, std::string p_heading)
{
    int2 windowBounds = BOGraphicInterface::GetWindowSize();
    float2 tooltipPos = m_tooltipFrame.GetPosition();
    std::string temp;
    if (m_price == 1)
    {
        temp = p_heading + "\n                  {Price: " + std::to_string(m_price) + "   }";
    }
    else
    {
        temp = p_heading + "\n                  {Price: " + std::to_string(m_price) + " }";
    }
    
    m_tooltipHeading.SetText(temp, int3(255, 255, 255), 300);

    int2 headingSize = m_tooltipHeading.GetSize();
    m_tooltipHeading.SetPosition(float2(tooltipPos.x, headingSize.y*0.5f + 60.0f));

    m_tooltipText.SetText(p_toolTip, int3(255, 255, 255), 290);

    int2 textSize = m_tooltipText.GetSize();
    m_tooltipText.SetPosition(float2(windowBounds.x - textSize.x*0.5f -60.0f, textSize.y*0.5f + 60.0f + headingSize.y));
}

int BOTechTreeNode::GetEffect()const
{
    return m_effect;
}
void BOTechTreeNode::SetEffect(int p_effect, std::string p_tooltip)
{
    m_effect = p_effect;
}
void BOTechTreeNode::SetEffect(int p_effect)
{
    m_effect = p_effect;
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

void BOTechTreeNode::SetTexture(SDL_Texture* p_texture)
{
    m_icon = p_texture;
}