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

    Based upon <l2util/advmanip.hpp> from deNASC AI decompiler.
    -- Lightmare
*/

#pragma once

#include <istream>

namespace l2util {

   template <typename charT, typename traits>
   std::basic_istream<charT, traits>&
   skip(std::basic_istream<charT, traits>& is)
    {
      typedef std::basic_streambuf<charT, traits>   streambuf_type;
      typedef typename traits::int_type             int_type;

      streambuf_type*   sb = is.rdbuf();
      int_type const    space = traits::to_int_type(is.widen('\40'));
      int_type const    tab = traits::to_int_type(is.widen('\t'));
      int_type          c = sb->sgetc();

      while (traits::eq_int_type(c, space) ||
             traits::eq_int_type(c, tab))
       {
         c = sb->snextc();
       }

      if (traits::eq_int_type(c, traits::eof()))
       {
         is.setstate(std::ios_base::eofbit);
       }

      return is;
    }

   template <typename charT, typename traits>
   std::basic_istream<charT, traits>&
   skipline(std::basic_istream<charT, traits>& is)
    {
      typedef std::basic_streambuf<charT, traits>   streambuf_type;
      typedef typename traits::int_type             int_type;

      streambuf_type*   sb = is.rdbuf();
      int_type const    nl = traits::to_int_type(is.widen('\n'));
      int_type const    eof = traits::eof();
      int_type          c = sb->sbumpc();

      while (!traits::eq_int_type(c, nl))
       {
         if (traits::eq_int_type(c, eof))
          {
            is.setstate(std::ios_base::eofbit);
            break;
          }
         c = sb->sbumpc();
       }

      return is;
    }

} // l2util namespace
