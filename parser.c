/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y" /* yacc.c:337  */

#include "vslc.h"
#include "stdio.h"
#include "stdlib.h"

#define C0(type, data) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 0))

#define C1(type, data, a1) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 1, (a1)))

#define C2(type, data, a1, a2) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 2, (a1), (a2)))

#define C3(type, data, a1, a2, a3) \
         (node_new_lc((type), (data), (yylineno), (yycolumn), 3, (a1), (a2), (a3)))


#line 89 "y.tab.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
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
   by #include "y.tab.h".  */
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
    UMINUS = 258,
    THEN = 259,
    ELSE = 260,
    FUNC = 261,
    PRINT = 262,
    RETURN = 263,
    CONTINUE = 264,
    IF = 265,
    WHILE = 266,
    DO = 267,
    OPENBLOCK = 268,
    CLOSEBLOCK = 269,
    VAR = 270,
    IDENTIFIER = 271,
    STRING = 272,
    NUMBER = 273,
    FUNCTION_COMMENT_PARSER = 274
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 30 "parser.y" /* yacc.c:352  */

    node_t *node;
    char *str;            /* Will always be a malloc'ed string. */
    enum node_type type;
    int_type integer;

#line 159 "y.tab.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   141

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

#define YYUNDEFTOK  2
#define YYMAXUTOK   274

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      26,    27,     5,     3,    25,     4,     2,     6,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    28,     2,
      30,    29,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     8,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     7,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    61,    64,    65,    68,    69,    73,    74,
      77,    78,    82,    83,    87,    88,    94,    94,    95,    95,
      97,    98,   101,   105,   107,   110,   111,   112,   113,   114,
     115,   116,   120,   121,   124,   125,   126,   127,   130,   131,
     134,   140,   141,   142,   146,   147,   148,   149,   153,   154,
     155,   158,   159,   162,   165,   168,   169,   172,   173,   174
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "'~'", "THEN", "ELSE", "FUNC", "PRINT", "RETURN", "CONTINUE", "IF",
  "WHILE", "DO", "OPENBLOCK", "CLOSEBLOCK", "VAR", "IDENTIFIER", "STRING",
  "NUMBER", "FUNCTION_COMMENT_PARSER", "','", "'('", "')'", "':'", "'='",
  "'<'", "'>'", "$accept", "start", "program", "global_list", "global",
  "statement_list", "print_list", "expression_list", "variable_list",
  "argument_list", "parameter_list", "declaration_list", "function",
  "function_comment", "statement", "block", "assignment_statement",
  "return_statement", "print_statement", "null_statement", "if_statement",
  "while_statement", "relation", "expression", "declaration", "print_item",
  "identifier", "number", "string", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    43,    45,    42,    47,   258,   126,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,    44,    40,    41,    58,    61,
      60,    62
};
# endif

