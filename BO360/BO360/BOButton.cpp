#include "BOButton.h"

BOButton::BOButton()
{

}

BOButton::~BOButton()
{

}

bool BOButton::Initialize(float2 p_position, int2 p_size, SDL_Texture* p_sprite, std::string p_name, ButtonAction p_action, std::string p_tooltip)
{
	m_action = p_action;
	m_position = p_position;
	m_size = p_size;
	m_name = p_name;

	// Load non highlighted texture.
	m_nonHighlighted = BOTextureManager::GetTexture(TEXMENUBUTTON);
	if (!m_nonHighlighted)
	{
		std::cout << "Failed to load texture " << "TEXMENUBUTTON" << "!" << std::endl;
		return false;
	}

	// Load highlighted texture.
	m_highlighted = BOTextureManager::GetTexture(TEXMENUBUTTONHL);
	if (!m_highlighted)
	{
		std::cout << "Failed to load texture " << "TEXMENUBUTTONHL" << "!" << std::endl;
		return false;
	}

	// Load tool tip.
	if (!m_toolTip.Initialize(float2(m_position.x + 125, m_position.y + 222.5f), int2(250, 295), BOTextureManager::GetTexture(TEXTOOLTIP)))
	{
		std::cout << "Failed to load tool tip " << "TEXTOOLTIP" << "!" << std::endl;
		return false;
	}

	// Load tooltip text
	if (!m_buttonTooltipText.Initialize(float2(0,0),p_tooltip, int3(0, 148, 255), 40, 242))
	{
		std::cout << "Failed to create button text tooltip in " << m_name << "!" << std::endl;
		return false;
	}

	// Set correct position of tooltip text
	int2 tempSize = m_buttonTooltipText.GetSize();
	float2 tempPos = float2(8 + m_position.x + tempSize.x / 2, 84 + m_position.y + tempSize.y / 2);
	m_buttonTooltipText.SetPosition(tempPos);

	// Set default sprite to the nonhighlit.
	m_sprite = m_nonHighlighted;
	m_lit = false;

	// Calculate button text position
	tempPos = float2(p_position.x + p_size.x / 2, p_position.y + p_size.y / 2);

	// Load button texts
	if (!m_buttonText.Initialize(tempPos, m_name, int3(0, 148, 255), 44,0))
	{
		std::cout << "Failed to create button text in " << m_name << "!" << std::endl;
		return false;
	}

	if (!m_buttonTextLit.Initialize(tempPos, m_name, int3(255, 255, 255), 44,0))
	{
		std::cout << "Failed to create button text (lit) in " << m_name << "!" << std::endl;
		return false;
	}

	return true;
}

bool BOButton::Intersects(int2 p_mousePosition)
{
	// Intersection test.
	if (BOPhysics::CheckCollisionPointToBox(p_mousePosition, box(m_position, m_size)))
	{
		// Hightlight button and return true;
		m_sprite = m_highlighted;
		m_lit = true;
		return true;
	}

	// Texture the button normaly and return false;
	m_sprite = m_nonHighlighted;
	m_lit = false;
	return false;
}

void BOButton::Draw()
{
	BOGraphicInterface::Draw(m_sprite, float2(m_position.x + (m_size.x / 2), m_position.y + (m_size.y / 2)), m_size);

	// Draw tool tip if selected.
	if (m_lit)
	{
		m_toolTip.Draw();
		m_buttonTextLit.Draw();
		m_buttonTooltipText.Draw();
	}
	else
	{
		m_buttonText.Draw();
	}
}

ButtonAction BOButton::GetAction()
{
	return m_action;
}

void BOButton::Shutdown()
{
	m_buttonText.Shutdown();
	m_buttonTextLit.Shutdown();
	m_buttonTooltipText.Shutdown();
}