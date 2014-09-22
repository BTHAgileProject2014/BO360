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

	void SwitchActive();

	void Activate();
	void Deactivate();

private:
	bool m_isActive;
};
#endif // !BOMULTIBALLS_H_
