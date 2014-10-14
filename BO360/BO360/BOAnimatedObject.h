#ifndef BOANIMATEDOBJECT_H_
#define BOANIMATEDOBJECT_H_

#include "BOObject.h"

class BOAnimatedObject : public BOObject
{
public:
	BOAnimatedObject();
	virtual ~BOAnimatedObject();

	virtual bool Initialize(float2 p_position, int2 p_size, int2 p_sourceSize, int p_frame, int p_maxFrames, double p_timePerFrame, bool p_hardReset, SDL_Texture* p_sprite);
    virtual void Animate(double p_deltaTime);
	virtual void MoveFrame(int p_frames);
	virtual void Draw();

	int2 GetSourceSize();
	void SetSourceSize(int2 p_sourceSize);

	int GetFrame();
	void SetFrame(int p_frame);

    bool Alive();
    void Kill();

protected:
	int2 m_sourceSize;
	int m_frame;
	int m_numberOfFrames;
	double m_timePerFrame;
	double m_timePassed;
	bool m_hardReset;
	bool m_increment;
    bool m_alive;
};
#endif
