#ifndef BOSTATE_H_
#define BOSTATE_H_

#include "BOButton.h"
#include "BOObject.h"
#include "BOSubscriber.h"
#include "BOPublisher.h"
#include <vector>

class BOState : public BOSubscriber
{
public:
	BOState();
	~BOState();
	
	bool Initialize(float2 p_position, int2 p_size, std::string p_name, std::string p_backgroundFil);
	void Shutdown();
	int Update();
	void Draw();

	void Handle(InputMessages p_inputMessages);

	void AddButton(float2 p_position, int2 p_size, std::string p_fileName, int p_action);
	void SetName(std::string p_name);
	void SetBackground(std::string p_fileName);

private:
	std::vector<BOButton> m_buttonList;
	int m_action;

	float2 m_position;
	int2 m_screenSize;
	std::string m_name;

	int2 m_mousePosition;
	bool m_mouseDown;

	BOObject m_background;
	std::vector<BOObject> m_menuBar;
};
#endif