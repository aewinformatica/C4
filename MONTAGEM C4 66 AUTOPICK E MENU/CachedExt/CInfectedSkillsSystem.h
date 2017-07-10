#pragma once

#include "Global.H"

class CInfectedSkillsSystem
{
public:
	static void Initialize();
	static bool RequestLoadInfectedSkills(CQuerySocket *pSocket, unsigned char *packet);
	static bool RequestSaveInfectedSkills(CQuerySocket *pSocket, unsigned char *packet);
	static bool RequestSaveToDB(CQuerySocket *pSocket, unsigned char *packet);
private:
};
