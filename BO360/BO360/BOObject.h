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

    double GetRotation();
    void SetRotation(double p_rotation);

	SDL_Texture* GetSprite();
	void SetSprite(Textures p_spriteIndex);

	virtual sphere GetBoundingSphere() const;

    Uint8 GetOpacity()const;
    void SetOpacity(Uint8 p_opacity);

	void SetScale(float p_scale);

protected:
	float2 m_position;
	int2 m_size;
    double m_rotation;
	SDL_Texture* m_sprite;
	float m_radius;
	float m_scale;
    Uint8 m_opacity;
};
#endif