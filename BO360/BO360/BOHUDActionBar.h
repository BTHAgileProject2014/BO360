#ifndef BOHUDACTIONBAR_H_
#define BOHUDACTIONBAR_H_

#include "BOHUDActionBarButton.h"
#include "BOGraphicInterface.h"
#include "BOTextureManager.h"

class BOHUDActionBar
{
public:
    BOHUDActionBar();
    ~BOHUDActionBar();

    bool Initialize(float2 p_position);
    void Shutdown();
    void Draw();

private:
    BOHUDActionBarButton m_actionBarButtons[6];


};
#endif // !BOHUDACTIONBAR
