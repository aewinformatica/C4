#pragma once

#include "Global.H"

class CQuestSystem
{
public:
	static void Initialize();
private:
	static void FixSaveMemo();
	static void MoveQuestData(__int32 index, __int8 maxQuests, INT32 newSaveMemo);
};
