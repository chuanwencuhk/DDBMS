/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
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
    NAME = 258,
    STRING = 259,
    NUMBER = 260,
    COMPARISION = 261,
    AND = 262,
    OR = 263,
    SELECT = 264,
    FROM = 265,
    WHERE = 266,
    ORDER = 267,
    BY = 268,
    ASC = 269,
    DESC = 270,
    FRAGMENT = 271,
    LOAD = 272,
    ALL = 273,
    UNIQUE = 274,
    DISTINCT = 275,
    CREATE = 276,
    TABLE = 277,
    DROP = 278,
    INDEX = 279,
    LOCAL = 280,
    INSERT = 281,
    INTO = 282,
    VALUES = 283,
    DELETE = 284,
    UPDATE = 285,
    SET = 286,
    CHARACTER = 287,
    INTEGER = 288,
    DATE = 289,
    FLOAT = 290,
    VARCHAR = 291,
    HORIZONAL = 292,
    VERTICAL = 293,
    MIXED = 294,
    NONE = 295,
    SHOW = 296,
    TABLES = 297,
    EXIT = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 80 "yacc.y" /* yacc.c:1909  */

	int intval;
	char* strval;

#line 103 "yacc.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */
