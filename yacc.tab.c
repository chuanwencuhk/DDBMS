/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

#include <string.h>
#include <string>
#include "parser.h"

extern "C"{
	extern int yylex(void);
	extern int lex_init();
	extern int yyerror(char *s);
}//extern "C" is necessary

OP Operator(char* opstr);
TYPE GetType(char* type_str);

int SaveSelItem(char* tb_name, char* col_name);
int SaveFromItem(char* tb_name);
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op);
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op);
int SaveOrderbyItem(char *col_name);
int SaveFragCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op);

int FillSelectCond();
int FillDeleteCond();
int FillUpdateCond();

/*
for insert stmt
 */
int insert_count = 0;
char* insert_record[MAX_TUPLE_SIZE];

/*
for create stmt.
 */
int attr_count = 0;
char* tb_name;
AttrInfo attr_list[MAX_ATTR_NUM];

/*
frag stmt.
 */
char frag_sql[10][MAX_SQL_SIZE];
char data_paths[10][MAX_SQL_SIZE];
int frag_count = 0;
int frag_cond_count = 0;
int frag_attr_count = 0;
char* frag_tb_name;
FRAG_TYPE frag_type;
FragInfo frag_list[MAX_FRAG_NUM];

UpdateQuery* update_query;
int update_col_count = 0;


SelectQuery* query;
DeleteQuery* delete_query;

int cond_count = 0;
int join_count = 0;
int sel_count = 0;
int from_count = 0;
int orderby_count = 0;
int curPos = 0;
int funcRnt;
Condition cond_list[MAX_COND_NUM];
static char errmsg[4096];
static char recordstr[4096];

#line 135 "yacc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.tab.h".  */
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
    INSERT = 280,
    INTO = 281,
    VALUES = 282,
    DELETE = 283,
    UPDATE = 284,
    SET = 285,
    CHARACTER = 286,
    INTEGER = 287,
    DATE = 288,
    FLOAT = 289,
    VARCHAR = 290,
    HORIZONAL = 291,
    VERTICAL = 292,
    MIX = 293,
    SHOW = 294,
    TABLES = 295,
    EXIT = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "yacc.y" /* yacc.c:355  */

	int intval;
	char* strval;

#line 222 "yacc.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 239 "yacc.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  34
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   162

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      47,    48,    11,     9,    49,    10,    50,    12,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   113,   119,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   134,   140,   148,   157,   165,   175,
     194,   195,   198,   217,   218,   221,   226,   232,   233,   236,
     262,   263,   266,   276,   289,   290,   293,   310,   329,   340,
     348,   349,   352,   359,   365,   370,   375,   381,   387,   395,
     404,   414,   423,   431,   443,   458,   474,   479,   494,   499,
     506,   513,   517,   522,   527,   534,   535,   538,   542,   548,
     549,   552,   558,   562,   567,   569,   572,   573,   576,   580,
     584,   588,   592,   597,   599,   602,   606
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "NUMBER",
  "COMPARISION", "AND", "OR", "'+'", "'-'", "'*'", "'/'", "SELECT", "FROM",
  "WHERE", "ORDER", "BY", "ASC", "DESC", "FRAGMENT", "LOAD", "ALL",
  "UNIQUE", "DISTINCT", "CREATE", "TABLE", "DROP", "INDEX", "INSERT",
  "INTO", "VALUES", "DELETE", "UPDATE", "SET", "CHARACTER", "INTEGER",
  "DATE", "FLOAT", "VARCHAR", "HORIZONAL", "VERTICAL", "MIX", "SHOW",
  "TABLES", "EXIT", "';'", "'('", "')'", "','", "'.'", "$accept",
  "sql_start", "sql_func", "show_table_stat", "table_load", "frag_stat",
  "frag_list_m", "frag_list_h", "frag_h", "frag_cond", "frag_expr",
  "frag_list_v", "frag_v", "attr_list", "attr_name", "update_stat",
  "set_cond", "set_expr", "table_def", "table", "table_attr_list",
  "column_def", "column", "data_type", "table_drop", "insert_stat",
  "insert_list", "delete_stat", "select_stat", "select_seg",
  "select_clause", "selectbegin", "unique", "sellist", "sel_column",
  "fromlist", "sel_table", "where_clause", "condition", "expr",
  "orderby_clause", "orderlist", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    43,
      45,    42,    47,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,    59,    40,    41,    44,
      46
};
# endif

