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

	void SelectLevel(int p_indexLevel);

	std::vector<int> m_levelList;
};


#endif // !BOLEVELMANAGER_H_

