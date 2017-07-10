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

/************************************************************
yybdefs.h
This file can be freely modified for the generation of
custom code.

Copyright (c) 1999-2003 Bumble-Bee Software Ltd.
************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Microsoft defines */
#ifdef _MSC_VER

/* structure alignment */
#ifdef _WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif


/* Borland defines */
#ifdef __BORLANDC__

#if !defined(RC_INVOKED)

#if (__BORLANDC__) >= 0x0530
/* restore default packing */
#pragma pack(pop)
#pragma nopackwarning
#else
#pragma option -a. /* restore default packing */
#endif  /* (__BORLANDC__) >= 0x0530 */

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */

#endif

#ifdef __cplusplus
};
#endif
