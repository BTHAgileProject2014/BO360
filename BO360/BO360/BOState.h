#ifndef BOSTATE_H_
#define BOSTATE_H_

#include "BOButton.h"
#include "BOObject.h"
#include "BOSubscriber.h"
#include "BOPublisher.h"
#include "BOTextManager.h"
#include "BODrawableText.h"
#include <vector>

class BOState : public BOSubscriber
{
public:
	BOState();
	~BOState();
	
	bool Initialize(float2 p_position, int2 p_size, float2 p_menuPosition, std::string p_name, std::string p_backgroundFil);
	void Shutdown();
	ButtonAction Update();
	void Draw();

	void Handle(InputMessages p_inputMessages);

	void AddButton(float2 p_position, int2 p_size, float2 p_menuPosition, std::string p_fileName, std::string p_name, ButtonAction p_action);
	void SetName(std::string p_name);
	void SetBackground(std::string p_fileName);

private:
	std::vector<BOButton> m_buttonList;

	float2 m_position;
	int2 m_screenSize;
	std::string m_name;

	int2 m_mousePosition;
	bool m_mouseDown;

	BOObject m_background;
	std::vector<BOObject> m_menuBar;

	BODrawableText m_menuText;
};
#endif