#define YYPACT_NINF -21

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-21)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,    -2,    -2,   -21,    20,   -21,     5,   -21,   -21,    -9,
     -21,   -21,    -5,     2,   -21,   -21,   -21,   -21,    -2,    -2,
       2,    -4,   -21,   120,    42,    81,   -21,    81,    81,    85,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,    13,    81,
      81,   -21,   -21,    81,    18,    34,   -21,     0,   -21,   -21,
      34,    15,     1,    16,   100,    85,   -21,   -21,    22,   -21,
     -21,     8,    42,    81,    81,    81,    81,    81,   120,    81,
      81,    81,   120,   -21,   -21,   110,   -21,    81,   -21,   -21,
       3,     3,   -21,   -21,    24,    31,    34,    37,    34,    34,
      34,   -21,   -21,    34,    81,   -21,   120,    34,   -21
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    24,     0,     2,     3,     4,     6,     0,
       7,    57,     0,    54,    14,     1,     5,    22,    19,     0,
      18,     0,    15,     0,     0,     0,    37,     0,     0,     0,
      23,    31,    25,    26,    27,    30,    28,    29,     0,     0,
       0,    59,    58,     0,    36,    55,    10,    52,    51,    56,
      35,     0,     0,     0,     0,     0,     8,    20,     0,    48,
      49,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,    33,     9,     0,    21,     0,    50,    11,
      44,    45,    46,    47,    16,     0,    12,    38,    41,    42,
      43,    40,    32,    34,     0,    53,     0,    13,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -21,   -21,   -21,   -21,    53,     6,   -21,   -21,    44,   -21,
     -21,   -21,    57,   -21,   -20,   -21,   -21,   -21,   -21,   -21,
     -21,   -21,    41,    17,   -19,    10,    -1,   -21,   -21
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    54,    44,    84,    13,    85,
      21,    55,     8,     9,    56,    31,    32,    33,    34,    35,
      36,    37,    51,    45,    10,    46,    47,    48,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      12,    14,     1,    30,    63,    64,    65,    66,    65,    66,
      57,    63,    64,    65,    66,     3,     1,    14,    22,    11,
      15,    18,    38,    23,    68,     2,    67,    19,    38,     3,
      69,    70,    71,    72,    74,    78,    76,    63,    64,    65,
      66,    58,    50,    62,    52,    52,    39,    96,    87,    94,
      40,    77,    91,    38,    38,    74,    59,    60,    95,    16,
      61,    75,    20,    11,    41,    42,    17,    38,    43,    53,
       0,    38,    79,     0,    38,     0,    98,     0,     0,     0,
      80,    81,    82,    83,    86,    39,    88,    89,    90,    40,
       0,     0,     0,     0,    93,    38,     0,    24,    25,    26,
      27,    28,    11,    29,    42,     2,    11,    43,     0,     0,
       0,    97,    24,    25,    26,    27,    28,     0,    29,    73,
       0,    11,    24,    25,    26,    27,    28,     0,    29,    92,
       0,    11,    24,    25,    26,    27,    28,     0,    29,     0,
       0,    11
};

static const yytype_int8 yycheck[] =
{
       1,     2,    11,    23,     3,     4,     5,     6,     5,     6,
      29,     3,     4,     5,     6,    24,    11,    18,    19,    21,
       0,    26,    23,    27,     9,    20,    26,    25,    29,    24,
      29,    30,    31,    17,    54,    27,    55,     3,     4,     5,
       6,    28,    25,    25,    27,    28,     4,    10,    68,    25,
       8,    29,    72,    54,    55,    75,    39,    40,    27,     6,
      43,    55,    18,    21,    22,    23,     9,    68,    26,    28,
      -1,    72,    62,    -1,    75,    -1,    96,    -1,    -1,    -1,
      63,    64,    65,    66,    67,     4,    69,    70,    71,     8,
      -1,    -1,    -1,    -1,    77,    96,    -1,    12,    13,    14,
      15,    16,    21,    18,    23,    20,    21,    26,    -1,    -1,
      -1,    94,    12,    13,    14,    15,    16,    -1,    18,    19,
      -1,    21,    12,    13,    14,    15,    16,    -1,    18,    19,
      -1,    21,    12,    13,    14,    15,    16,    -1,    18,    -1,
      -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    20,    24,    33,    34,    35,    36,    44,    45,
      56,    21,    58,    40,    58,     0,    36,    44,    26,    25,
      40,    42,    58,    27,    12,    13,    14,    15,    16,    18,
      46,    47,    48,    49,    50,    51,    52,    53,    58,     4,
       8,    22,    23,    26,    38,    55,    57,    58,    59,    60,
      55,    54,    55,    54,    37,    43,    46,    56,    28,    55,
      55,    55,    25,     3,     4,     5,     6,    26,     9,    29,
      30,    31,    17,    19,    46,    37,    56,    29,    27,    57,
      55,    55,    55,    55,    39,    41,    55,    46,    55,    55,
      55,    46,    19,    55,    25,    27,    10,    55,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    35,    35,    36,    36,    37,    37,
      38,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      43,    43,    44,    44,    45,    46,    46,    46,    46,    46,
      46,    46,    47,    47,    48,    49,    50,    51,    52,    52,
      53,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    57,    57,    58,    59,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     1,     1,     2,
       1,     3,     1,     3,     1,     3,     1,     0,     1,     0,
       1,     2,     2,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     4,     2,     2,     1,     4,     6,
       4,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     1,     1,     4,     2,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  *++yylsp = yylloc;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 61 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = ast_g_root = C1(PROGRAM, NULL, (yyvsp[0].node)); }
