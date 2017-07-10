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

#include "FeatureRegistry.h"
#include <windows.h>

void FeatureRegistry::error(const char* msg)
{
	MessageBoxA(NULL, msg, "L2Extend Error", MB_OK | MB_ICONERROR);
}

bool FeatureRegistry::initFeatures(Stage st)
{
	bool success = true;
	bool keepGoing = true;

	while (keepGoing)
	{
		keepGoing = false;

		FeatureMap::iterator it = instance()._features.begin();
		FeatureMap::iterator end = instance()._features.end();

		for (; it != end; ++it)
		{
			FeatureInfo& featInfo = it->second;

			if (featInfo.needsInit(st) && featInfo.dependsOk(st))
			{
				if (featInfo._feature->init(st))
				{
					featInfo.setStage(st);
					keepGoing = true;
				}
				else
				{
					featInfo.setStage(stInitFailed);
					success = false;
				}
			}
		}
	}

	return success;
}

FeatureRegistry& FeatureRegistry::instance()
{
	static FeatureRegistry singleton;
	return singleton;
}
