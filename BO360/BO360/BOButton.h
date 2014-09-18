#ifndef BOBUTTON_H_
#define BOBUTTON_H_

#include "BOObject.h"
#include "BOPhysics.h"

class BOButton : public BOObject
{
public:
	BOButton();
	~BOButton();

	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, int p_action);
	void Shutdown();

	bool Intersects(int2 p_mousePosition);
	void Draw();

	int GetAction();

private:
	int m_actionValue;
	bool m_lit;

	SDL_Texture* m_nonHighlighted;
	SDL_Texture* m_highlighted;

	BOObject m_toolTip;
};
#endif