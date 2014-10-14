#ifndef BODRAWABLETEXT_H_
#define BODRAWABLETEXT_H_

#include "BOUtility.h"
#include "BOComponent.h"
#include "BOGraphicInterface.h"
#include <string>
#include <SDL.h>

class BODrawableText : public BOComponent
{
public:
	BODrawableText();
	~BODrawableText();

	bool Initialize(float2 p_position, std::string p_text, int3 p_color, int p_fontSize, int p_maxWidth);
	void Shutdown();
	void Draw();
	
	void SetText(std::string p_text, int3 p_color, int p_maxWidth);

	void SetPosition(float2 p_position);
	float2 GetPosition();

	int2 GetSize();

private:
	std::string m_text;
	SDL_Texture* m_texture;

	int2 m_size;
	float2 m_position;
	int m_fontSize;
    Uint8 m_opacity;
};
#endif

