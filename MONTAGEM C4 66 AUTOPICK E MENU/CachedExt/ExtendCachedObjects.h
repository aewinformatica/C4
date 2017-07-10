#pragma once

class ExtendCachedObjects
{
public:
	static void Initialize();
private:
	static void ExtendCUser();
	static void ExtendCItem();
	static void ExtendCPledge();
};