#line 1437 "y.tab.c" /* yacc.c:1652  */
    break;

  case 4:
#line 64 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(GLOBAL_LIST, NULL, (yyvsp[0].node));     }
#line 1443 "y.tab.c" /* yacc.c:1652  */
    break;

  case 5:
#line 65 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(GLOBAL_LIST, NULL, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1449 "y.tab.c" /* yacc.c:1652  */
    break;

  case 6:
#line 68 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(GLOBAL, NULL, (yyvsp[0].node)); }
#line 1455 "y.tab.c" /* yacc.c:1652  */
    break;

  case 7:
#line 69 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(GLOBAL, NULL, (yyvsp[0].node)); }
#line 1461 "y.tab.c" /* yacc.c:1652  */
    break;

  case 8:
#line 73 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT_LIST, NULL, (yyvsp[0].node));     }
#line 1467 "y.tab.c" /* yacc.c:1652  */
    break;

  case 9:
#line 74 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(STATEMENT_LIST, NULL, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1473 "y.tab.c" /* yacc.c:1652  */
    break;

  case 10:
#line 77 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(PRINT_LIST, NULL, (yyvsp[0].node));     }
#line 1479 "y.tab.c" /* yacc.c:1652  */
    break;

  case 11:
#line 78 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(PRINT_LIST, NULL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1485 "y.tab.c" /* yacc.c:1652  */
    break;

  case 12:
#line 82 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(EXPRESSION_LIST, NULL, (yyvsp[0].node));     }
#line 1491 "y.tab.c" /* yacc.c:1652  */
    break;

  case 13:
#line 83 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(EXPRESSION_LIST, NULL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1497 "y.tab.c" /* yacc.c:1652  */
    break;

  case 14:
#line 87 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(VARIABLE_LIST, NULL, (yyvsp[0].node));     }
#line 1503 "y.tab.c" /* yacc.c:1652  */
    break;

  case 15:
#line 88 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(VARIABLE_LIST, NULL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1509 "y.tab.c" /* yacc.c:1652  */
    break;

  case 16:
#line 94 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(ARGUMENT_LIST,  NULL, (yyvsp[0].node)); }
#line 1515 "y.tab.c" /* yacc.c:1652  */
    break;

  case 17:
#line 94 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C0(ARGUMENT_LIST, NULL);  }
#line 1521 "y.tab.c" /* yacc.c:1652  */
    break;

  case 18:
#line 95 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(PARAMETER_LIST, NULL, (yyvsp[0].node)); }
#line 1527 "y.tab.c" /* yacc.c:1652  */
    break;

  case 19:
#line 95 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C0(PARAMETER_LIST, NULL); }
#line 1533 "y.tab.c" /* yacc.c:1652  */
    break;

  case 20:
#line 97 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(DECLARATION_LIST, NULL, (yyvsp[0].node));     }
#line 1539 "y.tab.c" /* yacc.c:1652  */
    break;

  case 21:
#line 98 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(DECLARATION_LIST, NULL, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1545 "y.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 101 "parser.y" /* yacc.c:1652  */
    {
              (yyvsp[0].node)->comment = (yyvsp[-1].node);
              (yyval.node) = (yyvsp[0].node);
             }
