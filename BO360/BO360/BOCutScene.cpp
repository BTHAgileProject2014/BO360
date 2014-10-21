#include "BOCutScene.h"

BOCutScene::BOCutScene()
{

}

BOCutScene::~BOCutScene()
{

}

void BOCutScene::Initialize(int2 p_size)
{
    m_textIndex = 0;
    m_totalNumberOfTexts = 0;

    m_texts.clear();
    m_portraits.clear();
    m_discriptions.clear();

    m_nextButton.Initialize(float2(p_size.x - 260.0f, 270.0f), int2(250, 75), BOTextureManager::GetTexture(TEXMENUBUTTON), "Next", NOACTION, "");
    m_nextButton.UseToolTip(false);

    m_playButton.Initialize(float2(p_size.x - 260.0f, 815.0f), int2(250, 75), BOTextureManager::GetTexture(TEXMENUBUTTON), "Start Map", CUTSCENEPLAY, "");
    m_playButton.UseToolTip(false);

    m_speakerPortrait.Initialize(float2(10.0f, 10.0f), int2(250, 250), BOTextureManager::GetTexture(TEXCUTSCENETEXTBACKGROUND));
    m_textBackground.Initialize(float2(260.0f, 10.0f), int2(p_size.x - 270, 250), BOTextureManager::GetTexture(TEXCUTSCENETEXTBACKGROUND));
    m_mapDescription.Initialize(float2(10.0f, 270.0f), int2(p_size.x - 280, p_size.y - 280), BOTextureManager::GetTexture(TEXCUTSCENETEXTBACKGROUND));

    m_text.Initialize(float2(m_textBackground.GetPosition().x + 10, m_textBackground.GetPosition().y + 10), "Initialized text.", int3(255, 255, 255), 30, m_textBackground.GetSize().x - 10);

    BOPublisher::AddSubscriber(this);

    LoadPortraits();
}

void BOCutScene::Shutdown()
{
    m_texts.clear();

    for (unsigned int i = 0; i < m_portraits.size(); i++)
    {
        BOGraphicInterface::DestroyTexture(m_portraits[i]);
    }
    m_portraits.clear();

    for (unsigned int i = 0; i < m_discriptions.size(); i++)
    {
        BOGraphicInterface::DestroyTexture(m_discriptions[i]);
    }
    m_discriptions.clear();
}

ButtonAction BOCutScene::Update()
{
    ButtonAction action = NOACTION;

        if (m_mouseDown && !m_mousePrev)
        {
            m_mousePositionPrev = m_mousePosition;
        }

        if (!m_mouseDown && m_mousePrev)
        {
            if (m_textsLeft && m_nextButton.Intersects(m_mousePositionPrev))
            {
                m_mousePrev = m_mouseDown;

                Next();

                action = NOACTION;
            }

            else if (m_playButton.Intersects(m_mousePositionPrev))
            {
                m_mousePrev = m_mouseDown;

                action = CUTSCENEPLAY;
            }
        }

        m_mousePrev = m_mouseDown;

        return action;
}

void BOCutScene::Draw()
{
    m_speakerPortrait.Draw();

    m_textBackground.Draw();
    m_text.Draw();

    m_mapDescription.Draw();

    m_nextButton.Draw();
    m_playButton.Draw();
}

void BOCutScene::LoadCutscene(int p_mapIndex)
{
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

            m_totalNumberOfTexts++;
        }
    }

    file.close();

    m_text.SetText(m_texts[m_textIndex].m_text, int3(255, 255, 255), 30);
    m_speakerPortrait.SetSpritePointer(m_portraits[m_texts[m_textIndex].m_portraitIndex]);
}

void BOCutScene::Next()
{
    if (m_textsLeft)
    {
        m_textIndex++;

        m_text.SetText(m_texts[m_textIndex].m_text, int3(255, 255, 255), 30);
        m_speakerPortrait.SetSpritePointer(m_portraits[m_texts[m_textIndex].m_portraitIndex]);
    }
}

void BOCutScene::Handle(InputMessages p_inputMessages)
{
    m_mousePosition = int2(p_inputMessages.mouseX, p_inputMessages.mouseY);
    m_mouseDown = p_inputMessages.leftMouseKey;
}

void BOCutScene::LoadPortraits()
{
    m_portraits.push_back(BOGraphicInterface::LoadTexture("Sprites/Portraits/Captain.png"));
    m_portraits.push_back(BOGraphicInterface::LoadTexture("Sprites/Portraits/Crewman.png"));
}