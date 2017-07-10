/*
    This file is part of L2Extend.

    L2Extend is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    L2Extend is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with L2Extend.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Global.h"
#include "FeatureRegistry.h"

#define MAX_NPC_CLASSES 16000


/*
	ABOUT NPC CLAN RELATION IN L2SERVER
	===================================

	typedef DWORD CBitStorage[7008 >> 5];

	0BC5D7ECh  int          g_npcClassCount = 0;
	07E07CC0h  CBitStorage  g_npcClanRelationMatrix[7000];

	These pseudo-definitions attempt to describe how NPC clan relation
	matrix in L2Server looks like. CBitStorage is actually a class, whose
	only member is an array of 219 DWORDs, and whose methods are inlined
	in the server, so they're a bit hard to find. Even the constructor is
	inlined inside sub_9578E0 (which is a compiler-generated initializer
	for the global array g_npcClanRelationMatrix).

	When loading npcdata.txt, a prototype CNPC-derived object is created
	and registered through CObjectDB::RegisterObject for each NPC class.
	The prototype reserves an index into clan relation matrix that all its
	clones (i.e. all NPCs of the same class) are going to consult whenever
	they see another creature being attacked, so as to decide whether they
	should come to aid in combat or not.

	// loc_6FCA13
	pNPC->SD->nClanRelationIndex = g_npcClassCount;
	if (g_npcClassCount < 7000) {
		g_npcClassCount++;
	} else {
		g_log.Add(2, "[%s][%d] npc class count over (MAX=%d)", ...);
	}

	As you can see, there's a maximum of 7000 NPC classes L2Server can
	manage. To increase this limit, we must provide a larger bit array,
	but also patch all access to its elements, because our matrix will
	have wider rows.
*/


typedef DWORD CBitStorage[(MAX_NPC_CLASSES + 31) >> 5];

static CBitStorage g_npcClanRelationMatrix[MAX_NPC_CLASSES];

struct NpcClanRelation : Feature<NpcClanRelation>
{
	const char* name() const
	{
		return "NPC Clan Relation";
	}

	NpcClanRelation()
	{
		if (this != &_instance) return;
		FeatureRegistry::addFeature(*this);
	}

	bool initProcessAttach()
	{
		extendClanHelpTable();
		return true;
	}

	void extendClanHelpTable()
	{
		// CCreature::GatherNeighborCreature
		WriteMemoryDWORD    (0x507F21+ 3, sizeof(CBitStorage));
		WriteRelativeAddress(0x507F28, 3, g_npcClanRelationMatrix, 0);
		WriteMemoryDWORD    (0x507F32+ 2, MAX_NPC_CLASSES);

		// CCreature::GatherNeighborCreatureSquare
		WriteMemoryDWORD    (0x50BFB5 +3, sizeof(CBitStorage));
		WriteRelativeAddress(0x50BFBC, 3, g_npcClanRelationMatrix, 0);
		WriteMemoryDWORD    (0x50BFC6 +2, MAX_NPC_CLASSES);

		// CCreature::GatherNeighborCreatureEx
		WriteMemoryDWORD    (0x50CEE4 +3, sizeof(CBitStorage));
		WriteRelativeAddress(0x50CEEB, 3, g_npcClanRelationMatrix, 0);
		WriteMemoryDWORD    (0x50CEF5 +2, MAX_NPC_CLASSES);

		// ComputeClanHelpTable
		WriteMemoryDWORD    (0x6C0046 +3, sizeof(CBitStorage));
		WriteRelativeAddress(0x6C004D, 3, g_npcClanRelationMatrix, 0);
		WriteMemoryDWORD    (0x6C0057 +2, MAX_NPC_CLASSES);
		WriteRelativeAddress(0x6C00EF, 3, g_npcClanRelationMatrix, 0);
		WriteMemoryDWORD    (0x6C0176 +3, sizeof(CBitStorage));
		WriteMemoryDWORD    (0x6C0180 +2, MAX_NPC_CLASSES);
		WriteMemoryDWORD    (0x6C0207 +3, sizeof(CBitStorage));
		WriteMemoryDWORD    (0x6C0211 +2, MAX_NPC_CLASSES);

		// CObjectDB::RegisterObject
		WriteMemoryDWORD    (0x6FCA26 +2, MAX_NPC_CLASSES);
		WriteMemoryDWORD    (0x6FCA2E +4, MAX_NPC_CLASSES);

		// CWorld::Attack
		WriteMemoryDWORD    (0x8B8FD5 +3, sizeof(CBitStorage));
		WriteRelativeAddress(0x8B8FDC, 3, g_npcClanRelationMatrix, 0);
		WriteMemoryDWORD    (0x8B8FE6 +2, MAX_NPC_CLASSES);

		// CWorld::Spell
		WriteMemoryDWORD    (0x8BA82C +3, sizeof(CBitStorage));
		WriteRelativeAddress(0x8BA833, 3, g_npcClanRelationMatrix, 0);
		WriteMemoryDWORD    (0x8BA83D +2, MAX_NPC_CLASSES);

		// don't patch sub_9578E0, let it initialize the original array
	}
};
