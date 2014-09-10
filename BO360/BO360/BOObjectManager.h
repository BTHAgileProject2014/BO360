#ifndef BOOBJECTMANGAGER_H_
#define BOOBJECTMANGAGER_H_

#include "BOComponent.h"
#include "BOObject.h"
#include "BOBlackHole.h"
#include <vector>

class BOObjectManager :
	public BOComponent
{
public:
	BOObjectManager();
	~BOObjectManager();

	bool Initialize(int windowWidth, int windowHeight);
	void Shutdown();
	void Update();
	void Draw();

	//std::vector<BOObject> ObjectList;

private:
	BOBlackHole m_blackHole;
};

#endif