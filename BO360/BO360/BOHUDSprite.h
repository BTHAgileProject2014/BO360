#ifndef BOHUDSPRITE_H_
#define BOHUDSPRITE_H_

#include "BOHUDElement.h"
#include "BOObject.h"

class BOHUDSprite : public BOHUDElement
{
public:
    BOHUDSprite();
    ~BOHUDSprite();

    bool Initialize(float2 p_position, HUDAnchor p_anchor, int2 p_size, SDL_Texture* p_sprite);
    void Shutdown();

    void Draw();

    void SetPosition(float2 p_position);
    void SetRelativePosition(HUDAnchor p_anchor);

private:
    BOObject m_sprite;
};

#endif