#define YYPACT_NINF -50

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-50)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       3,   -50,    12,     9,   -11,    14,     1,    24,    26,    -2,
     -50,   -50,    47,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,   -50,    30,    63,    33,   -22,    45,    75,    75,
      75,    75,    46,    35,   -50,   -50,    -3,   -50,   -50,   -50,
       6,    76,    79,    80,    81,   -50,    38,    40,    56,    73,
      86,   -50,   -50,    77,    -8,   -50,    41,   -50,    43,   -50,
      90,    48,    90,    50,    91,   -50,    51,    94,    53,    95,
      -1,   -50,    52,    -3,    87,    99,   101,   100,    -9,   -50,
       5,   -50,   102,    -7,   -50,    62,    -4,   -50,   -50,   -38,
     -50,    15,    57,    -5,   103,   -50,   -50,    59,    86,    66,
     104,   -50,    92,   -50,   -50,   -50,    61,    90,   -50,   -50,
      90,   -50,   -15,   -50,    48,   -50,   -50,   102,    67,    91,
      64,   -50,   -50,    68,    70,   -50,   -50,   -50,    19,    65,
     111,    94,   -50,   -50,   -50,   -50,   -50,   113,   -50,   -50,
     -50,   -50,   115,   102,   -50,    23,   -50,   -50,   114,   116,
     117,    74,    69,   -50,   -50,   118,   -50,   -50,    78,   -50,
     -50,   120,    82,    83,    84,   -50,   -50,   -50,    22,   122,
     -50,   -50,   -50,   -50,    85,   -50,   -50,   -50,   123,   -50
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     4,     0,     2,    12,     6,    11,    13,     5,     7,
       8,     9,    10,     0,     0,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    56,     0,    62,    64,    63,
       0,     0,     0,     0,     0,    39,     0,     0,     0,    74,
       0,    14,    71,     0,    74,    69,    67,    59,    58,    65,
       0,     0,     0,     0,     0,    49,     0,     0,     0,     0,
      74,    34,     0,     0,    83,     0,     0,     0,     0,    20,
       0,    23,     0,     0,    27,     0,     0,    15,    43,     0,
      40,     0,     0,     0,    75,    76,    55,     0,     0,     0,
      72,    70,     0,    57,    68,    66,     0,     0,    16,    22,
       0,    32,     0,    30,     0,    17,    18,     0,     0,     0,
       0,    45,    46,     0,     0,    42,    52,    51,     0,     0,
       0,     0,    36,    37,    35,    33,    73,     0,    26,    25,
      21,    24,     0,     0,    28,     0,    38,    41,     0,     0,
       0,     0,     0,    80,    79,     0,    77,    85,    84,    29,
      31,     0,     0,     0,     0,    50,    54,    53,     0,     0,
      19,    44,    48,    47,     0,    82,    81,    86,     0,    78
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -50,   -50,   -50,   -50,   -50,   -50,   -50,   -50,    21,    71,
      27,   -50,    20,    25,   -14,   -50,   -50,    42,   -50,    29,
     -50,    17,   -50,   -50,   -50,   -50,   -50,   -50,   -50,    88,
     -50,   -50,   -50,   -50,    72,   -50,    89,   -49,   -50,     7,
     -50,   -50
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    85,    78,    79,    80,
      81,    83,    84,   112,   113,    17,    70,    71,    18,    46,
      89,    90,    91,   125,    19,    20,   128,    21,    22,    23,
      24,    25,    40,    58,    59,    54,    55,    68,    94,    95,
     103,   158
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,   129,   107,   110,   114,    74,    98,    67,   109,    56,
     118,   119,   110,    27,    67,    28,     1,    57,    41,    42,
      43,    99,    26,     2,     3,   174,   175,   176,     4,    32,
       5,    30,     6,   142,   143,     7,     8,   108,    31,   115,
      29,    73,    33,   117,    53,   130,     9,    34,    10,    11,
     120,   121,   122,   123,   124,    37,    38,    39,    47,    48,
      49,   126,   127,   132,   133,   138,   139,   151,   152,   153,
     154,   161,   143,   166,   167,    44,    35,    36,    45,    60,
      50,    51,    61,    62,    63,    64,    65,    66,    67,    69,
       1,    75,    76,    77,    88,    82,    87,    93,    92,    96,
     100,    97,   104,   102,    56,   111,   106,   136,   116,   137,
     131,   148,   135,   146,   155,   149,   157,   150,   159,   162,
     165,   163,   164,   170,   168,   177,   179,   169,   140,   160,
     171,   172,   173,    86,   144,   178,   147,   141,   156,     0,
     134,    72,   145,     0,     0,     0,     0,     0,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101
};

