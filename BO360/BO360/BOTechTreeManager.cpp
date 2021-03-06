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
    float2 midScreen = float2(m_windowSize.x * 0.5f, m_windowSize.y * 0.5f + 150); // To save computation
    int diameter = 7; // Original is 7
    float xOffset = m_Size.x * 0.85f;
    float yOffset = m_Size.y*0.5f;

    for (unsigned int y = diameter - 3, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x - x * xOffset, midScreen.y - (y + 4) * yOffset), m_Size, " ");
    }
    for (unsigned int y = diameter - 2, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + xOffset - x * xOffset, midScreen.y + yOffset - (y + 3) * yOffset), m_Size, " ");
    }
    for (unsigned int y = diameter - 1, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + xOffset * 2 - x * xOffset, midScreen.y + yOffset * 3 - (y + 3) * yOffset), m_Size, " ");
    }
    for (unsigned int y = diameter, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + xOffset * 3 - x * xOffset, midScreen.y + yOffset * 5 - (y + 3) * yOffset), m_Size, " ");
    }
    for (unsigned int y = diameter - 1, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + xOffset * 3 - x * xOffset, midScreen.y + yOffset * 6 - (y + 3) * yOffset), m_Size, " ");
    }
    for (unsigned int y = diameter - 2, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + xOffset * 3 - x * xOffset, midScreen.y + yOffset * 7 - (y + 3) * yOffset), m_Size, " ");
    }
    for (unsigned int y = diameter - 3, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + xOffset * 3 - x * xOffset, midScreen.y + yOffset * 8 - (y + 3) * yOffset), m_Size, " ");
    }

    MapNodes();
    SetLPE();

    m_resetButton.Initialize(float2(m_windowSize.x-300.0f, m_windowSize.y-125.0f), int2(250, 75), BOTextureManager::GetTexture(TEXMENUBUTTON), "RESET", TECHTREERESET, "");

    // Tech Points
    m_techPointsText.Initialize(float2(0,0), "ERROR", int3(255, 255, 255), 50, 0);
    float2 resetPos = m_resetButton.GetPosition();
    int2 resetSize = m_resetButton.GetSize();
    int2 textSize = m_techPointsText.GetSize();
    m_techPointsText.SetPosition(float2(resetPos.x - textSize.x*0.5f - 50.0f, resetPos.y + resetSize.y*0.5f));
    m_maxTechPoints = 0;
    m_techPointsLeft = 0;

    BOPublisher::AddSubscriber(this);

    return true;
}
void BOTechTreeManager::Update()
{
    m_startNode->SetAdjacentActive(true);
    //SetAdjacentNodes(m_startNode);

    for (unsigned int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Update(m_techPointsLeft);

        if (m_nodeList[i]->Intersects(m_mousePosition))
        {
            m_nodeList[i]->SetHover(true);
            if (m_mouseDown && !m_mousePrev)
            {
                m_mousePositionPrev = m_mousePosition;
            }
            if (!m_mouseDown && m_mousePrev)
            {
                if (m_nodeList[i]->Intersects(m_mousePositionPrev))
                {
                    if (m_nodeList[i]->GetAdjacentActive() && !m_nodeList[i]->GetActive())
                    {
                        if (m_techPointsLeft >= m_nodeList[i]->GetPrice())
                        {
                            m_mousePrev = m_mouseDown;
                            m_nodeList[i]->SetActive(true);
                            SetAdjacentNodes(m_nodeList[i]);
                            HandleUpgrades(m_nodeList[i]);
                            m_techPointsLeft -= m_nodeList[i]->GetPrice();
                            SetTechPointText();
                        }
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
    for (unsigned int i = 0; i < m_nodeList.size(); i++)
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
    for (unsigned int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Draw();
    }

    m_resetButton.Draw();
    m_techPointsText.Draw();
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
    for (unsigned int i = 0; i < m_nodeList.size() - 1; i++)
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
    SetNodeLPE(m_startNode, 0, 3, 0);

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
    for (unsigned int i = 0; i < m_nodeList.size(); i++)
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
        m_nodeList[i]->SetEffect(i);
        // Tooltips
        HandleToolTips(m_nodeList[i]);
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
    for (unsigned int i = 0; i < m_nodeList.size(); i++)
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
    for (unsigned int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Reset();
    }
    
    BOTechTreeEffects::BallEffects = TechTreeBallEffects();
    BOTechTreeEffects::LevelEffects = TechTreeLevelEffects();
    BOTechTreeEffects::PaddleEffects = TechTreePaddleEffects();
    BOTechTreeEffects::PUEffects = TechTreePUEffects();
    BOTechTreeEffects::UtilityEffects = TechTreeUtilityEffects();

    m_techPointsLeft = m_maxTechPoints;
    SetTechPointText();
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
        BOTechTreeEffects::LevelEffects.startNodePowerups = true;
        break;
    case DecreasePowerUpFallSpeed:
        BOTechTreeEffects::PUEffects.speed -= 0.15f;
        break;
    case AddBounceToShield:
        BOTechTreeEffects::PUEffects.shieldCharge++;
        break;
    case IncreasePadSpeed:
        BOTechTreeEffects::PaddleEffects.speed = 1.20f;
        break;
    case DecreaseBallSpeed:
        BOTechTreeEffects::BallEffects.speed -= 0.1f;
        break;
    case DecreaseGravityPull:
        BOTechTreeEffects::BallEffects.gravity = 1;
        break;
    case PowerUpGift:
        BOTechTreeEffects::UtilityEffects.PUGiftEnabled = true;
        break;
    case DecreasePowerUpFallSpeed2:
        BOTechTreeEffects::PUEffects.speed -= 0.20f;
        break;
    case StartWithShield:
        BOTechTreeEffects::PUEffects.startShield = true;
        break;
    case StickyPad:
        BOTechTreeEffects::LevelEffects.stickyPadPUDuration = 5.0f;
        break;
    case IncreaseMaxPadSize:
        BOTechTreeEffects::PaddleEffects.maxSize += 1;
        break;
    case ChanceDoublePadSizeIncrease:
        BOTechTreeEffects::PUEffects.biggerPadEffectMultiplier += 0.33f;
        break;
    case IncreaseMaxPadSize2:
        BOTechTreeEffects::PaddleEffects.maxSize += 1;
        break;
    case BallsGetFuelWhenTheyCollide:
        BOTechTreeEffects::UtilityEffects.ballsCollideFuel = true;
        break;
    case MoreFuelAtRefill:
        BOTechTreeEffects::UtilityEffects.extraBallFuel = 3.0f;
        break;
    case IncreaseBallDamage:
        BOTechTreeEffects::BallEffects.damage += 1;
        break;
    case Fireball:
        BOTechTreeEffects::LevelEffects.fireBallPUDuration += 5.0f;
        break;
    case IncreaseBallDamage2:
        BOTechTreeEffects::BallEffects.damage += 1;
        break;
    case SlowTime:
        BOTechTreeEffects::LevelEffects.slowTimePUDuration = 5.0f;
        break;
    case PowerUpBoost1:
        BOTechTreeEffects::PUEffects.multiBallMultiplyChance += 0.33f;
        BOTechTreeEffects::PUEffects.biggerPadEffectMultiplier += 0.33f;
        break;
    case PowerUpBoost2:
        BOTechTreeEffects::LevelEffects.slowTimePUDuration += 3.0f;
        BOTechTreeEffects::LevelEffects.fireBallPUDuration += 3.0f;
        break;
    case MegaPad:
        BOTechTreeEffects::UtilityEffects.megaPadEnabled = true;
        break;
    case StackableShield:
        BOTechTreeEffects::PUEffects.stackableShield = true;
        break;
    case IncreaseStartPadSize:
        BOTechTreeEffects::PaddleEffects.size += 1;
        break;
    case Regenerate:
        BOTechTreeEffects::UtilityEffects.extraLifePerLevel = 1;
        break;
    case IncreaseStartPadSize2:
        BOTechTreeEffects::PaddleEffects.size += 1;
        break;
    case ChanceDoublePadSizeIncrease2:
        BOTechTreeEffects::PUEffects.biggerPadEffectMultiplier += 0.33f;
        break;
    case GiantBall:
        BOTechTreeEffects::UtilityEffects.giantBallEnabled = true;
        break;
    case MuliSpawn:
        BOTechTreeEffects::UtilityEffects.extraBallsFirstLaunch += 0.33f;
        break;
    case DoubleMultiBall:
        BOTechTreeEffects::PUEffects.multiBallMultiplyChance += 0.33f;
        break;
    case SuperTank:
        BOTechTreeEffects::UtilityEffects.superBouncy = true;
        break;
    case DoubleMultiBall2:
        BOTechTreeEffects::PUEffects.multiBallMultiplyChance += 0.33f;
        break;
    case MultiSpawn2:
        BOTechTreeEffects::UtilityEffects.extraBallsFirstLaunch += 0.33f;
        break;
    case QuantumFuel:
        BOTechTreeEffects::UtilityEffects.quantumFuelEnabled = true;
        break;
    case DecreaseCD:
        BOTechTreeEffects::PUEffects.decreaseCD = 0.75f;
        break;
    case MultiSpawn3:
        BOTechTreeEffects::UtilityEffects.extraBallsFirstLaunch += 0.33f;
        break;
    case ShockWave:
        BOTechTreeEffects::UtilityEffects.shockwaveEnabled = true;
        break;
    }
}
void BOTechTreeManager::HandleToolTips(BOTechTreeNode* p_node)
{
    int upgradeIdentifier = p_node->GetEffect();
    switch (upgradeIdentifier)
    {
    case DropBasicPowerUp:
        p_node->SetToolTip("Break blocks without breaking the technology inside. This allows power ups to be dropped from hexagons.", "Scavenge Technology");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTDROPBASICPOWERUP));
        break;
    case DecreasePowerUpFallSpeed:
        p_node->SetToolTip("Lowers the fall speed of power ups by 15%.", "Obtainable Technology");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTDECREASEPOWERUPFALLSPEED));
        break;
    case AddBounceToShield:
        p_node->SetToolTip("Allow shields to reflect an additional pod before breaking.", "Second Chance");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTADDBOUNCETOSHIELD));
        break;
    case IncreasePadSpeed:
        p_node->SetToolTip("Increases the movement speed of the mothership by 20%", "Effective Engines");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTINCREASEPADSPEED));
        break;
    case DecreaseBallSpeed:
        p_node->SetToolTip("Decrease pod speed by 10%             ", "Throttled Engines");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTDECREASEBALLSPEED));
        break;
    case DecreaseGravityPull:
        p_node->SetToolTip("Upgrade escape pods to use a lightweight hull, causing less interference from the black hole.", "Improved Alloy");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTDECREASEGRAVITYPULL));
        break;
    case PowerUpGift:
        p_node->SetToolTip("Scan your surroundings for new technology, adding a chance for a technology to drop when new pods are launched.", "Technology Radar");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTPOWERUPGIFT));
        break;
    case DecreasePowerUpFallSpeed2:
        p_node->SetToolTip("Lowers the fall speed of power ups by 20%.", "Obtainable Technology 2");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTDECREASEPOWERUPFALLSPEED));
        break;
    case StartWithShield:
        p_node->SetToolTip("Start the level with an active shield.", "Pre-charged Batteries");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTSTARTWITHSHIELD));
        break;
    case StickyPad:
        p_node->SetToolTip("Increases the duration of Magnetic Field.", "Improved Magnetic Core");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTSTICKYPAD));
        break;
    case IncreaseMaxPadSize:
        p_node->SetToolTip("Increase the maximum ship segment limit by 1.", "Reinforced Backbone");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTINCREASEMAXPADSIZE));
        break;
    case ChanceDoublePadSizeIncrease:
        p_node->SetToolTip("Adds a 1/3 chance to get an additional ship segments when catching the ship segment tech.", "Skilled Engineer");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTCHANCETODOUBLEPADSIZEINCREASE));
        break;
    case IncreaseMaxPadSize2:
        p_node->SetToolTip("Increase the maximum ship segment limit by 1.", "Reinforced Backbone");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTINCREASEMAXPADSIZE));
        break;
    case BallsGetFuelWhenTheyCollide:
        p_node->SetToolTip("When escape pods collide with each other, their tanks refill. We don't know how it works, it just does!", "Higgs-Boson Fuel");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTBALLSGETFUELWHENTHEYCOLLIDE));
        break;
    case MoreFuelAtRefill:
        p_node->SetToolTip("Increases the amount of fuel a pod can carry.", "Oversized Fuel Tanks");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTMOREFUELATREFILL));
        break;
    case IncreaseBallDamage:
        p_node->SetToolTip("Adds spikes to the hull of escape pods, resulting in more damage dealt against hexagons.", "Spiked Hull");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTINCREASEBALLDAMAGE));
        break;
    case Fireball:
        p_node->SetToolTip("Yes, it's dangerous, but it's also awesome. Increases the duration of Burning Pod.", "Rocket-Fuel Coating");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTFIREBALL));
        break;
    case IncreaseBallDamage2:
        p_node->SetToolTip("Adds spikes to the hull of escape pods, resulting in more damage dealt against hexagons.", "Spiked Hull");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTINCREASEBALLDAMAGE));
        break;
    case SlowTime:
        p_node->SetToolTip("Increases the duration of the Time Manipulator tech.", "Master of Time");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTSLOWTIME));
        break;
    case PowerUpBoost1:
        p_node->SetToolTip("Gives a 1/3 chance to double the effect when you acquire extra pods or ship segments.", "High Roller");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTPOWERUPBOOST1));
        break;
    case PowerUpBoost2:
        p_node->SetToolTip("Increases the duration of Burning Pod and Time Manipulator.", "Neverending");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTPOWERUPBOOST2));
        break;
    case MegaPad:
        p_node->SetToolTip("Unlocks use of the Infi-Ship ability, enclosing the entire black hole with your ship. \nDuration: 8s\nCooldown: 20s", "The Chosen One");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTMEGAPAD));
        break;
    case StackableShield:
        p_node->SetToolTip("Allows you to collect several shield charges that activate as soon as previous charges are consumed.", "Multiple Shield Charges");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTSTACKABLESHIELD));
        break;
    case IncreaseStartPadSize:
        p_node->SetToolTip("Adds an extra segment to the mothership.", "Deluxe Version");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTINCREASESTARTPADSIZE));
        break;
    case Regenerate:
        p_node->SetToolTip("Start the level with an extra life.", "Sacrifice Crew");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTREGENERATE));
        break;
    case IncreaseStartPadSize2:
        p_node->SetToolTip("Adds an extra segment to the mothership.", "Deluxe Version");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTINCREASESTARTPADSIZE));
        break;
    case ChanceDoublePadSizeIncrease2:
        p_node->SetToolTip("Adds a 1/3 chance to get an additional ship segments when catching the ship segment tech.", "Skilled Engineer");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTCHANCETODOUBLEPADSIZEINCREASE));
        break;
    case GiantBall:
        p_node->SetToolTip("Unlocks use of the giant-pod ability. This ability doubles the size of all escape pods.\nDuration: 8s\nCooldown: 20s", "Bigger is Better");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTGIANTBALL));
        break;
    case MuliSpawn:
        p_node->SetToolTip("Gives a 1/3 chance to spawn an extra escape pod at the start of the level.", "Extra Funding");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTMULTISPAWN));
        break;
    case DoubleMultiBall:
        p_node->SetToolTip("Gives a 1/3 chance to get two pods instead of one when obtaining new escape pods.", "Reinforcements");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTMULTIBALL));
        break;
    case SuperTank:
        p_node->SetToolTip("Bouncing on hexagons will add some fuel to the tank.", "Fuel Collector");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTSUPERTANK));
        break;
    case DoubleMultiBall2:
        p_node->SetToolTip("Gives a 1/3 chance to get two pods instead of one when obtaining new escape pods.", "Reinforcements");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTMULTIBALL));
        break;
    case MultiSpawn2:
        p_node->SetToolTip("Gives a 1/3 chance to spawn an extra escape pod at the start of the level.", "Extra Funding");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTMULTISPAWN));
        break;
    case QuantumFuel:
        p_node->SetToolTip("Unlocks the Quantum Fuel ability. This is ability recharges the fuel of all escape pods.\nCooldown: 20s", "Quantum Fuel");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTQUANTUMFUEL));
        break;
    case DecreaseCD:
        p_node->SetToolTip("Lowers the cooldown on all abilities by 25%.", "Techmaster");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTDECREASECD));
        break;
    case MultiSpawn3:
        p_node->SetToolTip("Gives a 1/3 chance to spawn an extra escape pod at the start of the level.", "Extra Funding");
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTMULTISPAWN));
        break;
    case ShockWave:
        p_node->SetToolTip("Unlocks the Shockwave as an active ability. This ability pushes all the balls away from the black hole.\nCooldown: 20s", "Shockwave"); //////Cd time
        p_node->SetTexture(BOTextureManager::GetTexture(TEXTTSHOCKWAVE));
        break;
    }
}
void BOTechTreeManager::SetTechPoint(int p_numberOfLevels, bool p_fromSelect)
{
    m_maxTechPoints = p_numberOfLevels * 3;

    if (p_fromSelect == true)
    {
    m_techPointsLeft = m_maxTechPoints;
    }
    else
    {
        m_techPointsLeft += 3;
    }

    SetTechPointText();
}
void BOTechTreeManager::SetTechPointText()
{
    std::string temp = "Tech Points: " + std::to_string(m_techPointsLeft);
    m_techPointsText.SetText(temp, int3(255, 255, 255), 0);
    m_techPointsText.SetPosition(float2(m_windowSize.x - m_techPointsText.GetSize().x * 0.5f - 310, m_windowSize.y - m_techPointsText.GetSize().y*2 - m_techPointsText.GetSize().y * 0.5f));
}