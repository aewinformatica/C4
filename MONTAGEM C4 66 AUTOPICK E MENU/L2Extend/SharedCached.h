#pragma once

// don't change existing index

enum PacketServerToCached
{
	S_SAVE_INFECTED_SKILLS_TO_DB = 5,
	S_GET_INFECTED_SKILLS,
	S_SET_INFECTED_SKILLS,

	S_GET_USER_EXINFO,
	S_SET_USER_EXINFO,

	S_LOAD_JAIL_INFO,
	S_SAVE_JAIL_INFO,

	S_SET_PLEDGE_POWER,
	S_GET_PLEDGE_INFO,
	S_GET_PLEDGE_REPUTATION,
	S_GET_PLEDGE_SKILL,
	S_SET_USER_NEWPLEDGETYPE,
	S_NEW_SUBPLEDGE_OR_SET_CAPTAIN,
	S_DELETE_SUBPLEDGE,
	S_SET_SPONSOR,
	S_SET_APPRENTICE,
	S_UPDATE_SUBPLEDGE_USER,
	S_INCREASE_MEMBER_SUBPLEDGE,

	S_GET_CURSEDWEAPONS,
	S_SET_CURSEDWEAPONS,
	S_SET_CW,
	S_UPDATE_CW,
	S_DELETE_CURSED_WEAPON,
	S_SET_USER_CWINFO,

	S_SAVE_EX_ITEM_INFO
};

enum PacketCachedToServer
{
	C_LOAD_USER_EX_INFO,
	C_LOAD_JAIL_INFO,
	C_LOAD_CURSEDWEAPONS
};

enum ExInfoItemType
{
	EIIT_LOCATION_SLOT,
	EIIT_AUGMENTATION_ID,
	EIIT_MANA,
	EIIT_ATK_ATTR_ELEMENT,
	EIIT_ATK_ATTR_VALUE,
	EIIT_DEF_ATTR_FIRE,
	EIIT_DEF_ATTR_WATER,
	EIIT_DEF_ATTR_WIND,
	EIIT_DEF_ATTR_EARTH,
	EIIT_DEF_ATTR_HOLY,
	EIIT_DEF_ATTR_UNHOLY
};