static const yytype_int16 yycheck[] =
{
       3,     6,    11,     7,    11,    54,     7,    15,     3,     3,
      48,    49,     7,     4,    15,    26,    13,    11,    40,    41,
      42,    70,    10,    20,    21,     3,     4,     5,    25,     3,
      27,    30,    29,    48,    49,    32,    33,    46,    14,    46,
      26,    49,    44,    47,    47,    50,    43,     0,    45,    46,
      35,    36,    37,    38,    39,    22,    23,    24,    29,    30,
      31,     4,     5,     4,     5,     4,     5,    48,    49,     4,
       5,    48,    49,     4,     5,    30,    46,    14,     3,     3,
      34,    46,     3,     3,     3,    47,    46,    31,    15,     3,
      13,    50,    49,     3,     3,    47,    46,     3,    47,    46,
      48,     6,     3,    16,     3,     3,     6,     3,    46,    17,
       7,    47,    46,    46,     3,    47,     3,    47,     3,     5,
      46,     5,     5,     3,     6,     3,     3,    49,   107,   143,
      48,    48,    48,    62,   114,    50,   119,   110,   131,    -1,
      98,    53,   117,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    20,    21,    25,    27,    29,    32,    33,    43,
      45,    46,    52,    53,    54,    55,    56,    66,    69,    75,
      76,    78,    79,    80,    81,    82,    10,     4,    26,    26,
      30,    14,     3,    44,     0,    46,    14,    22,    23,    24,
      83,    40,    41,    42,    30,     3,    70,    70,    70,    70,
      34,    46,     3,    47,    86,    87,     3,    11,    84,    85,
       3,     3,     3,     3,    47,    46,    31,    15,    88,     3,
      67,    68,    80,    49,    88,    50,    49,     3,    58,    59,
      60,    61,    47,    62,    63,    57,    60,    46,     3,    71,
      72,    73,    47,     3,    89,    90,    46,     6,     7,    88,
      48,    87,    16,    91,     3,    85,     6,    11,    46,     3,
       7,     3,    64,    65,    11,    46,    46,    47,    48,    49,
      35,    36,    37,    38,    39,    74,     4,     5,    77,     6,
      50,     7,     4,     5,    68,    46,     3,    17,     4,     5,
      59,    61,    48,    49,    63,    64,    46,    72,    47,    47,
      47,    48,    49,     4,     5,     3,    90,     3,    92,     3,
      65,    48,     5,     5,     5,    46,     4,     5,     6,    49,
       3,    48,    48,    48,     3,     4,     5,     3,    50,     3
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    55,    56,    56,    56,    57,
      58,    58,    59,    60,    60,    61,    61,    62,    62,    63,
      64,    64,    65,    66,    67,    67,    68,    68,    69,    70,
      71,    71,    72,    73,    74,    74,    74,    74,    74,    75,
      76,    77,    77,    77,    77,    78,    79,    80,    81,    81,
      82,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    91,    91,    92,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     5,     6,     6,     6,     5,
       1,     3,     2,     1,     3,     3,     3,     1,     3,     4,
       1,     3,     1,     6,     1,     3,     3,     3,     7,     1,
       1,     3,     2,     1,     4,     1,     1,     4,     4,     4,
       8,     1,     1,     3,     3,     5,     2,     5,     3,     3,
       1,     0,     1,     1,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     4,     0,     2,     1,     3,     7,     3,
       3,     5,     5,     0,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 102 "yacc.y" /* yacc.c:1646  */
    {
			if(funcRnt == 0)
			{
				cout << "Success" <<endl;
			}
			else if(funcRnt < 0)
			{
				cout << "Failure："<<funcRnt<<errmsg<<endl; 
			}
			return 0;
		}
#line 1452 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 114 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Should Flush Table Here.\n"<<endl;
		}
