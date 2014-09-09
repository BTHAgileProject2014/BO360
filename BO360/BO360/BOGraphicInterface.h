#ifndef BOGRAPHICINTERFACE_H_
#define BOGRAPHICINTERFACE_H_

#include "BOWindow.h"
#include "BOComponent.h"

class BOGraphicInterface : public BOComponent
{
public:
	BOGraphicInterface();
	~BOGraphicInterface();

	bool Initialize();
	void Shutdown();
	void Draw();
	void Clear();
	void Present();

private:
	BOWindow* m_window;
	int m_windowWidth;
	int m_windowHeight;
	//bool m_fullscreen;	// Use only when fullscreen and resolutions is supported
};
#endif

