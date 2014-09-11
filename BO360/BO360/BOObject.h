#ifndef BOOBJECT_H_
#define BOOBJECT_H_

#include "BOUtility.h"
#include "BOGraphicInterface.h"
#include <SDL.h>
#include <string>

class BOObject : BOComponent
{
public:
	BOObject();
	~BOObject();

	virtual bool Initialize(float2 p_position, int2 p_size, std::string p_fileName);
	virtual void Shutdown();
	virtual void Draw();

	float2 GetPosition();
	void SetPosition(float2 p_position);

	int2 GetSize();
	void SetSize(int2 p_size);

	SDL_Texture* GetSprite();
	void SetSprite(std::string p_fileName);

	sphere GetBoundingSphere();

protected:
	float2 m_position;
	int2 m_size;
	SDL_Texture* m_sprite;
};
#endif