#line 1460 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 120 "yacc.y" /* yacc.c:1646  */
    {
			funcRnt = 100;
		}
#line 1468 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 135 "yacc.y" /* yacc.c:1646  */
    {
			exec_show_table_stmt();
		}
#line 1476 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 141 "yacc.y" /* yacc.c:1646  */
    {
			tb_name = (yyvsp[-1].strval);
			cout<<"LOAD " << (yyvsp[-3].strval) <<" INTO "<<(yyvsp[-1].strval)<<" "<<endl;
			string tmp_name(tb_name);
			load_data_into_local_db(tmp_name);
		}
#line 1487 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 149 "yacc.y" /* yacc.c:1646  */
    {
			frag_type = HOR;
			frag_tb_name = (yyvsp[-2].strval);
			cout<<"frag type is " << frag_type <<" HORIZONAL "<<endl;
			cout<<"frag_tb_name is "<<frag_tb_name<<endl;
			cout<<"load_data";
			load_data();
		}
#line 1500 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 158 "yacc.y" /* yacc.c:1646  */
    {
			frag_type = VER;
			frag_tb_name = (yyvsp[-2].strval);
			cout<<"frag type is " << frag_type <<" VERTICAL "<<endl;
			cout<<"frag_tb_name is "<<frag_tb_name<<endl;
			load_data();
		}
#line 1512 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 166 "yacc.y" /* yacc.c:1646  */
    {
			frag_type = M;
			frag_tb_name = (yyvsp[-2].strval);
			cout<<"frag type is " << frag_type <<" MIXED"<<endl;
			cout<<"frag_tb_name is "<<frag_tb_name<<endl;
			load_data();
	}
#line 1524 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 176 "yacc.y" /* yacc.c:1646  */
    {
		frag_list[frag_count].site_name = (yyvsp[0].strval);
		frag_list[frag_count].cond_count = frag_cond_count;
		frag_list[frag_count].attr_count = frag_attr_count;
		cout<<"M:db_name is "<< frag_list[frag_count].site_name <<endl;
		cout<<"frag info"<< frag_list[frag_count].cond_count<<" "<< frag_list[frag_count].attr_count << endl;
		for(int i = 0; i < frag_list[frag_count].cond_count; i++){
			cout<< "cond " << i <<" "<<frag_list[frag_count].CondList[i].col_name <<" op " <<frag_list[frag_count].CondList[i].op <<" "<<frag_list[frag_count].CondList[i].value<<endl;
		}
		for(int i=0; i< frag_list[frag_count].attr_count; i++){
			cout<<frag_list[frag_count].attr_names[i]<<",";
		}
		frag_cond_count = 0;
		frag_attr_count = 0;
		frag_count ++;
	}
#line 1545 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 199 "yacc.y" /* yacc.c:1646  */
    {
			frag_list[frag_count].site_name = (yyvsp[0].strval);
			frag_list[frag_count].cond_count = frag_cond_count;
			frag_list[frag_count].attr_count = frag_attr_count;
			cout<<"M:db_name is "<< frag_list[frag_count].site_name <<endl;
			cout<<"frag info "<< frag_list[frag_count].cond_count<<" "<< frag_list[frag_count].attr_count << endl;
			for(int i = 0; i < frag_list[frag_count].cond_count; i++){
				cout<< "cond " << i <<" "<<frag_list[frag_count].CondList[i].col_name <<" op " <<frag_list[frag_count].CondList[i].op <<" "<<frag_list[frag_count].CondList[i].value<<endl;
			}
			for(int i=0; i< frag_list[frag_count].attr_count; i++){
				cout<<frag_list[frag_count].attr_names[i]<<",";
			}
			frag_cond_count = 0;
			frag_attr_count = 0;
			frag_count ++;
		}
#line 1566 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 222 "yacc.y" /* yacc.c:1646  */
    {
			SaveFragCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), I, Operator((yyvsp[-1].strval)));	
		
		}
