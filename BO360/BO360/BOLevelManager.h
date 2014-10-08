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

	std::vector<int> m_levelList;
private:
	int m_currentLevel;
};


#endif // !BOLEVELMANAGER_H_

