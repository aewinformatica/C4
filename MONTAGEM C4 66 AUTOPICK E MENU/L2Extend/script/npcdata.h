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

	struct occupation
	{
		enum _enum_t
		{
			fighter             =   0,
			warrior             =   1, // NPC or PC
			gladiator           =   2,
			warlord             =   3,
			knight              =   4, // NPC or PC
			paladin             =   5,
			dark_avenger        =   6,
			rogue               =   7, // NPC or PC
			treasure_hunter     =   8,
			hawkeye             =   9,
			mage	            =  10,
			wizard              =  11, // NPC or PC
			sorcerer            =  12,
			necromancer         =  13,
			warlock             =  14,
			cleric              =  15, // NPC or PC
			bishop              =  16,
			prophet             =  17,
			elven_fighter       =  18,
			elven_knight        =  19,
			temple_knight       =  20,
			swordsinger         =  21,
			elven_scout         =  22,
			plains_walker       =  23,
			silver_ranger       =  24,
			elven_mage          =  25,
			elven_wizard        =  26,
			spellsinger         =  27,
			elemental_summoner  =  28,
			oracle              =  29,
			elder	            =  30,
			dark_fighter        =  31,
			palus_knight        =  32,
			shillien_knight     =  33,
			bladedancer         =  34,
			assassin            =  35,
			abyss_walker        =  36,
			phantom_ranger      =  37,
			dark_mage           =  38,
			dark_wizard         =  39,
			spellhowler         =  40,
			phantom_summoner    =  41,
			shillien_oracle     =  42,
			shillien_elder      =  43,
			orc_fighter         =  44,
			orc_raider          =  45,
			destroyer           =  46,
			orc_monk            =  47,
			tyrant              =  48,
			orc_mage            =  49,
			orc_shaman          =  50,
			overlord            =  51,
			warcryer            =  52,
			dwarven_fighter     =  53,
			scavenger           =  54,
			bounty_hunter       =  55,
			artisan             =  56,
			warsmith            =  57,

			shaman              =  58, // NPC only
			monk                =  59, // NPC only
			collector           =  60, // NPC only
			artisan             =  56, // NPC only
			merchant            =  61, // NPC only
			trainer             =  62, // NPC only
			teleporter          =  63, // NPC only
			warehouse_keeper    =  64, // NPC only
			package_keeper      =  65, // NPC only
			newbie_guide        =  66, // NPC only
			guard               =  67, // NPC only
			citizen             =  68, // NPC only
			guild_master        =  69, // NPC only
			guild_coach         =  70, // NPC only
			summon              =  71, // NPC only
			object              =  72, // NPC only
			chamberlain         =  73, // NPC only
			temptrainer         =  74, // NPC only
			holything           =  75, // NPC only
			castle_gate         =  76, // NPC only
			commander           =  77, // NPC only
			house_master        =  78, // NPC only
			blacksmith          =  79, // NPC only
			pet                 =  80, // NPC only
			boss                =  81, // NPC only
			minion              =  82, // NPC only (aka 'zzoldagu')
			treasure            =  83, // NPC only
			monrace             =  84, // NPC only
			mrkeeper            =  85, // NPC only
			xmastree            =  86, // NPC only
			siege_unit          =  87, // NPC only

			duelist             =  88,
			dreadnought         =  89,
			phoenix_knight      =  90,
			hell_knight         =  91,
			sagittarius         =  92,
			adventurer          =  93,
			archmage            =  94,
			soultaker           =  95,
			arcana_lord         =  96,
			cardinal            =  97,
			hierophant          =  98,
			evas_templar        =  99,
			sword_muse          = 100,
			wind_rider          = 101,
			moonlight_sentinel  = 102,
			mystic_muse         = 103,
			elemental_master    = 104,
			evas_saint          = 105,
			shillien_templar    = 106,
			spectral_dancer     = 107,
			ghost_hunter        = 108,
			ghost_sentinel      = 109,
			storm_screamer      = 110,
			spectral_master     = 111,
			shillien_saint      = 112,
			titan               = 113,
			grand_khavatari     = 114,
			dominator           = 115,
			doomcryer           = 116,
			fortune_seeker      = 117,
			maestro             = 118,

			male_soldier        = 123,
			female_soldier      = 124,
			trooper             = 125,
			warder              = 126,
			berserker           = 127,
			male_soulbreaker    = 128,
			female_soulbreaker  = 129,
			arbalester          = 130,
			doombringer         = 131,
			male_soulhound      = 132,
			female_soulhound    = 133,
			trickster           = 134,
			inspector           = 135,
			judicator           = 136,
		};
	};

	struct race
	{
		enum _enum_t
		{
			human           =  0,
			elf             =  1,
			darkelf         =  2,
			orc             =  3,
			dwarf           =  4,
			humanoid        =  5,
			animal          =  6,
			monster         =  7,
			creature        =  8,
			undead          =  9,
			elemental       = 10,
			devil           = 11,
			dragon          = 12,
			angel           = 13,
			construct       = 14,
			beast           = 15,
			plant           = 16,
			divine          = 17,
			demonic         = 18,
			giant           = 19,
			bug             = 20,
			fairy           = 21,
			siege_weapon    = 22,
			mercenary       = 23,
			castle_guard    = 24,
			etc             = 26,
		};
	};

	struct sex
	{
		enum _enum_t
		{
			male        = 0,
			female      = 1,
			etc         = 2,
		};
	};

} // namespace Script