#line 1575 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 227 "yacc.y" /* yacc.c:1646  */
    {
			SaveFragCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), C, Operator((yyvsp[-1].strval)));
		}
#line 1583 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 237 "yacc.y" /* yacc.c:1646  */
    {
			frag_list[frag_count].site_name = (yyvsp[0].strval);
			frag_list[frag_count].cond_count = frag_cond_count;
			frag_list[frag_count].attr_count = frag_attr_count;
			/*
				print this frag info.
			 */
			cout<<"M:db_name is "<< frag_list[frag_count].site_name <<endl;
			cout<<"frag info"<< frag_list[frag_count].cond_count<<" "<< frag_list[frag_count].attr_count << endl;
			for(int i = 0; i < frag_list[frag_count].cond_count; i++){
				cout<< "cond " << i <<" "<<frag_list[frag_count].CondList[i].col_name <<" op " <<frag_list[frag_count].CondList[i].op <<" "<<frag_list[frag_count].CondList[i].value<<endl;
			}
			for(int i=0; i< frag_list[frag_count].attr_count; i++){
				cout<<frag_list[frag_count].attr_names[i]<<",";
			}
			cout<<endl;
			/*
				initial cout.
			 */
			frag_cond_count = 0;
			frag_attr_count = 0;
			frag_count ++;
		}
#line 1611 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 267 "yacc.y" /* yacc.c:1646  */
    {
			frag_list[frag_count].attr_names[frag_attr_count] = (char*)malloc(sizeof((yyvsp[0].strval)));
			memcpy(frag_list[frag_count].attr_names[frag_attr_count],(yyvsp[0].strval),sizeof((yyvsp[0].strval)));
			frag_attr_count++;
		}
#line 1621 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 277 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Update";
			update_query->tb_name = (yyvsp[-4].strval);
			cout<<"tb_name:"<<update_query->tb_name<<endl;
			FillUpdateCond();
			cout<<"Update Cond:"<<endl;
			PrintCondList();
			cout<<"execute update."<<endl;
			exec_update_stmt();
		}
#line 1636 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 294 "yacc.y" /* yacc.c:1646  */
    {
			if(strcmp("=",(yyvsp[-1].strval))==0){
				cout << "string comp"<<endl;
				cout << "update_count"<<update_col_count<<endl;
				update_query->col_name[update_col_count] = (char*)malloc(20);
				memcpy(update_query->col_name[update_col_count],(yyvsp[-2].strval),20);
				update_query->col_value[update_col_count]=(char*)malloc(256);
				memcpy(update_query->col_value[update_col_count],(yyvsp[0].strval),256);
				cout<<update_query->col_name[update_col_count]<<" = "<< update_query->col_value[update_col_count]<<endl;
				update_col_count++;
			}
			else{
				cout<<"syntax error"<<endl;
			}
			
		}
#line 1657 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 311 "yacc.y" /* yacc.c:1646  */
    {
			if(strcmp("=",(yyvsp[-1].strval))==0){
				cout << "comp"<<endl;
				update_query->col_name[update_col_count] = (char*)malloc(20);
				memcpy(update_query->col_name[update_col_count],(yyvsp[-2].strval),20);
				update_query->col_value[update_col_count]=(char*)malloc(sizeof(int)*8);
				sprintf(update_query->col_value[update_col_count],"%d",(yyvsp[0].strval));
				cout<<update_query->col_name[update_col_count]<<" = "<<update_query->col_value[update_col_count];
				update_col_count++;			
			}
			else{
				cout<<"syntax error"<<endl;
			}
		}
#line 1676 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 330 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Create Table "<< tb_name << endl;
			PrintAttrList();
			cout<<"exec_create_stmt"<<endl;
			exec_create_stmt();
			//parser_init();	
		}
#line 1688 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 341 "yacc.y" /* yacc.c:1646  */
    {
			tb_name = (yyvsp[0].strval);
			attr_list[attr_count].table_name = (yyvsp[0].strval);
			//printf("tb_name %s \n",tb_name);
		}
#line 1698 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 353 "yacc.y" /* yacc.c:1646  */
    {
			attr_count++;
			
		}
#line 1707 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 360 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].attr_name = (yyvsp[0].strval);
		}
#line 1715 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 366 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type = C;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1724 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 371 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= I;
			attr_list[attr_count].used_size = 1;
		}
