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

#include <istream>

// This is not correct implementation, and it only supports reading
// of UTF-16 files in native byte order, no conversion is done.

class utf16_streambuf : public std::basic_streambuf<wchar_t>
{
public:

	using std::basic_streambuf<wchar_t>::char_type;
	using std::basic_streambuf<wchar_t>::int_type;
	using std::basic_streambuf<wchar_t>::traits_type;

	typedef std::basic_streambuf<char> wrapped_streambuf;

	utf16_streambuf(wrapped_streambuf* sb, bool skip_bom = true)
		: _sb(sb), _skip_bom(skip_bom) {}

protected:

	char_type           _ch[8];
	wrapped_streambuf*  _sb;
	bool                _skip_bom;

	virtual int_type underflow()
	{
		std::streamsize bytes = _sb->sgetn((char*)_ch, sizeof(_ch));
		std::streamsize count = bytes / sizeof(_ch[0]);

		setg(_ch, _ch, _ch + count);

		if (_skip_bom && count > 0)
		{
			_skip_bom = false;
			if (traits_type::to_int_type(_ch[0]) == 0xFEFF)
			{
				setg(_ch + 1, _ch + 1, _ch + count);
			}
		}

		if (gptr() < egptr())
			return traits_type::to_int_type(*gptr());
		else
			return traits_type::eof();
	}
};
