#include "Global.h"
#include "ExtendCachedObjects.h"

void ExtendCachedObjects::Initialize()
{
	ExtendCachedObjects::ExtendCUser();
	ExtendCachedObjects::ExtendCItem();
	ExtendCachedObjects::ExtendCPledge();
}

void ExtendCachedObjects::ExtendCUser()
{
	int newSize = sizeof(CUser);

	// CUserDbHelper::MakeNewUserObject
	// .text:004AF5D3                 push    5A8h
	WriteMemoryDWORD(0x4AF5D4, newSize);
	// .text:004AF60E                 mov     dword_9804A8[eax*4], 5A8h
	WriteMemoryDWORD(0x4AF615, newSize);
}

void ExtendCachedObjects::ExtendCItem()
{
	int newSize = sizeof(CItem);

	// enlarge CItem allocation size (can't be done by just patching
	// 'push 58h', because the new size is greater than 0x7F and the
	// pushes are signed 8-bit, so the argument would be negative!)
	WriteMemoryDWORD(0x442684, newSize);
	WriteInstruction(0x444354, (INT32)&CItem::Alloc_442640, 0, ASM_CALL);
	WriteInstruction(0x4B1E6D, (INT32)&CItem::Alloc_442640, 0, ASM_CALL);
	WriteInstruction(0x4B2090, (INT32)&CItem::Alloc_442640, 0, ASM_CALL);
	WriteInstruction(0x4B7560, (INT32)&CItem::Alloc_442640, 0, ASM_CALL);

	WriteInstruction(0x443B4E, (INT32)&CItem::Alloc_44B290, 0, ASM_CALL);
	WriteMemoryDWORD(0x443B7F, newSize);
	WriteInstruction(0x452755, (INT32)&CItem::Alloc_44B290, 0, ASM_CALL);
	WriteMemoryDWORD(0x452782, newSize);
	WriteInstruction(0x4B1584, (INT32)&CItem::Alloc_44B290, 0, ASM_CALL);
	WriteMemoryDWORD(0x4B15B1, newSize);

	// call CItem::CItem(int)
	WriteInstruction(0x4B1E8C, (INT32)&CItem::ConstructBlank, 0, ASM_CALL);
	WriteInstruction(0x4B20AF, (INT32)&CItem::ConstructBlank, 0, ASM_CALL);

	// call CItem::CItem(...)
	WriteInstruction(0x443BBA, (INT32)&CItem::ConstructCopy, 0, ASM_CALL);
	WriteInstruction(0x44439C, (INT32)&CItem::ConstructLoad, 0, ASM_CALL);
	WriteInstruction(0x4527C3, (INT32)&CItem::ConstructLoad, 0, ASM_CALL);
	WriteInstruction(0x4B15FB, (INT32)&CItem::ConstructLoad, 0, ASM_CALL);
	WriteInstruction(0x4B75A8, (INT32)&CItem::ConstructLoad, 0, ASM_CALL);

	// override CItem::~CItem
	WriteMemoryDWORD(0x515484 + 0x0C, (INT32)&CItem::Destruct);
}

void ExtendCachedObjects::ExtendCPledge()
{
	int newSize = sizeof(CPledge);

	// .text:004582DE                 push    148h
	WriteMemoryDWORD(0x4582DF, newSize);

	// .text:00458797                 push    148h
	WriteMemoryDWORD(0x458798, newSize);

	// .text:0045983B                 push    148h
	WriteMemoryDWORD(0x45983C, newSize);

	// .text:00456FFD                 mov     dword_9804A8[eax*4], 148h
	WriteMemoryDWORD(0x457004, newSize);
}