#line 1733 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 376 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= D;
			attr_list[attr_count].used_size = 1;
		}
#line 1742 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 382 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= V;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1751 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 388 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= F;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1760 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 396 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"DROP TABLE"<< tb_name << endl;
			cout<<"exec_drop_table_stmt"<<endl;
			exec_drop_table_stmt();
		}
#line 1770 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 405 "yacc.y" /* yacc.c:1646  */
    {
			cout << "Call Insert Func() here."<<endl;
			cout << "INSERT INTO " << tb_name << " " << recordstr <<endl;
			for(int i = 0; i<insert_count;i++){
				cout<<i<<" "<<insert_record[i]<<endl;
			}			
		}
#line 1782 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 415 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_LENGTH);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), MAX_INT_LENGTH);
			insert_count++;

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos+=strlen((yyvsp[0].strval));
		}
#line 1795 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 424 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), 256);

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos+=strlen((yyvsp[0].strval));
		}
#line 1807 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 432 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_LENGTH);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), MAX_INT_LENGTH);
			insert_count++;

			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos += strlen((yyvsp[0].strval));
		}
#line 1823 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 444 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],(yyvsp[0].strval),256);
			insert_count++;

			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos += strlen((yyvsp[0].strval));
		}
#line 1839 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 459 "yacc.y" /* yacc.c:1646  */
    {
			cout << "DELETE FROM\n"<<endl;
			delete_query->tb_name = tb_name;
			cout << delete_query->tb_name <<endl;
			FillDeleteCond();
			PrintCondList();
			exec_delete_stmt();
			//cout << "Call delete() function here."<<endl;
			
		}
#line 1854 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 475 "yacc.y" /* yacc.c:1646  */
    {
		}
#line 1861 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 480 "yacc.y" /* yacc.c:1646  */
    {
			FillSelectCond();
			PrintSelectQuery();
			//query->tb_name = tb_name;
			query->cond_count = cond_count;
			query->sel_count = sel_count;
			query->join_count = join_count;
			query->from_count = from_count;
			//cout<<"query_tb_name"<<query->tb_name<<endl;
			cout<<"cond "<<query->cond_count<<"sel "<<query->sel_count<<"join "<<query->join_count<<"from "<<query->from_count<<endl;
			exec_select_stmt();
		}
#line 1878 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 495 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 0;
			cout<<"all "<<query->all<<endl;
		}
#line 1887 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 500 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 1;
			cout<<"all "<<query->all<<endl;
		}
#line 1896 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 507 "yacc.y" /* yacc.c:1646  */
    {
			printf("-----one sub selection begin----\n");
		}
#line 1904 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 513 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 0;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1913 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 518 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 0;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1922 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 523 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1931 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 528 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1940 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 539 "yacc.y" /* yacc.c:1646  */
    {
			SaveSelItem(NULL,(yyvsp[0].strval));
		}
#line 1948 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 543 "yacc.y" /* yacc.c:1646  */
    {
			SaveSelItem((yyvsp[-2].strval),(yyvsp[0].strval));
		}
#line 1956 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 553 "yacc.y" /* yacc.c:1646  */
    {	
			SaveFromItem((yyvsp[0].strval));
			
		}
#line 1965 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 559 "yacc.y" /* yacc.c:1646  */
    {	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
#line 1973 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 563 "yacc.y" /* yacc.c:1646  */
    {	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
#line 1981 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 577 "yacc.y" /* yacc.c:1646  */
    {
			SaveJoin((yyvsp[-6].strval), (yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), Operator((yyvsp[-3].strval)));	
		}
#line 1989 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 581 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), I, Operator((yyvsp[-1].strval)));	
		}
#line 1997 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 585 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), C, Operator((yyvsp[-1].strval)));
		}
#line 2005 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 589 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition((yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), I, Operator((yyvsp[-1].strval)));
		}
#line 2013 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 593 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition((yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), C, Operator((yyvsp[-1].strval)));
		}
#line 2021 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 603 "yacc.y" /* yacc.c:1646  */
    {
			SaveOrderbyItem((yyvsp[0].strval));
		}
#line 2029 "yacc.tab.c" /* yacc.c:1646  */
    break;


