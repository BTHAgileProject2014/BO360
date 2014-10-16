#ifndef BOINPUT_H_
#define BOINPUT_H_

#include "BOComponent.h"
#include "SDL.h"
#include "BOPublisher.h"
#include "BOUtility.h"

// To keep track of key indexes in a reasonable way
enum BOInputKey
{
	BOInput_Up,
	BOInput_Down,
	BOInput_Left,
	BOInput_Right,
	BOInput_Space,
	BOInput_Enter,
	BOInput_M1,
	BOInput_M2,
	BOInput_z,
	BOInput_x,
	BOInput_f,
	BOInput_t,
	BOInput_g,
	BOInput_h,
	BOInput_j,
	LAST_OF_BOINPUT
};

class BOInput : BOComponent
{
public:
	BOInput();
	~BOInput();

	bool Initialize();
	void Shutdown();

	// Handles SDL_Events
	bool Update();

private:
	BOPublisher m_publisher;
	bool m_buttonsPressed[LAST_OF_BOINPUT];
};
#endif