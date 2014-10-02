#ifndef BOSCORE_H_
#define BOSCORE_H_
#include "BOComponent.h"
#include "BOHUDManager.h"

class BOScore
{
public:
	BOScore();
	~BOScore();

	static bool Initialize();
	static void Shutdown();

	static void AddScore(int p_amount);
	static void SetScore(int p_score);

	static void ResetScore();
	static int GetScore();

private:
	static int m_score;
};
#endif
