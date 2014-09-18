#ifndef BOMULTIBALLS_H_
#define BOMULTIBALLS_H_

#include "BOObject.h"
#include "BOPowerUp.h"

class BOMultiballs : BOPowerUp
{
public:
	BOMultiballs();
	~BOMultiballs();
	bool Initialize();
	int Update();
	void Draw();

	void SetActive(bool p_isActive);
	void SwitchActive();
	bool GetActive();

	void Active();
	void Deactivate();

private:
	bool m_isActive;
};
#endif // !BOMULTIBALLS_H_