#line 1554 "y.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 105 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C3(FUNCTION, NULL, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1560 "y.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 107 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C0(FUNCTION_COMMENT, (yyvsp[0].str)); }
#line 1566 "y.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 110 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT, NULL, (yyvsp[0].node)); }
#line 1572 "y.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 111 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT, NULL, (yyvsp[0].node)); }
#line 1578 "y.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 112 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT, NULL, (yyvsp[0].node)); }
#line 1584 "y.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 113 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT, NULL, (yyvsp[0].node)); }
#line 1590 "y.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 114 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT, NULL, (yyvsp[0].node)); }
#line 1596 "y.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 115 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT, NULL, (yyvsp[0].node)); }
#line 1602 "y.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 116 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(STATEMENT, NULL, (yyvsp[0].node)); }
#line 1608 "y.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 120 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(BLOCK, NULL, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1614 "y.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 121 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(BLOCK, NULL, (yyvsp[-1].node));     }
#line 1620 "y.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 124 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(ASSIGNMENT_STATEMENT, NULL, (yyvsp[-3].node), (yyvsp[0].node)); }
#line 1626 "y.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 125 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(RETURN_STATEMENT, NULL, (yyvsp[0].node));         }
#line 1632 "y.tab.c" /* yacc.c:1652  */
    break;

  case 36:
#line 126 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(PRINT_STATEMENT,  NULL, (yyvsp[0].node));         }
#line 1638 "y.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 127 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C0(NULL_STATEMENT,   NULL);             }
#line 1644 "y.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 130 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(IF_STATEMENT, NULL, (yyvsp[-2].node), (yyvsp[0].node));     }
#line 1650 "y.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 131 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C3(IF_STATEMENT, NULL, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1656 "y.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 134 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(WHILE_STATEMENT, NULL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1662 "y.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 140 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(RELATION, "=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1668 "y.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 141 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(RELATION, "<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1674 "y.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 142 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(RELATION, ">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1680 "y.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 146 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(EXPRESSION, "+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1686 "y.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 147 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(EXPRESSION, "-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1692 "y.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 148 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(EXPRESSION, "*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1698 "y.tab.c" /* yacc.c:1652  */
    break;

  case 47:
#line 149 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(EXPRESSION, "/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1704 "y.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 153 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(EXPRESSION, "-", (yyvsp[0].node));     }
#line 1710 "y.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 154 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(EXPRESSION, "~", (yyvsp[0].node));     }
#line 1716 "y.tab.c" /* yacc.c:1652  */
    break;

  case 50:
#line 155 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1722 "y.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 158 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(EXPRESSION, NULL, (yyvsp[0].node));     }
#line 1728 "y.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 159 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(EXPRESSION, NULL, (yyvsp[0].node));     }
#line 1734 "y.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 162 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C2(EXPRESSION, "func_call", (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1740 "y.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 165 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(DECLARATION, NULL, (yyvsp[0].node)); }
#line 1746 "y.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 168 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(PRINT_ITEM, NULL, (yyvsp[0].node)); }
#line 1752 "y.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 169 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C1(PRINT_ITEM, NULL, (yyvsp[0].node)); }
#line 1758 "y.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 172 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C0(IDENTIFIER_DATA, NODE_DATA_CAST (yyvsp[0].str));     }
#line 1764 "y.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 173 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C0(NUMBER_DATA,     NODE_DATA_CAST (yyvsp[0].integer)); }
#line 1770 "y.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 174 "parser.y" /* yacc.c:1652  */
    { (yyval.node) = C0(STRING_DATA,     NODE_DATA_CAST (yyvsp[0].str));     }
#line 1776 "y.tab.c" /* yacc.c:1652  */
    break;


#line 1780 "y.tab.c" /* yacc.c:1652  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 176 "parser.y" /* yacc.c:1918  */


int yyerror(const char *error)
{
    fprintf(stderr, "%s on line %d, col:%d\n", error, yylineno, yycolumn);
    exit(EXIT_FAILURE);
}
