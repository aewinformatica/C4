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

#include "yywclex.h"
#include "yywcpars.h"

// namespaces
#ifdef YYSTDCPPLIB
using namespace std;
#endif
#ifdef YYNAMESPACE
using namespace yl;
#endif

int yywflexer::yylex(void){ return 0; }
void yywlexer::yyunputoverflow(void) {}
void yywlexer::yytextoverflow(void) {}
int yywlexer::yygetchar(void) { return 0; }
int yywlexer::yywrap(void) { return 0; }
void yywlexer::yyunput(int) {}
void yywlexer::yyoutput(int) {}
int yywlexer::yyinput(void) { return 0; }
yywlexer::~yywlexer(void) {}
yywlexer::yywlexer(void) {}
int yywparser::yygettoken(void) { return 0; }
void yywparser::yydiscard(int) {}
void yywparser::yysyntaxerror(void) {}
void yywparser::yyerror(wchar_t const *) {}
void yywparser::yystackoverflow(void) {}
void yywparser::yycopyattribute(void *,void const *,int) {}
void yywparser::yydeleteattribute(void *) {}
void * yywparser::yynewattribute(int) { return NULL; }
void yywparser::yylvaltostack(int) {}
void yywparser::yyvaltolval(void) {}
void yywparser::yylvaltoval(void) {}
void yywparser::yyvaltostack(int) {}
void yywparser::yystacktoval(int) {}
yywparser::~yywparser(void) {}
yywparser::yywparser(void) {}
void yywfparser::yydestructclearin(void) {}
int yywfparser::yywork(void) { return 0; }