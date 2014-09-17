#ifndef BOSTATE_H_
#define BOSTATE_H_

#include "BOObject.h"
#include "BOButton.h"
#include <vector>

class BOState : public BOObject
{
public:
	BOState();
	~BOState();

	int CheckAction();
	void ClearAction();

private:
	std::vector<BOButton> m_buttonList;
	bool m_actionToReport;
	int m_action;
};
#endif