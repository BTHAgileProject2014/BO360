#ifndef BOHUDMANAGER_H_
#define BOHUDMANAGER_H_
#include "BOComponent.h"
#include "BODrawableText.h"
#include "BOObject.h"
#include "BOGraphicInterface.h"
#include "BOTextManager.h"
#include "BOHUDActionBar.h"
#include "BOSoundManager.h"

class BOHUDManager
{
public:
	BOHUDManager();
	~BOHUDManager();

	static bool Initialize();
	static void Shutdown();
	static void Draw();

	static void SetLives(int p_lives);
	static void SetScore(int p_score);
	static void SetLevel(int p_level);
	static void SetKeys(int p_keys, int p_maxKeys);
    static void SetShockwave(bool p_active);
    static void SetSlowtime(bool p_active);
    static void ModifyState(bool p_lives, bool p_score, bool p_level, bool p_keys);
    static void ActionBarButtonCanUse(ActionBarButton p_button, bool p_canUse);
    static void ActionBarButtonEnabled(ActionBarButton p_button, bool p_enabled);

private:
	static float2 m_livesAnchor;
	static BODrawableText m_lives;
	static BOObject m_life;
	static int m_noLives;
	static bool m_livesEnabled;

	static float2 m_scoreAnchor;
	static BODrawableText m_score;
	static bool m_scoreEnabled;

	static float2 m_levelAnchor;
	static BODrawableText m_level;
	static bool m_levelEnabled;

	static float2 m_keyAnchor;
	static BOObject m_keySprite;
	static BODrawableText m_keyText;
	static bool m_keyEnabled;

    static BOHUDActionBar m_actionBar;
};
#endif