#ifndef BOLEVELMANAGER_H_
#define BOLEVELMANAGER_H_
#include "BOUtility.h"
#include "BOComponent.h"
#include "BOMapLoader.h"
#include <vector>

class BOLevelManager : public BOComponent
{
public:
	BOLevelManager();
	~BOLevelManager();

	bool Initialize();
	void Shutdown();

	void SetLevel(int p_indexLevel);
	int GetNextLevel();
	int GetCurrentLevel();

	int GetUnlockedLevels();
	void SetUnlockedLevels(int p_numberLevels);
	
private:
	std::vector<int> m_levelList;
	int m_currentLevel;
	int m_unlockedLevels;
};


#endif // !BOLEVELMANAGER_H_

