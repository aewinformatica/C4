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

#pragma once

namespace Script
{

	struct target_type
	{
		enum _enum_t
		{
			self            =  0,
			target          =  1,
			others          =  2,
			enemy           =  3,
			enemy_only      =  4,
			item            =  5,
			summon          =  6,
			holything       =  7,
			door_treasure   =  9,
			pc_body         = 10,
			npc_body        = 11,
			wyvern_target   = 12,
		};
	};

	struct trigger_type
	{
		enum _enum_t
		{
			counter         =  1,
			chance          =  2,
			physical_attack =  4,
			critical_attack =  8,
			magical_attack  = 16,
		};
	};

} // namespace Script
