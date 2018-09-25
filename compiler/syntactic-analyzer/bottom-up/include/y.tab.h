/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
    VOID = 258,
    INT = 259,
    DOUBLE = 260,
    BOOL = 261,
    STRING = 262,
    CLASS = 263,
    INTERFACE = 264,
    NULL = 265,
    THIS = 266,
    EXTENDS = 267,
    IMPLEMENTS = 268,
    FOR = 269,
    WHILE = 270,
    IF = 271,
    ELSE = 272,
    RETURN = 273,
    BREAK = 274,
    NEW = 275,
    NEWARRAY = 276,
    PRINT = 277,
    READINTEGER = 278,
    READLINE = 279,
    ID = 280,
    USERTYPE = 281,
    INTCONSTANT = 282,
    DOUBLECONSTANT = 283,
    TRUE = 284,
    FALSE = 285,
    STRINGCONSTANT = 286,
    UMINUS = 287,
    L = 288,
    LEQ = 289,
    G = 290,
    GEQ = 291,
    EQ = 292,
    NEQ = 293,
    AND = 294,
    OR = 295,
    EOF = 296
  };
#endif
/* Tokens.  */
#define VOID 258
#define INT 259
#define DOUBLE 260
#define BOOL 261
#define STRING 262
#define CLASS 263
#define INTERFACE 264
#define NULL 265
#define THIS 266
#define EXTENDS 267
#define IMPLEMENTS 268
#define FOR 269
#define WHILE 270
#define IF 271
#define ELSE 272
#define RETURN 273
#define BREAK 274
#define NEW 275
#define NEWARRAY 276
#define PRINT 277
#define READINTEGER 278
#define READLINE 279
#define ID 280
#define USERTYPE 281
#define INTCONSTANT 282
#define DOUBLECONSTANT 283
#define TRUE 284
#define FALSE 285
#define STRINGCONSTANT 286
#define UMINUS 287
#define L 288
#define LEQ 289
#define G 290
#define GEQ 291
#define EQ 292
#define NEQ 293
#define AND 294
#define OR 295
#define EOF 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
