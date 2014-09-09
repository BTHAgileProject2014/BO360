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
	int m_screenWidth;
	int m_screenHeight;
	bool m_fullscreen;
};
#endif

