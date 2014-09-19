#ifndef BOHUDMANAGER_H_
#define BOHUDMANAGER_H_
#include "BOComponent.h"
#include "BODrawableText.h"
#include "BOObject.h"
#include "BOGraphicInterface.h"

class BOHUDManager
{
public:
	BOHUDManager();
	~BOHUDManager();
	static bool Initialize(bool p_enabled);
	static void Shutdown();
	static void Draw();
	static void SetLives(int p_lives);
	static void SetScore(int p_score);
	static void SetLevel(int p_level);
	static void ModifyState(bool p_lives, bool p_score, bool p_levels);
	static void EnableHud(bool p_enable);

private:
	static bool m_livesEnabled;
	static bool m_scoreEnabled;
	static bool m_levelsEnabled;
	static bool m_hudEnabled;
	static BODrawableText m_lives;
	static BODrawableText m_score;
	static BODrawableText m_level;
	static BOObject m_life;
	static int m_noLives;
	static float2 m_livesAnchor;
	static float2 m_scoreAnchor;
	static float2 m_levelAnchor;
};
#endif