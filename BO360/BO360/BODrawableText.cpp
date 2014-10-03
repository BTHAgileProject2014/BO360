#include "BODrawableText.h"

BODrawableText::BODrawableText()
{

}

BODrawableText::~BODrawableText()
{

}

bool BODrawableText::Initialize(float2 p_position, std::string p_text, int3 p_color, int p_fontSize, int p_maxWidth)
{
	m_position = p_position;
	m_text = p_text;
	m_texture = BOGraphicInterface::DrawTextToTexture(m_text, p_color, &m_size, p_fontSize, p_maxWidth);
	m_fontSize = p_fontSize;
	return true;
}

void BODrawableText::Shutdown()
{
	BOGraphicInterface::DestroyTexture(m_texture);
}

void BODrawableText::Draw()
{
	BOGraphicInterface::Draw(m_texture, m_position, m_size);
}

void BODrawableText::SetPosition(float2 p_position)
{
	m_position = p_position;
}

void BODrawableText::SetText(std::string p_text, int3 p_color, int p_maxWidth)
{
	m_text = p_text;
	BOGraphicInterface::DestroyTexture(m_texture);
	m_texture = BOGraphicInterface::DrawTextToTexture(m_text, p_color, &m_size, m_fontSize, p_maxWidth);
}

float2 BODrawableText::GetPosition()
{
	return m_position;
}

int2 BODrawableText::GetSize()
{
	return m_size;
}