#line 2033 "yacc.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 608 "yacc.y" /* yacc.c:1906  */


void parser_init()
{
	lex_init();
	tb_name = NULL;
	frag_tb_name = NULL;
	for(int i = 0; i<insert_count;i++)
		memset(insert_record[i],0,MAX_TUPLE_SIZE);

	memset(delete_query,0,sizeof(DeleteQuery));
	memset(update_query,0,sizeof(UpdateQuery));
	memset(attr_list,0,sizeof(AttrInfo)*MAX_ATTR_NUM);
	memset(cond_list,0,sizeof(Condition)*MAX_COND_NUM);
	memset(query,0,sizeof(SelectQuery));
	
	funcRnt = 0;
	curPos = 0;
	
	update_col_count = 0;
	cond_count = 0;
	join_count = 0;
	attr_count = 0;
	sel_count = 0;
	from_count = 0;

	frag_count = 0;
	frag_cond_count = 0;
	frag_attr_count = 0;
	frag_tb_name = NULL;
	memset(frag_list,0,sizeof(FragInfo)*MAX_FRAG_NUM);
	for(int i = 0; i<10;i++){
		memset(frag_sql[i],0,sizeof(char)*MAX_SQL_SIZE);
		memset(data_paths[i],0,sizeof(char)*MAX_SQL_SIZE);

	}	
	return;
}

void InitQuery(){
	delete_query = (DeleteQuery*)malloc(sizeof(DeleteQuery));
	update_query = (UpdateQuery*)malloc(sizeof(UpdateQuery));
	query = (SelectQuery*)malloc(sizeof(SelectQuery));
	query->distinct = 0;
	query->all = 0;
}
void DestoryQuery(){
	free(update_query);
	free(delete_query);
	free(query);
}
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op){
	if(cond_count > MAX_COND_NUM){
		return -1;
	}
	cond_list[cond_count].col_name = col_name;
	
	cond_list[cond_count].tb_name = tb_name;
	cond_list[cond_count].value = value;
	
	cond_list[cond_count].value_type = value_type;
	
	cond_list[cond_count].op = op;
	
	cond_count++;
	
	return 0;
}
int SaveFragCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op){
	if(cond_count > MAX_COND_NUM){
		return -1;
	}
	frag_list[frag_count].CondList[frag_cond_count].col_name = col_name;
	frag_list[frag_count].CondList[frag_cond_count].op = op;
	frag_list[frag_count].CondList[frag_cond_count].tb_name = tb_name;
	frag_list[frag_count].CondList[frag_cond_count].value = value;
	frag_list[frag_count].CondList[frag_cond_count].value_type = value_type;

	frag_cond_count++;
	
	return 0;
}
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op){
	if(join_count > MAX_JOIN_NUM){
			return -1;
		}
	query->JoinList[join_count].col_name1 = col_name1;
	query->JoinList[join_count].col_name2 = col_name2;
	query->JoinList[join_count].op = op;
	query->JoinList[join_count].tb_name1 = tb_name1;
	query->JoinList[join_count].tb_name2 = tb_name2;
	join_count++;
	return 0;

}

