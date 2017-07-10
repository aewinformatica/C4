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

	struct armor_type
	{
		enum _enum_t
		{
			none        = 0,
			light       = 1,
			heavy       = 2,
			robe        = 3,
		};
	};

	struct consume_type
	{
		enum _enum_t
		{
			normal      = 0,
			charge      = 1,
			stackable   = 2,
			asset       = 3,
		};
	};

	struct default_action
	{
		enum _enum_t
		{
			none              =  0,
			skill_reduce      =  1,
			equip             =  2,
			soulshot          =  3,
			spiritshot        =  4,
			skill_maintain    =  5,
			map_open          =  6,
			dice              =  7,
			recipe            =  8,
			capsule           =  9,
			calc              = 10,
			seed              = 11,
			harvest           = 12,
			xmas_open         = 13,
			show_html         = 14,
			show_ssq_status   = 15,
			summon_soulshot   = 16,
			summon_spiritshot = 17,
			fishingshot       = 18,
		};
	};

	struct etcitem_type
	{
		enum _enum_type
		{
			none                  =  0,
			scroll                =  1,
			arrow                 =  2,
			potion                =  3,
			spellbook             =  4,
			recipe                =  5,
			material              =  6,
			pet_collar            =  7,
			castle_guard          =  8,
			dye                   =  9,
			seed                  = 10,
			seed2                 = 11,
			harvest               = 12,
			lotto                 = 13,
			race_ticket           = 14,
			ticket_of_lord        = 15,
			lure                  = 16,
			crop                  = 17,
			maturecrop            = 18,
			scrl_enchant_wp       = 19,
			scrl_enchant_am       = 20,
			bless_scrl_enchant_wp = 21,
			bless_scrl_enchant_am = 22,
		};
	};

	struct item_type
	{
		enum _enum_t
		{
			weapon      = 0,
			armor       = 1, // armor/shield/underwear/head-accessory
			accessary   = 2, // ring/earring/necklace/bracelet
			questitem   = 3,
			asset       = 4, // adena/ancient adena
			etcitem     = 5,
		};
	};

	struct weapon_type
	{
		enum _enum_t
		{
			none        =  0,
			sword       =  1,
			blunt       =  2,
			dagger      =  3,
			pole        =  4,
			barefist    =  5, // originally 'fist'
			bow         =  6,
			etc         =  7,
			dualsword   =  8, // originally 'dual'
			dualfist    =  9,
			fishingrod  = 10,
		};
	};

} // namespace Script
