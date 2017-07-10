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

	You May Not Make Commercial Use of any of our content, and any kind
	of newer implementations will be need to be shared and commited.
*/

#include "CGameEvents.h"
#include "CAmpedX64.h"
//#include "CAugmentationSystem.h"
//#include "CChangeWeaponSystem.h"
//#include "CShadowItem.h"
#include "HEXHooks.h"
#include "CParserForSkillEnchanting.h"
#include "FeatureRegistry.h"

struct LogFailedFeature
{
	void operator() (const char* featName, bool failed, bool skipped)
	{
		if (failed)
			CLog::Add(CLog::red, "%s initialization failed", featName);
		else if (skipped)
			CLog::Add(CLog::red, "%s couldn't be initialized", featName);
	}
};

INT32 nOnLoadData = 0;
void CGameEvents::OnLoadData()
{
	L2SERVER_SHARED_GUARD(nOnLoadData);
	TLS_TRACE_BEGIN;

	// Functions
	typedef void (__fastcall *_LD) ();
	_LD xLoadData = (_LD)0x006426A0L;

	// Calling Original Function
	xLoadData();

	// ChangeWeaponSystem system
	//CChangeWeaponSystem::InitializeAfterLoadage();

	// Post Loading Data
	CAmpedX64::InitializeAfterLoadage();
	HEXHooks::PostLoadHooks();
	//CAugmentationSystem::InitializeAfterLoadage();
	InitializeSkillEnchantingAfterLoadage();

	FeatureRegistry::Stage st = FeatureRegistry::stAfterLoadData;
	FeatureRegistry::initFeatures(st);
	FeatureRegistry::foreachFeature(st, LogFailedFeature());

	TLS_TRACE_END_NO_RETURN;
}