int SaveSelItem(char* tb_name, char* col_name){
	query->SelList[sel_count].col_name = col_name;
	query->SelList[sel_count].table_name = tb_name;
	sel_count ++;
	return 0;
}
int SaveFromItem(char* tb_name){
	query->FromList[from_count].tb_name = tb_name;
	from_count++;
	return 0;
}
int SaveOrderbyItem(char *col_name){
	query->OrderbyList[orderby_count].col_name = col_name;
	orderby_count ++;
	return 0;
}
int FillSelectCond(){
	memcpy(query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillDeleteCond(){
	delete_query->cond_count = cond_count;
	memcpy(delete_query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillUpdateCond(){
	update_query->cond_count = cond_count;
	update_query->col_count = update_col_count;
	memcpy(update_query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}

/*
 * attr_list: attributes iostreamfor a table
 */
int PrintAttrList(){
	int i;
	for(i=0;i<attr_count;i++){
			cout<<"attr "<<i<<": "<<attr_list[i].attr_name<<" type "<<attr_list[i].type<<" size "<<attr_list[i].used_size<<endl;
		}
		return 0;
}
int PrintCondList(){
	int i;
	for(i = 0; i < cond_count; i++){
		cout << "AND "<<endl;	
		if(cond_list[i].tb_name != "")
			cout<<"\t"<<cond_list[i].tb_name<<"."<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;
		else
			cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;		
	}
}
int PrintSelectQuery(){
	int i = 0;
	if(from_count!=0)
		cout << "SELECT "<< endl;
	if(query->all != 0)
		cout<< "*" << endl;
	if(sel_count!=0){
		cout << "SEL_LIST" <<endl;
		for(i=0; i < sel_count; i++){
			cout<<"\t"<<query->SelList[i].col_name<<endl;
		}
	}	
	cout << "FROMLIST" << endl;
	for(i = 0; i < from_count; i++){
		cout<<"\t"<<query->FromList[i].tb_name<<endl;
	}
	if(cond_count!=0){
		cout <<"WHERECLAUSE"<< endl;
	}
	//PrintTree();
	for(i = 0; i < cond_count; i++){
			
		if(query->CondList[i].tb_name != "")
			cout<<"\t"<<query->CondList[i].tb_name<<"."<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;
		else
			//cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;	
		cout << "AND "<<endl;	
	}
	for(i=0;i < join_count; i++){
		cout<<"\t"<<query->JoinList[i].tb_name1<<"."<<query->JoinList[i].col_name1<<" op "<<query->JoinList[i].op<<" "<<query->JoinList[i].tb_name2<<"."<<query->JoinList[i].col_name2<<endl;
		cout << "AND "<<endl;
	}
	if(attr_count != 0)
		cout<<"CREATE TABLE "<<endl;
	for(i=0;i<attr_count;i++){
		cout<<attr_list[i].table_name<<"attr_name "<<attr_list[i].attr_name<<"type "<<attr_list[i].type<<"size "<<attr_list[i].used_size<<endl;
	}
	if(orderby_count!=0)
		cout<<"ORDER BY"<< endl;
	for(i=0;i<orderby_count;i++)
		cout<<query->OrderbyList[i].col_name<<endl;
	
	return 0;
}

bool GetFragInfo(FragInfo *g_frag_list,char* g_tb_name,int g_frag_count,int g_frag_type){
	cout<<"enter GetFragInfo"<<endl;
	cout<<"frag_count"<<frag_count<<endl;
	if(frag_count == 0)
	{
		cout<<"there is no frag info"<<endl;
		return false;
	}
	if(NULL == (g_frag_list = (FragInfo*) malloc(frag_count*sizeof(FragInfo)))){
		cout<<"malloc failure."<<endl;
		return false;
	}
	if(NULL == memcpy(g_frag_list,frag_list,frag_count*sizeof(FragInfo))){
		cout<<"memcpy failure."<<endl;
		return false;
	}
	if(NULL == strcpy(g_tb_name,frag_tb_name)){
		cout<<"strcpy failure."<<endl;
		return false;
	}
	g_frag_count = frag_count;
	g_frag_count = frag_type;
	return true;

}

OP Operator(char* opstr)
{
	OP op;
	if (strcmp(opstr, "=") == 0){
		op = E;
		return op;
	}
	else if (strcmp(opstr, ">=") == 0) {
		op = GE;
		return op;
	}	
	else if (strcmp(opstr, "<=") == 0){
		op = LE;
		return op;
	}
	else if (strcmp(opstr, ">") == 0) {
		op = G;
		return op;
	}
	else if (strcmp(opstr, "<") == 0) {
		op = L;
		return op;
	}
	else if (strcmp(opstr, "<>") == 0) {
		op = NE;
		return op;
	}
	return E;
}

TYPE GetType(char* type_str)
{
	TYPE type;
	if (strcmp(type_str, "INTEGER") == 0){
		type = I;
		return type;
	}
	else if (strcmp(type_str, "CHARACTER") == 0) {
		type = C;
		return type;
	}	
	else if (strcmp(type_str, "VARCHAR") == 0){
		type = V;
		return type;
	}
	else if (strcmp(type_str, "FLOAT") == 0) {
		type = F;
		return type;
	}
	else if (strcmp(type_str, "DATE") == 0) {
		type = D;
		return type;
	}
	return I;
}

