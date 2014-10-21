#ifndef BOHUDTEXT_H_
#define BOHUDTEXT_H_

#include "BOHUDElement.h"
#include "BODrawableText.h"

class BOHUDText : public BOHUDElement
{
public:
    BOHUDText();
    ~BOHUDText();

    bool Initialize(float2 p_position, HUDAnchor p_anchor, std::string p_text, int3 p_color, int p_fontSize, int p_maxWidth);
    void Shutdown();

    void Draw();

    void SetText(std::string p_text, int3 p_color, int p_maxWidth);
    void SetPosition(float2 p_position);

private:
    BODrawableText m_text;
};
#endif // !BOHUDTEXT_H_
