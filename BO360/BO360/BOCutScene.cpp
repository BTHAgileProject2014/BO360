#include "BOCutScene.h"

BOCutScene::BOCutScene()
{

}

BOCutScene::~BOCutScene()
{

}

void BOCutScene::Initialize(int2 p_size)
{
    m_size = p_size;
    m_textIndex = 0;
    m_totalNumberOfTexts = 0;

    m_texts.clear();
    m_portraits.clear();
    m_descriptions.clear();

    BOButton button;
    button.Initialize(float2(p_size.x - 260.0f, 270.0f), int2(250, 75), BOTextureManager::GetTexture(TEXMENUBUTTON), "Next", CUTSCENENEXT, "");
    button.UseToolTip(false);
    m_buttonList.push_back(button);

    button.Initialize(float2(p_size.x - 260.0f, 355.0f), int2(250, 75), BOTextureManager::GetTexture(TEXMENUBUTTON), "Previous", CUTSCENEPREVIOUS, "");
    button.UseToolTip(false);
    m_buttonList.push_back(button);

    button.Initialize(float2(p_size.x - 260.0f, 815.0f), int2(250, 75), BOTextureManager::GetTexture(TEXMENUBUTTON), "Start Map", CUTSCENEPLAY, "");
    button.UseToolTip(false);
    m_buttonList.push_back(button);

    InitializeCutScene(m_size);

    BOPublisher::AddSubscriber(this);

    LoadPortraits();
    LoadDescriptions();
}

void BOCutScene::Shutdown()
{
    m_texts.clear();

    for (unsigned int i = 0; i < m_portraits.size(); i++)
    {
        BOGraphicInterface::DestroyTexture(m_portraits[i]);
    }
    m_portraits.clear();

    for (unsigned int i = 0; i < m_descriptions.size(); i++)
    {
        BOGraphicInterface::DestroyTexture(m_descriptions[i]);
    }
    m_descriptions.clear();
}

ButtonAction BOCutScene::Update()
{
    for (unsigned int i = 0; i < m_buttonList.size(); i++)
    {
        if (m_buttonList[i].Intersects(m_mousePosition))
        {
            if (m_mouseDown && !m_mousePrev)
            {
                m_mousePositionPrev = m_mousePosition;
            }

            if (!m_mouseDown && m_mousePrev)
            {
                if (m_buttonList[i].Intersects(m_mousePositionPrev))
                {
                    m_mousePrev = m_mouseDown;

                    if (m_buttonList[i].GetAction() == CUTSCENENEXT)
                    {
                        Next();
                    }

                    else if (m_buttonList[i].GetAction() == CUTSCENEPREVIOUS)
                    {
                        Previous();
                    }

                    else 
                    {
                        return m_buttonList[i].GetAction();
                    }
                }
            }
        }
    }

    m_mousePrev = m_mouseDown;

    return NOACTION;
}

void BOCutScene::Draw()
{
    m_background.Draw();

    m_speakerPortrait.Draw();

    m_textBackground.Draw();
    m_text.Draw();

    m_mapDescription.Draw();

    for (unsigned int i = 0; i < m_buttonList.size(); i++)
    {
        m_buttonList[i].Draw();
    }
}

void BOCutScene::LoadCutscene(int p_mapIndex)
{
    // Reset things.
    InitializeCutScene(m_size);

    m_texts.clear();
    m_textIndex = 0;
    m_totalNumberOfTexts = 0;

    std::ifstream file;
    std::string filename = "Cutscenes/Cutscene" + std::to_string(p_mapIndex);
    filename.append(".boc");
    file.open(filename);

    // Check to see if we found the file.
    if (!file.is_open())
    {
        std::cout << "Failed to load cutscene file!" << std::endl;
        std::cin.get();
    }

    // Read cutscene size data.
    if (file.good())
    {
        std::string line;
        int portrait = 0;

        while (!file.eof())
        {
            file >> portrait;
            std::getline(file, line);

            CutSceneText text;
            text.m_portraitIndex = portrait;
            text.m_text = line;

            m_texts.push_back(text);
        }
    }

    m_totalNumberOfTexts = m_texts.size();
    file.close();

    if (p_mapIndex < 4)
    {
        m_description = m_descriptions[p_mapIndex];
    }

    m_text.SetText(m_texts[0].m_text, int3(255, 255, 255), m_textBackground.GetSize().x - 10);
    m_speakerPortrait.SetSpritePointer(m_portraits[m_texts[0].m_portraitIndex]);

    m_text.SetPosition(float2(m_textPosition.x + m_text.GetSize().x / 2, m_textPosition.y + m_text.GetSize().y / 2));
}

