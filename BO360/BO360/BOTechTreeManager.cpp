#include "BOTechTreeManager.h"


BOTechTreeManager::BOTechTreeManager()
{
}


BOTechTreeManager::~BOTechTreeManager()
{
}
bool BOTechTreeManager::Initialize(int2 p_windowDimension)
{
    m_windowSize = p_windowDimension;

    m_grid = BOTextureManager::GetTexture(TEXTTHIGHLIGHTED);

    int2 m_Size = int2(100, 100);
    float2 midScreen = float2(m_windowSize.x * 0.5, m_windowSize.y * 0.5 + 150); // To save computation
    int diameter = 7; // Original is 7

    for (int y = diameter - 3, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x                 - x * m_Size.x, midScreen.y                     - (y + 4) * m_Size.y*0.5), m_Size, "1");
    }
    for (int y = diameter - 2, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x      - x * m_Size.x, midScreen.y + m_Size.y * 0.5     - (y + 3) * m_Size.y*0.5), m_Size, "2");
    }
    for (int y = diameter - 1, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 2  - x * m_Size.x, midScreen.y + m_Size.y * 1.5     - (y + 3) * m_Size.y*0.5), m_Size, "3");
    }
    for (int y = diameter, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 2.5     - (y + 3) * m_Size.y*0.5), m_Size, "4");
    }
    for (int y = diameter - 1, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 3       - (y + 3) * m_Size.y*0.5), m_Size, "5");
    }
    for (int y = diameter - 2, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 3.5   - (y + 3) * m_Size.y*0.5), m_Size, "6");
    }
    for (int y = diameter - 3, x = 0; y != 0; y-- ,x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 4     - (y + 3) * m_Size.y*0.5), m_Size, "7");
    }

    MapNodes();
    SetLPE();

    m_resetButton.Initialize(float2(m_windowSize.x-50.0f-250.0f, m_windowSize.y-50.0f-75.0f), int2(250, 75), BOTextureManager::GetTexture(TEXMENUBUTTON), "RESET", NOACTION, "");

    BOPublisher::AddSubscriber(this);

    return true;
}
void BOTechTreeManager::Update()
{
    m_startNode->SetAdjacentActive(true);
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Update();

        if (m_nodeList[i]->Intersects(m_mousePosition))
        {
            if (!m_nodeList[i]->GetActive())
            {
               m_nodeList[i]->SetHover(true);
            }
            if (m_mouseDown && !m_mousePrev)
            {
                m_mousePositionPrev = m_mousePosition;
            }
            if (!m_mouseDown && m_mousePrev)
            {
                if (m_nodeList[i]->Intersects(m_mousePositionPrev))
                {
                    if (m_nodeList[i]->GetAdjacentActive())
                    {
                        m_mousePrev = m_mouseDown;
                        m_nodeList[i]->SetActive(true);
                        SetAdjacentNodes(m_nodeList[i]);
                        HandleUpgrades(m_nodeList[i]);
                    }
                }
            }
        }
        else
        {
            m_nodeList[i]->SetHover(false);
        }
    }

    // Reset button pressed
    if (m_resetButton.Intersects(m_mousePosition))
    {
        if (m_mouseDown && !m_mousePrev)
        {
            m_mousePositionPrev = m_mousePosition;
        }
        if (!m_mouseDown && m_mousePrev)
        {
            if (m_resetButton.Intersects(m_mousePositionPrev))
            {
                m_mousePrev = m_mouseDown;
                Reset();
            }
        }
    }

    m_mousePrev = m_mouseDown;
}
void BOTechTreeManager::Shutdown()
{
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Shutdown();
        delete m_nodeList[i];
        m_nodeList[i] = NULL;
    }
    m_resetButton.Shutdown();
    m_techPointsText.Shutdown();
}
void BOTechTreeManager::Draw()
{
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Draw();
    }

    m_resetButton.Draw();
}
BOTechTreeNode* BOTechTreeManager::CreateNode(float2 p_pos,int2 p_size, std::string p_tooltip)
{
    BOTechTreeNode* newNode = new BOTechTreeNode();
    newNode->Initialize(p_pos, p_size, p_tooltip);
    m_nodeList.push_back(newNode);
    return newNode;
}
void BOTechTreeManager::MapNodes()
{
    for (int i = 0; i < m_nodeList.size() - 1; i++)
    {
        if (i != 3 && i != 8 && i != 14 && i != 21 && i != 27 && i != 32)
        {
            m_nodeList[i]->SetDownLeftNode(m_nodeList[i+ 1]);
            m_nodeList[i+ 1]->SetUpRightNode(m_nodeList[i]);
        }

        if (i < 4)
        {
            m_nodeList[i]->SetDownRightNode(m_nodeList[i + 4]);
            m_nodeList[i + 4]->SetUpLeftNode(m_nodeList[i]);

            m_nodeList[i]->SetDownNode(m_nodeList[i + 5]);
            m_nodeList[i + 5]->SetUpNode(m_nodeList[i]);
        }
        else if (i < 9)
        {
            m_nodeList[i]->SetDownRightNode(m_nodeList[i + 5]);
            m_nodeList[i + 5]->SetUpLeftNode(m_nodeList[i]);

            m_nodeList[i]->SetDownNode(m_nodeList[i + 6]);
            m_nodeList[i + 6]->SetUpNode(m_nodeList[i]);
        }
        else if (i < 15)
        {
            m_nodeList[i]->SetDownRightNode(m_nodeList[i + 6]);
            m_nodeList[i + 6]->SetUpLeftNode(m_nodeList[i]);

            m_nodeList[i]->SetDownNode(m_nodeList[i + 7]);
            m_nodeList[i + 7]->SetUpNode(m_nodeList[i]);
        }
        else if (i < 22)
        {
            if (i != 15)
            {
                m_nodeList[i]->SetDownRightNode(m_nodeList[i + 6]);
                m_nodeList[i + 6]->SetUpLeftNode(m_nodeList[i]);
            }
            if (i != 21)
            {
                m_nodeList[i]->SetDownNode(m_nodeList[i + 7]);
                m_nodeList[i + 7]->SetUpNode(m_nodeList[i]);
            }
        }
        else if (i < 28)
        {
            if (i != 22)
            {
                m_nodeList[i]->SetDownRightNode(m_nodeList[i + 5]);
                m_nodeList[i + 5]->SetUpLeftNode(m_nodeList[i]);
            }
            if (i != 27)
            {
                m_nodeList[i]->SetDownNode(m_nodeList[i + 6]);
                m_nodeList[i + 6]->SetUpNode(m_nodeList[i]);
            }
        }
        else if (i < 33)
        {
            if (i != 28)
            {
                m_nodeList[i]->SetDownRightNode(m_nodeList[i + 4]);
                m_nodeList[i + 4]->SetUpLeftNode(m_nodeList[i]);
            }
            if (i != 32)
            {
                m_nodeList[i]->SetDownNode(m_nodeList[i + 5]);
                m_nodeList[i + 5]->SetUpNode(m_nodeList[i]);
            }
        }
    }

    m_startNode = m_nodeList[(m_nodeList.size()-1)/2];
}
void BOTechTreeManager::SetLPE()
{
    //Set Price
    //Sets start node
    SetNodeLPE(m_startNode, 0, 99, 0);

    //Set Price for layer 1
    m_startNode->GetUpNode()->SetPrice(1);
    m_startNode->GetUpRightNode()->SetPrice(2);
    m_startNode->GetUpLeftNode()->SetPrice(2);
    m_startNode->GetDownNode()->SetPrice(2);
    m_startNode->GetDownRightNode()->SetPrice(1);
    m_startNode->GetDownLeftNode()->SetPrice(1);

    //Sets the price for layer 2 & 3
    FixAdjacent();
    FixAdjacent();
    FixAdjacent();
    FixAdjacent();

    //Set Layer
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        if (m_nodeList[i]->GetPrice() == 1 || m_nodeList[i]->GetPrice() == 2)
        {
            m_nodeList[i]->SetLayer(1);
        }
        else if (m_nodeList[i]->GetPrice() == 3 || m_nodeList[i]->GetPrice() == 4)
        {
            m_nodeList[i]->SetLayer(2);
        }
        else if (m_nodeList[i]->GetPrice() == 5 || m_nodeList[i]->GetPrice() == 6)
        {
            m_nodeList[i]->SetLayer(3);
        }
        //Set Effect
        // Temporary tooltips for demo
        switch (i)
        {
            case(11) :
            {
                m_nodeList[i]->SetEffect(i, "PUG");
                break;
            }
            case(12) :
            {
                m_nodeList[i]->SetEffect(i, "DGP");
                break;
            }
            case(17) :
            {
                m_nodeList[i]->SetEffect(i, "PUFS");
                break;
            }
            case(18) :
            {
                m_nodeList[i]->SetEffect(i, "START");
                break;
            }
            case(19) :
            {
                m_nodeList[i]->SetEffect(i,"DBS");
                break;
            }
            case(24) :
            {
                m_nodeList[i]->SetEffect(i, "SC");
                break;
            }
            case(25) :
            {
                m_nodeList[i]->SetEffect(i, "IPS");
                break;
            }
            default:
                m_nodeList[i]->SetEffect(i);
                break;
        }
    }
}
void BOTechTreeManager::SetNodeLPE(BOTechTreeNode* p_node, int p_layer, int p_price, int p_effect)
{
    p_node->SetLayer(p_layer);
    p_node->SetPrice(p_price);
    p_node->SetEffect(p_effect);
}
void BOTechTreeManager::FixAdjacent()
{
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0;
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        if (m_nodeList[i]->GetPrice() == 0)
        {
            BOTechTreeNode* node = m_nodeList[i];
            n1 = n2 = n3 = n4 = n5 = n6 = 0;
            //Calculate value of adjacent nodes
            if (node->GetUpNode() != NULL)
            {
                if (node->GetUpNode()->GetPrice() == 1)
                {
                    n1++;
                }
                else if (node->GetUpNode()->GetPrice() == 2)
                {
                    n2++;
                }
                else if (node->GetUpNode()->GetPrice() == 3)
                {
                    n3++;
                }
                else if (node->GetUpNode()->GetPrice() == 4)
                {
                    n4++;
                }
                else if (node->GetUpNode()->GetPrice() == 5)
                {
                    n5++;
                }
                else if (node->GetUpNode()->GetPrice() == 6)
                {
                    n6++;
                }
            }
            if (node->GetUpLeftNode() != NULL)
            {
                if (node->GetUpLeftNode()->GetPrice() == 1)
                {
                    n1++;
                }
                else if (node->GetUpLeftNode()->GetPrice() == 2)
                {
                    n2++;
                }
                else if (node->GetUpLeftNode()->GetPrice() == 3)
                {
                    n3++;
                }
                else if (node->GetUpLeftNode()->GetPrice() == 4)
                {
                    n4++;
                }
                else if (node->GetUpLeftNode()->GetPrice() == 5)
                {
                    n5++;
                }
                else if (node->GetUpLeftNode()->GetPrice() == 6)
                {
                    n6++;
                }
            }
            if (node->GetUpRightNode() != NULL)
            {
                if (node->GetUpRightNode()->GetPrice() == 1)
                {
                    n1++;
                }
                else if (node->GetUpRightNode()->GetPrice() == 2)
                {
                    n2++;
                }
                else if (node->GetUpRightNode()->GetPrice() == 3)
                {
                    n3++;
                }
                else if (node->GetUpRightNode()->GetPrice() == 4)
                {
                    n4++;
                }
                else if (node->GetUpRightNode()->GetPrice() == 5)
                {
                    n5++;
                }
                else if (node->GetUpRightNode()->GetPrice() == 6)
                {
                    n6++;
                }
            }
            if (node->GetDownNode() != NULL)
            {
                if (node->GetDownNode()->GetPrice() == 1)
                {
                    n1++;
                }
                else if (node->GetDownNode()->GetPrice() == 2)
                {
                    n2++;
                }
                else if (node->GetDownNode()->GetPrice() == 3)
                {
                    n3++;
                }
                else if (node->GetDownNode()->GetPrice() == 4)
                {
                    n4++;
                }
                else if (node->GetDownNode()->GetPrice() == 5)
                {
                    n5++;
                }
                else if (node->GetDownNode()->GetPrice() == 6)
                {
                    n6++;
                }
            }
            if (node->GetDownLeftNode() != NULL)
            {
                if (node->GetDownLeftNode()->GetPrice() == 1)
                {
                    n1++;
                }
                else if (node->GetDownLeftNode()->GetPrice() == 2)
                {
                    n2++;
                }
                else if (node->GetDownLeftNode()->GetPrice() == 3)
                {
                    n3++;
                }
                else if (node->GetDownLeftNode()->GetPrice() == 4)
                {
                    n4++;
                }
                else if (node->GetDownLeftNode()->GetPrice() == 5)
                {
                    n5++;
                }
                else if (node->GetDownLeftNode()->GetPrice() == 6)
                {
                    n6++;
                }
            }
            if (node->GetDownRightNode() != NULL)
            {
                if (node->GetDownRightNode()->GetPrice() == 1)
                {
                    n1++;
                }
                else if (node->GetDownRightNode()->GetPrice() == 2)
                {
                    n2++;
                }
                else if (node->GetDownRightNode()->GetPrice() == 3)
                {
                    n3++;
                }
                else if (node->GetDownRightNode()->GetPrice() == 4)
                {
                    n4++;
                }
                else if (node->GetDownRightNode()->GetPrice() == 5)
                {
                    n5++;
                }
                else if (node->GetDownRightNode()->GetPrice() == 6)
                {
                    n6++;
                }
            }
            //Calculate value for current node
            //Look for value 5
            if (n3 == 1 && n4 == 1)
            {
                node->SetPrice(5);
            }
            //Look for value 6
            else if (n4 == 1 && n5 == 2)
            {
                node->SetPrice(6);
            }
            //Look for value 4
            else if ((n1 == 1 && n3 == 2) || (n2 == 1 && n3 == 2))
            {
                node->SetPrice(4);
            }
            //Look for value 3
            else if (n1 == 1 && n2 == 1)
            {
                node->SetPrice(3);
            }
        }
    }
    m_startNode->GetPrice();
}
void BOTechTreeManager::Reset()
{
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Reset();
    }
    
    BOTechTreeEffects::BallEffects = TechTreeBallEffects();
    BOTechTreeEffects::LevelEffects = TechTreeLevelEffects();
    BOTechTreeEffects::PaddleEffects = TechTreePaddleEffects();
    BOTechTreeEffects::PUEffects = TechTreePUEffects();
    BOTechTreeEffects::UtilityEffects = TechTreeUtilityEffects();
}

