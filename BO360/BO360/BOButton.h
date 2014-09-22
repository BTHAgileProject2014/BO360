#ifndef BOBUTTON_H_
#define BOBUTTON_H_

#include "BOObject.h"
#include "BOPhysics.h"
#include "BODrawableText.h"

class BOButton : public BOObject
{
public:
	BOButton();
	~BOButton();

	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName, std::string p_name, ButtonAction p_action);
	void Shutdown();

	bool Intersects(int2 p_mousePosition);
	void Draw();

	ButtonAction GetAction();

private:
	ButtonAction m_action;
	bool m_lit;
	std::string m_name;

	SDL_Texture* m_nonHighlighted;
	SDL_Texture* m_highlighted;

	BOObject m_toolTip;

	BODrawableText m_buttonText;
	BODrawableText m_buttonTextLit;
};
#endif