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

    int2 m_Size = int2(50, 50);
    float2 midScreen = float2(m_windowSize.x * 0.5, m_windowSize.y * 0.5);//To save computation
    int diameter = 7;//Original is 7

    for (int y = diameter - 3, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x                 - x * m_Size.x, midScreen.y                     - (y + 6) * m_Size.y*0.5), m_Size);
    }
    for (int y = diameter - 2, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x      - x * m_Size.x, midScreen.y + m_Size.y * 0.5     - (y + 5) * m_Size.y*0.5), m_Size);
    }
    for (int y = diameter - 1, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 2  - x * m_Size.x, midScreen.y + m_Size.y * 1.5     - (y + 5) * m_Size.y*0.5), m_Size);
    }
    for (int y = diameter, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 2.5     - (y + 5) * m_Size.y*0.5), m_Size);
    }
    for (int y = diameter - 1, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 3       - (y + 5) * m_Size.y*0.5), m_Size);
    }
    for (int y = diameter - 2, x = 0; y != 0; y--, x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 3.5   - (y + 5) * m_Size.y*0.5), m_Size);
    }
    for (int y = diameter - 3, x = 0; y != 0; y-- ,x++)
    {
        BOTechTreeNode* newNode = CreateNode(float2(midScreen.x + m_Size.x * 3  - x * m_Size.x, midScreen.y + m_Size.y * 4     - (y + 5) * m_Size.y*0.5), m_Size);
    }

    MapNodes();
    SetLPE();

    return true;
}
void BOTechTreeManager::Update()
{
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Update();
    }
}
void BOTechTreeManager::Shutdown()
{
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Shutdown();
        delete m_nodeList[i];
        m_nodeList[i] = NULL;
    }
}
void BOTechTreeManager::Draw()
{
    for (int i = 0; i < m_nodeList.size(); i++)
    {
        m_nodeList[i]->Draw();
    }
}
BOTechTreeNode* BOTechTreeManager::CreateNode(float2 p_pos,int2 p_size)
{
    BOTechTreeNode* newNode = new BOTechTreeNode();
    newNode->Initialize(p_pos, p_size);
    m_nodeList.push_back(newNode);
    return newNode;
}
void BOTechTreeManager::MapNodes()
{
    
    for (int i = 0; i < m_nodeList.size() - 1; i++)
    {
        if (i != 3 && i != 8 && i != 14 && i != 21 && i != 27 && i != 32)
        {
            m_nodeList[i]->SetDownLeftNode(m_nodeList[i++]);
            m_nodeList[i++]->SetUpRightNode(m_nodeList[i]);
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
    SetNodeLPE(m_startNode, 0, 0, 0);
    BOTechTreeNode* node = m_nodeList[0];

    while (node->GetDownLeftNode() != NULL)
    {
        node->SetLayer(3);



        node = node->GetDownLeftNode();
    }


}
void BOTechTreeManager::SetNodeLPE(BOTechTreeNode* p_node, int p_layer, int p_price, int p_effect)
{
    p_node->SetLayer(p_layer);
    p_node->SetPrice(p_price);
    p_node->SetEffect(p_effect);
}