/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    nat = 259,
    real = 260,
    character = 261,
    sir = 262,
    BOOL = 263,
    CLASS = 264,
    vec = 265,
    function = 266,
    define = 267,
    IF = 268,
    ELSE = 269,
    FOR = 270,
    WHILE = 271,
    exec = 272,
    comparation = 273,
    evaluate = 274,
    minus = 275,
    copy = 276,
    compare = 277,
    concat = 278,
    AND = 279,
    OR = 280,
    PRINT = 281,
    integer = 282,
    nrReal = 283,
    charact = 284,
    s = 285,
    bol = 286,
    identifier = 287
  };
#endif
/* Tokens.  */
#define MAIN 258
#define nat 259
#define real 260
#define character 261
#define sir 262
#define BOOL 263
#define CLASS 264
#define vec 265
#define function 266
#define define 267
#define IF 268
#define ELSE 269
#define FOR 270
#define WHILE 271
#define exec 272
#define comparation 273
#define evaluate 274
#define minus 275
#define copy 276
#define compare 277
#define concat 278
#define AND 279
#define OR 280
#define PRINT 281
#define integer 282
#define nrReal 283
#define charact 284
#define s 285
#define bol 286
#define identifier 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "lfac.y"

int natVal;
float realVal;
char* bolVal;
char charactVal;
char* sirVal;
char* nameVar;
char* type;

#line 131 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
