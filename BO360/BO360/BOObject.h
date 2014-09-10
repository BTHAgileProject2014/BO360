#ifndef BOOBJECT_H_
#define BOOBJECT_H_

#include "BOUtility.h"
#include <SDL.h>
#include <string>

class BOObject
{
public:
	BOObject();
	~BOObject();

	virtual bool Initialize(float2 p_position, int2 p_size, std::string p_fileName);
	virtual void Shutdown();

	float2 GetPosition();
	void SetPosition(float2 p_position);

	int2 GetSize();
	void SetSize(int2 p_size);

	SDL_Surface* GetSprite();
	void SetSprite(std::string p_fileName);

	void Draw();

protected:
	float2 m_position;
	int2 m_size;
	SDL_Surface* m_sprite;
};
#endif