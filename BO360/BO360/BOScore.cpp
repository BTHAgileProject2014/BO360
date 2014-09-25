#include "BOScore.h"

int BOScore::m_score;

BOScore::BOScore()
{
}


BOScore::~BOScore()
{
}

bool BOScore::Initialize()
{
	m_score = 0;
	return true;
}

void BOScore::Shutdown()
{

}

void BOScore::AddScore(int p_amount)
{
	m_score += p_amount;
	BOHUDManager::SetScore(m_score);
}

void BOScore::SetScore(int p_score)
{
	m_score = p_score;
	BOHUDManager::SetScore(m_score);
}

void BOScore::ResetScore()
{
	m_score = 0;
	BOHUDManager::SetScore(m_score);
}

int BOScore::GetScore()
{
	return m_score;
}
