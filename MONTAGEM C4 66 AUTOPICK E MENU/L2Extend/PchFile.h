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

    Based upon <l2util/pch_loader.hpp> from deNASC AI decompiler.
    -- Lightmare
*/

#pragma once

#include "global.h"
#include "adv_manip.h"
#include "utf16_streambuf.h"

#include <fstream>
#include <map>

class PchFile
{
public:

	typedef std::wstring                        string_type;
	typedef int                                 number_type;
	typedef std::map<string_type, number_type>  map_type;
	typedef map_type::const_iterator            map_iterator;

	map_type map;

	bool Exists(const string_type& str) const
	{
		return map.find(str) != map.end();
	}

	number_type Get(const string_type& str, number_type def) const
	{
		map_type::const_iterator it = map.find(str);
		return it == map.end() ? def : it->second;
	}

	// Input lines must have this form:
	//
	//    [string] = number
	//
	// Braces around 'string' are required, and spaces are not allowed
	// inside. The equal sign as well as spaces around it are optional.
	// Unlike in denasc, 'number' can only be decimal.
	//
	template <typename CharT, typename TraitsT>
	void
	Load(std::basic_istream<CharT, TraitsT>& is)
	{
		CharT const c_lbrace = is.widen('[');
		CharT const c_rbrace = is.widen(']');
		CharT const c_slash = is.widen('/');
		CharT const c_space = is.widen(' ');
		CharT const c_tab = is.widen('\t');
		CharT const c_newline = is.widen('\n');

		string_type str;
		number_type num;
		CharT c1, c2;

		is >> std::noskipws;

		while (is.good()) {

			is >> std::ws;
			is >> c1;

			if (is.fail()) {

				// nothing
			}
			else if (c1 == c_slash && is.peek() == c_slash) {

				// comment - ignore this line
			}
			else if (c1 == c_lbrace) {

				c2 = c1;
				str.clear();

				// read constant name (must end with ']' to be accepted)
				while (is.peek() != c_newline && is.good()) {
					is >> c2;
					if (c2 == c_rbrace || c2 == c_space || c2 == c_tab)
						break;
					str.append(1, c2);
				}

				// skip optional equal sign
				is >> l2util::skip;
				if (is.peek() == is.widen('=')) {
					is.ignore();
				}

				// read constant value
				is >> l2util::skip >> num;

				if (!is.fail() && c2 == c_rbrace) {
					if (map.find(str) != map.end())
					{
						LogRedefine(str.c_str(), num);
					}
					map[str] = num;
				}
			}

			// ignore trailing characters
			if (!is.eof()) {
				is.clear(is.rdstate() & ~is.failbit);
				is >> l2util::skipline;
			}
		}
	}

	void LoadUnicode(const char* filename)
	{
		std::filebuf frbuf;
		if (frbuf.open(filename, std::ios::in | std::ios::binary))
		{
			utf16_streambuf unibuf(&frbuf);
			Load(std::wistream(&unibuf));
		}
	}

protected:

	void LogRedefine(const char* str, int num)
	{
		CLog::Add(CLog::red, "  [%s] = %d rewrites previous value", str, num);
	}

	void LogRedefine(const wchar_t* str, int num)
	{
		CLog::Add(CLog::red, L"  [%s] = %d rewrites previous value", str, num);
	}
};
