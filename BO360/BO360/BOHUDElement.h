#ifndef HUDELEMENT_H_
#define HUDELEMENT_H_

#include "BOUtility.h"
#include "BOComponent.h"


enum HUDAnchor
{
    HUDANCHOR_CENTER,
    HUDANCHOR_TOP,
    HUDANCHOR_LEFT,
    HUDANCHOR_BOTTOM,
    HUDANCHOR_RIGHT,
    HUDANCHOR_TOPLEFT,
    HUDANCHOR_TOPRIGHT,
    HUDANCHOR_BOTTOMLEFT,
    HUDANCHOR_BOTTOMRIGHT
};

class BOHUDElement : public BOComponent
{
public:
    BOHUDElement();
    ~BOHUDElement();

    bool Initialize(float2 p_position, int2 p_size, HUDAnchor p_anchor);
    void Shutdown();

    virtual void SetRelativePosition(HUDAnchor p_anchor);
    void EnableElement(bool p_enable);
    int2 GetSize()const;
    virtual void SetPosition(float2 p_position);
    float2 GetPosition()const;

protected:
    float2 m_position;
    float2 m_relativePosition;
    int2 m_size;
    HUDAnchor m_anchor;
    bool m_enabled;
};
#endif // !HUDELEMENT_H_
