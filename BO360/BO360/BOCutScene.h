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
    void LoadPortraits();

    int m_textIndex;
    int m_totalNumberOfTexts;
    bool m_textsLeft;

    std::vector<CutSceneText> m_texts;
    std::vector<SDL_Texture*> m_portraits;
    std::vector<SDL_Texture*> m_discriptions;

    BOButton m_nextButton;
    BOButton m_playButton;

    BOObject m_speakerPortrait;
    BOObject m_textBackground;
    BOObject m_mapDescription;

    BODrawableText m_text;

    int2 m_mousePosition;
    int2 m_mousePositionPrev;
    bool m_mouseDown;
    bool m_mousePrev;
};
#endif;