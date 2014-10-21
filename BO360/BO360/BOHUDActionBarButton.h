#ifndef BOHUDACTIONBARBUTTON_H_
#define BOHUDACTIONBARBUTTON_H_

#include "BODrawableText.h"
#include "BOTextureManager.h"
#include "BOObject.h"

class BOHUDActionBarButton
{
public:
    BOHUDActionBarButton();
    ~BOHUDActionBarButton();

    bool Initialize(float2 p_position, SDL_Texture* p_sprite, int2 p_size, std::string p_hotkey);
    void Shutdown();
    void Draw();

    void SetEnabled(bool p_enabled);
    void CanUse(bool p_canUse);

private:
    BOObject m_button;
    BOObject m_background;
    BODrawableText m_buttonText;
    bool m_enabled;
    bool m_canUse;
};

#endif // !BOHUDACTIONBARBUTTON_H_
