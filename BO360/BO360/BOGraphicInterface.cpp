#include "BOGraphicInterface.h"


BOGraphicInterface::BOGraphicInterface()
{
	m_window = 0;
	m_windowWidth = 800;
	m_windowHeight = 600;
	//m_fullscreen = false;		// Make use of this later if we reach fullscreen support

}


BOGraphicInterface::~BOGraphicInterface()
{
}

bool BOGraphicInterface::Initialize()
{
	bool result;

	m_window = new BOWindow;
	if (!m_window)
	{
		// Pointer failed
		return false;
	}

	result = m_window->Initialize("ScreenName", m_windowWidth, m_windowHeight);
	if (!result)
	{
		// Initialize failed
		return false;
	}
	
	return true;
}

void BOGraphicInterface::Shutdown()
{
	m_window->Shutdown();
	delete m_window;
	m_window = 0;
}

void BOGraphicInterface::Draw()
{

}

void BOGraphicInterface::Clear()
{

}

void BOGraphicInterface::Present()
{

}