void BOCutScene::Next()
{
    if (m_textIndex < m_totalNumberOfTexts - 1)
    {
        m_textIndex++;

        if (m_textIndex == m_totalNumberOfTexts - 1)
        {
            m_mapDescription.SetSpritePointer(m_description);
        }

        m_text.SetText(m_texts[m_textIndex].m_text, int3(255, 255, 255), m_textBackground.GetSize().x - 10);
        m_speakerPortrait.SetSpritePointer(m_portraits[m_texts[m_textIndex].m_portraitIndex]); 

        m_text.SetPosition(float2(m_textPosition.x + m_text.GetSize().x / 2, m_textPosition.y + m_text.GetSize().y / 2));
    }
}

void BOCutScene::Previous()
{
    if (m_textIndex > 0)
    {
        m_textIndex--;

        m_text.SetText(m_texts[m_textIndex].m_text, int3(255, 255, 255), m_textBackground.GetSize().x - 10);
        m_speakerPortrait.SetSpritePointer(m_portraits[m_texts[m_textIndex].m_portraitIndex]);

        m_text.SetPosition(float2(m_textPosition.x + m_text.GetSize().x / 2, m_textPosition.y + m_text.GetSize().y / 2));
    }
}

void BOCutScene::Handle(InputMessages p_inputMessages)
{
    m_mousePosition = int2(p_inputMessages.mouseX, p_inputMessages.mouseY);
    m_mouseDown = p_inputMessages.leftMouseKey;
}

void BOCutScene::LoadPortraits()
{
    m_portraits.push_back(BOGraphicInterface::LoadTexture("Sprites/Cutscenes/Portraits/None.png"));
    m_portraits.push_back(BOGraphicInterface::LoadTexture("Sprites/Cutscenes/Portraits/Captain.png"));
    m_portraits.push_back(BOGraphicInterface::LoadTexture("Sprites/Cutscenes/Portraits/Crewman.png"));
    m_portraits.push_back(BOGraphicInterface::LoadTexture("Sprites/Cutscenes/Portraits/Perry.png"));
    m_portraits.push_back(BOGraphicInterface::LoadTexture("Sprites/Cutscenes/Portraits/Navigator.png"));
}

void BOCutScene::LoadDescriptions()
{
    m_descriptions.push_back(BOGraphicInterface::LoadTexture("Sprites/Descriptions/Description0.png"));
    m_descriptions.push_back(BOGraphicInterface::LoadTexture("Sprites/Descriptions/Description1.png"));
    m_descriptions.push_back(BOGraphicInterface::LoadTexture("Sprites/Descriptions/Description2.png"));
    m_descriptions.push_back(BOGraphicInterface::LoadTexture("Sprites/Descriptions/Description3.png"));
}

void BOCutScene::InitializeCutScene(int2 p_size)
{
    m_background.Initialize(float2(0.0f, 0.0f), p_size, BOTextureManager::GetTexture(TEXCUTSCENETEXTBACKGROUND));
    m_speakerPortrait.Initialize(float2(10.0f, 10.0f), int2(250, 250), BOTextureManager::GetTexture(TEXCUTSCENETEXTFRAME));
    m_textBackground.Initialize(float2(260.0f, 10.0f), int2(p_size.x - 270, 250), BOTextureManager::GetTexture(TEXCUTSCENETEXTFRAME));
    m_mapDescription.Initialize(float2(10.0f, 270.0f), int2(p_size.x - 280, p_size.y - 280), BOTextureManager::GetTexture(TEXCUTSCENETEXTFRAME));

    m_textPosition = float2(m_textBackground.GetPosition().x + 10, m_textBackground.GetPosition().y + 10);
    m_text.Initialize(m_textPosition, " ", int3(255, 255, 255), 60, m_textBackground.GetSize().x - 10);

    m_background.SetPosition(float2(m_background.GetPosition().x + m_background.GetSize().x / 2, m_background.GetPosition().y + m_background.GetSize().y / 2));
    m_speakerPortrait.SetPosition(float2(m_speakerPortrait.GetPosition().x + m_speakerPortrait.GetSize().x / 2, m_speakerPortrait.GetPosition().y + m_speakerPortrait.GetSize().y / 2));
    m_textBackground.SetPosition(float2(m_textBackground.GetPosition().x + m_textBackground.GetSize().x / 2, m_textBackground.GetPosition().y + m_textBackground.GetSize().y / 2));
    m_mapDescription.SetPosition(float2(m_mapDescription.GetPosition().x + m_mapDescription.GetSize().x / 2, m_mapDescription.GetPosition().y + m_mapDescription.GetSize().y / 2));
}