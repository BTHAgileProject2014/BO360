#ifndef BOHUDACTIONBAR_H_
#define BOHUDACTIONBAR_H_

#include "BOHUDActionBarButton.h"
#include "BOGraphicInterface.h"
#include "BOTextureManager.h"

enum ActionBarButton
{
    ABB_SHOCKWAVE,
    ABB_SLOWTIME,
    ABB_GIANTBALL,
    ABB_MEGAPAD,
    ABB_QUANTUMFUEL,
    
    ABB_NROFBUTTONS
};

class BOHUDActionBar
{

public:
    BOHUDActionBar();
    ~BOHUDActionBar();

    bool Initialize(float2 p_position);
    void Shutdown();
    void Draw();

    void CanUse(bool p_canUse, ActionBarButton p_button);
    void Enable(bool p_enable, ActionBarButton p_button);

private:
    BOHUDActionBarButton m_actionBarButtons[ABB_NROFBUTTONS];


};
#endif // !BOHUDACTIONBAR
