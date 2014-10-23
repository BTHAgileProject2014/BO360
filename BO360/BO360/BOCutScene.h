#ifndef BOCUTSCENE_H_
#define BOCUTSCENE_H_

#include "BOButton.h"
#include "BOObject.h"
#include "BOSubscriber.h"
#include "BOPublisher.h"
#include "BODrawableText.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class BOCutScene : public BOSubscriber
{
public:
    BOCutScene();
    ~BOCutScene();

    void Initialize(int2 p_size);
    void Shutdown();

    ButtonAction Update();
    void Handle(InputMessages p_inputMessages);
    void Draw();

    void LoadCutscene(int p_mapIndex);

private:
    struct CutSceneText
    {
        std::string m_text;
        int m_portraitIndex;
    };

    void Next();
    void Previous();
    void LoadPortraits();
    void LoadDescriptions();
    void InitializeCutScene(int2 p_size);

    int m_textIndex;
    int m_totalNumberOfTexts;

    std::vector<CutSceneText> m_texts;
    std::vector<SDL_Texture*> m_portraits;
    std::vector<SDL_Texture*> m_descriptions;

    std::vector<BOButton> m_buttonList;

    BOObject m_background;
    BOObject m_speakerPortrait;
    BOObject m_textBackground;

    SDL_Texture* m_description;
    BOObject m_mapDescription;

    float2 m_textPosition;

    BODrawableText m_text;

    int2 m_mousePosition;
    int2 m_mousePositionPrev;
    bool m_mouseDown;
    bool m_mousePrev;

    int2 m_size;
};
#endif;