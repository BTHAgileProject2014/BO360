#include "BOTextManager.h"
std::vector<BODrawableText*> BOTextManager::m_texts;

BOTextManager::BOTextManager()
{
}


BOTextManager::~BOTextManager()
{
}

bool BOTextManager::Initialize()
{
	return true;
}

void BOTextManager::Shutdown()
{
	for (int i = 0; i < m_texts.size(); i++)
	{
		m_texts[i]->Shutdown();
		delete m_texts[i];
		m_texts[i] = 0;
	}

	m_texts.clear();
}

BODrawableText* BOTextManager::AddText(std::string p_text, float2 p_position, int3 p_color)
{
	BODrawableText* newText = new BODrawableText;
	newText->Initialize(p_position, p_text, p_color);
	m_texts.push_back(newText);
	return newText;
}

void BOTextManager::RemoveText(BODrawableText* p_text)
{
	for (unsigned int i = 0; i < m_texts.size(); i++)
	{
		if (m_texts[i] == p_text)
		{
			delete m_texts[i];
			m_texts[i] = 0;
			m_texts.erase(m_texts.begin() + i);
			break;
		}
	}
}

void BOTextManager::MoveText(BODrawableText* p_text, float2 p_position)
{
	for (unsigned int i = 0; i < m_texts.size(); i++)
	{
		if (m_texts[i] == p_text)
		{
			m_texts[i]->SetPosition(p_position);
			break;
		}
	}
}

void BOTextManager::ChangeText(BODrawableText* p_text, std::string p_textString, int3 p_color)
{
	for (unsigned int i = 0; i < m_texts.size(); i++)
	{
		if (m_texts[i] == p_text)
		{
			m_texts[i]->SetText(p_textString, p_color);
			break;
		}
	}
}

void BOTextManager::DrawTexts()
{
	for (unsigned int i = 0; i < m_texts.size(); i++)
	{
		m_texts[i]->Draw();
	}
}