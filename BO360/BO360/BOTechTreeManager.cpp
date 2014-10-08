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
/*
    m_startNode = CreateNode(float2(m_windowSize.x / 2.0f, m_windowSize.y / 2.0f), 0, 0, 0);

    
    BOTechTreeNode* newNode1 = CreateNode(float2(m_startNode->GetPosition().x + 0 , m_startNode->GetPosition().y - 44), 1, 1, 0);

    BOTechTreeNode* newNode2 = CreateNode(float2(m_startNode->GetPosition().x + 39, m_startNode->GetPosition().y - 22), 1, 1, 0);
    BOTechTreeNode* newNode3 = CreateNode(float2(m_startNode->GetPosition().x + 39, m_startNode->GetPosition().y + 22), 1, 1, 0);
    BOTechTreeNode* newNode4 = CreateNode(float2(m_startNode->GetPosition().x + 0 , m_startNode->GetPosition().y + 44), 1, 1, 0);
    BOTechTreeNode* newNode5 = CreateNode(float2(m_startNode->GetPosition().x - 39, m_startNode->GetPosition().y + 22), 1, 1, 0);
    BOTechTreeNode* newNode6 = CreateNode(float2(m_startNode->GetPosition().x - 39, m_startNode->GetPosition().y - 22), 1, 1, 0);

    */
    int2 m_Size = int2(50, 50);
    //m_startNode = CreateNode(float2(m_windowSize.x / 2.0f, m_windowSize.y / 2.0f), 0, 0, 0);

    int x = 0;
    for (int y = 4; y != 0; y--)
    {
        BOTechTreeNode* newNode = CreateNode(float2(m_windowSize.x * 0.5 - (x * 2) * 25, m_windowSize.y * 0.5 - (y + 6) * 25), m_Size, 3, 6, 0);
        x++;
    }
    x = 0;
    for (int y = 5; y != 0; y--)
    {
        BOTechTreeNode* newNode = CreateNode(float2(m_windowSize.x * 0.5 + 50 - (x * 2) * 25, m_windowSize.y * 0.5 + 35 - (y + 5) * 25), m_Size, 3, 6, 0);
        x++;
    }
    x = 0;









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
BOTechTreeNode* BOTechTreeManager::CreateNode(float2 p_pos,int2 p_size, int p_layer, int p_price, int p_effect)
{
    BOTechTreeNode* newNode = new BOTechTreeNode();
    newNode->Initialize(p_pos, p_size, p_layer, p_price, p_effect);
    m_nodeList.push_back(newNode);
    return newNode;
}