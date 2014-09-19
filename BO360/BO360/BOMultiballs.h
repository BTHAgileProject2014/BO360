#ifndef BOMULTIBALLS_H_
#define BOMULTIBALLS_H_

#include "BOObject.h"
#include "BOPowerUp.h"
#include "BOPowerUpManager.h"

class BOMultiballs : public BOPowerUp
{
public:
	BOMultiballs();
	~BOMultiballs();

	void SetActive(bool p_isActive);
	void SwitchActive();
	bool GetActive();

	void Activate();
	void Deactivate();

private:
	bool m_isActive;
};
#endif // !BOMULTIBALLS_H_
