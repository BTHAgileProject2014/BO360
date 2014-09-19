#include "BOButton.h"

BOButton::BOButton()
{

}

BOButton::~BOButton()
{

}

bool BOButton::Initialize(float2 p_position, int2 p_size, std::string p_fileName, std::string p_name, int p_action)
{
	m_actionValue = p_action;
	m_position = p_position;
	m_size = p_size;
	m_name = p_name;

	// Load non highlighted texture.
	std::string l_nonLitName = p_fileName;
	l_nonLitName.append(".png");
	m_nonHighlighted = BOGraphicInterface::LoadTexture(l_nonLitName);
	if (!m_nonHighlighted)
	{
		std::cout << "Failed to load texture " << l_nonLitName << "!" << std::endl;
		return false;
	}

	// Load highlighted texture.
	std::string l_LitName = p_fileName;
	l_LitName.append("Highlighted.png");
	m_highlighted = BOGraphicInterface::LoadTexture(l_LitName);
	if (!m_highlighted)
	{
		std::cout << "Failed to load texture " << l_LitName << "!" << std::endl;
		return false;
	}

	// Load tool tip.
	std::string l_ToolName = p_fileName;
	l_ToolName.append("ToolTip.png");
	if (m_toolTip.Initialize(float2(m_position.x + 250, m_position.y + 220), int2(500, 300), l_ToolName))
	{
		std::cout << "Failed to load tool tip " << l_ToolName << "!" << std::endl;
		return false;
	}

	// Set default sprite to the nonhighlit.
	m_sprite = m_nonHighlighted;
	m_lit = false;

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
	}
}

int BOButton::GetAction()
{
	return m_actionValue;
}

void BOButton::Shutdown()
{
	if (m_sprite)
	{
		BOGraphicInterface::DestroyTexture(m_sprite);
	}
}