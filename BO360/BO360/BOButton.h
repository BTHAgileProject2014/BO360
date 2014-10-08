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

	bool Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, std::string p_name, ButtonAction p_action, std::string p_tooltip);
	void Shutdown();

	bool Intersects(int2 p_mousePosition);
	void Draw();

	ButtonAction GetAction();
	void SetAction(ButtonAction p_action);

private:
	ButtonAction m_action;
	bool m_lit;
	std::string m_name;

	SDL_Texture* m_nonHighlighted;
	SDL_Texture* m_highlighted;

	BOObject m_toolTip;

	BODrawableText m_buttonText;
	BODrawableText m_buttonTextLit;
	BODrawableText m_buttonTooltipText;
};
#endif