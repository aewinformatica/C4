#pragma once

class NpcServer
{
public:
	static NpcServer *I();

	void Send(const char* format, ...);
private:
	static NpcServer *npcServerStatic;
};