void BOTechTreeManager::Handle(InputMessages p_inputMessages)
{
    m_mousePosition = int2(p_inputMessages.mouseX, p_inputMessages.mouseY);
    m_mouseDown = p_inputMessages.leftMouseKey;
}

void BOTechTreeManager::SetAdjacentNodes(BOTechTreeNode* p_node)
{
    if (p_node->GetUpNode() != NULL)
    {
        p_node->GetUpNode()->SetAdjacentActive(true);
    }
    if (p_node->GetUpLeftNode() != NULL)
    {
        p_node->GetUpLeftNode()->SetAdjacentActive(true);
    }
    if (p_node->GetUpRightNode() != NULL)
    {
        p_node->GetUpRightNode()->SetAdjacentActive(true);
    }
    if (p_node->GetDownNode() != NULL)
    {
        p_node->GetDownNode()->SetAdjacentActive(true);
    }
    if (p_node->GetDownLeftNode() != NULL)
    {
        p_node->GetDownLeftNode()->SetAdjacentActive(true);
    }
    if (p_node->GetDownRightNode() != NULL)
    {
        p_node->GetDownRightNode()->SetAdjacentActive(true);
    }
}
void BOTechTreeManager::HandleUpgrades(BOTechTreeNode* p_node)
{
    int upgradeIdentifier = p_node->GetEffect();
    switch (upgradeIdentifier)
    {
    case DropBasicPowerUp:
        break;
    case DecreasePowerUpFallSpeed:
        BOTechTreeEffects::PUEffects.speed -= 0.25f;
        break;
    case AddBounceToShield:
        BOTechTreeEffects::PUEffects.shieldCharge++;
        break;
    case IncreasePadSpeed:
        BOTechTreeEffects::PaddleEffects.speed + 1.25f;
        break;
    case DecreaseBallSpeed:
        BOTechTreeEffects::BallEffects.speed -= 0.25f;
        break;
    case DecreaseGravityPull:
        BOTechTreeEffects::BallEffects.gravity = 1;
        break;
    case PowerUpGift:
        BOTechTreeEffects::UtilityEffects.PUGiftEnabled = true;
        break;
    case DecreasePowerUpFallSpeed2:///////////_STOP
        break;
    case StartWithShield:
        break;
    case StickyPad:
        break;
    case IncreaseMaxPadSize:
        break;
    case ChanceDoublePadSizeIncrease:
        break;
    case IncreaseMaxPadSize2:
        break;
    case BallsGetFuelWhenTheyCollide:
        break;
    case MoreFuelAtRefill:
        break;
    case IncreaseBallDamage:
        break;
    case Fireball:
        break;
    case IncreaseBallDamage2:
        break;
    case SlowTime:
        break;
    case PowerUpBoost1:
        break;
    case PowerUpBoost2:
        break;
    case MegaPad:
        break;
    case StackableShield:
        break;
    case IncreaseStartPadSize:
        break;
    case Regenerate:
        break;
    case IncreaseStartPadSize2:
        break;
    case ChanceDoublePadSizeIncrease2:
        break;
    case GiantBall:
        break;
    case MuliSpawn:
        break;
    case DoubleMultiBall:
        break;
    case SuperTank:
        break;
    case DoubleMultiBall2:
        break;
    case MultiSpawn2:
        break;
    case QuantumFuel:
        break;
    case DoubleMultiBall3:
        break;
    case PowerUpBoost3:
        break;
    case ShockWave:
        break;
    }
}