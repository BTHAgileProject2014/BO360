#ifndef BOOBJECT_H_
#define BOOBJECT_H_

#include "BOUtility.h"
#include "BOGraphicInterface.h"
#include "BOTextureManager.h"
#include <SDL.h>
#include <string>

class BOObject : BOComponent
{
public:
	BOObject();
	virtual ~BOObject();

	virtual bool Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite);
    virtual bool Initialize(float2 p_position, int2 p_size, float scale, SDL_Texture* p_sprite);
	virtual void Shutdown();
	virtual void Draw();

	float2 GetPosition() const;
	virtual void SetPosition(float2 p_position);

	int2 GetSize();
	void SetSize(int2 p_size);

	SDL_Texture* GetSprite();
	void SetSprite(Textures p_spriteIndex);

	sphere GetBoundingSphere() const;

protected:
	float2 m_position;
	int2 m_size;
	SDL_Texture* m_sprite;
	float m_radius;
	float m_scale;
};
#endif