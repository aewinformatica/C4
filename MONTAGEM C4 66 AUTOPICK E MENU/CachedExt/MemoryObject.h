#pragma once

#pragma pack( push, 1 )
class MemoryObject
{
public:
	virtual void Release(char* file, int line, int ObjType, __int8 flag=0) {};
	virtual void sub_452900() {};
	virtual void sub_442940() {};
	//virtual void IncreaseRefCount(char *file, int line, int ObjType) {};
	void MemoryObjectConstructor();	
};
#pragma pack( pop )
