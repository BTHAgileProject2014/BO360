#ifndef BOTEXTMANAGER_H_
#define BOTEXTMANAGER_H_
#include "BOObject.h"
#include "BODrawableText.h"
#include <vector>

class BOTextManager
{
public:
	BOTextManager();
	~BOTextManager();
	static bool Initialize();
	static void Shutdown();
	static BODrawableText* AddText(std::string p_text, float2 p_position, int3 p_color, int p_fontSize, int p_maxWidth);
	static void RemoveText(BODrawableText* p_text);
	static void MoveText(BODrawableText* p_text, float2 p_position);
	static void ChangeText(BODrawableText* p_text, std::string p_textString, int3 p_color, int p_maxWidth);
	static void DrawTexts();

private:
	static std::vector<BODrawableText*> m_texts;
};
#endif

