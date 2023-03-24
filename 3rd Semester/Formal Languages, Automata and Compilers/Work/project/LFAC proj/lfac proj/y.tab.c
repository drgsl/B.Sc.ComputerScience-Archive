/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lfac.y"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char *);

extern FILE* yyin;
extern char* yytext;
extern int yylineno;

//De scris in fisier
int fd1, fd2;
char buffer[100];
char buffer2[100];

//daca programul compileaza corect
int correct_compilation = 1;


//Functii
int cautare(char* tip, char* numeVar);
int cautaNume(char *numeVar);
char *obtineTipul(char *numeVar);
int schimbaValoareaNat(char *tip, char *numeVar, int valoareNat);
int schimbaValoareaReal(char *tip, char *numeVar, float valoareReal);
int schimbaValoareaSir(char *tip, char *numeVar, char *valoareSir);
int schimbaValoareaCara(char *tip, char *numeVar, char valoareCara);
int schimbaValoareabool(char *tip, char *numeVar, char *valoareBool);
int cautaVal(char *numeVar);
void Print(char *str, int value);


#line 109 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 235 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  32
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   267

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  223

#define YYUNDEFTOK  2
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    41,    34,    33,    43,     2,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    79,    79,    87,    88,    90,    91,    93,    94,    95,
      96,    97,    98,   103,   104,   105,   106,   107,   110,   111,
     112,   113,   114,   116,   116,   118,   119,   120,   121,   122,
     123,   124,   125,   127,   128,   129,   130,   131,   135,   137,
     138,   140,   141,   145,   146,   147,   150,   169,   172,   181,
     189,   197,   204,   212,   213,   216,   217,   220,   221,   222,
     223,   224,   225,   229,   230,   231,   232,   233,   237,   260,
     262,   293,   326,   327,   329,   330,   331,   332,   335,   336,
     337,   338,   339,   340,   349,   348,   372,   374,   375,   379,
     381,   382,   386,   388,   389,   394,   396,   397,   402,   403,
     404
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "nat", "real", "character",
  "sir", "BOOL", "CLASS", "vec", "function", "define", "IF", "ELSE", "FOR",
  "WHILE", "exec", "comparation", "evaluate", "minus", "copy", "compare",
  "concat", "AND", "OR", "PRINT", "integer", "nrReal", "charact", "s",
  "bol", "identifier", "'+'", "'*'", "'/'", "'{'", "'}'", "'['", "']'",
  "'('", "')'", "'='", "','", "$accept", "S", "progr",
  "declaratii_globale", "declaratie", "variabila", "variabila_declarata",
  "obiect", "$@1", "array", "definitie", "main_program", "acolade", "cods",
  "cod", "declaratii_locale", "declaratie_main", "operatii_naturale",
  "operatie_naturala", "operatii_boolene", "interogare", "conditie",
  "loop", "metoda", "$@2", "valoare_nat", "lista_de_variabile_nat",
  "valoare_real", "lista_de_variabile_real", "valoare_charact",
  "lista_de_variabile_charact", "valoare_boolean",
  "lista_de_variabile_boolean", "valoare_sir", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,    43,    42,    47,   123,   125,    91,    93,
      40,    41,    61,    44
};
# endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     120,    -4,     7,    29,    67,    71,    82,    84,    15,   111,
     113,   175,  -112,   120,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,   137,   139,   140,   141,   142,   143,  -112,   163,
     146,   130,  -112,  -112,  -112,   151,   161,   162,   160,   117,
     164,   155,   165,   166,   167,   168,   152,  -112,  -112,  -112,
    -112,  -112,    40,  -112,  -112,  -112,  -112,  -112,  -112,  -112,
     154,   156,  -112,  -112,  -112,  -112,   144,   150,   159,   169,
     170,  -112,   173,   158,    78,   151,   174,   176,    36,  -112,
    -112,  -112,  -112,  -112,  -112,    75,  -112,  -112,  -112,  -112,
    -112,   171,   172,    21,  -112,   177,   179,   180,   181,   151,
      78,   178,   188,   189,   190,   191,   182,   184,   187,   151,
     186,   -16,   199,   185,    90,  -112,  -112,   192,   193,  -112,
    -112,    70,   -21,    76,    65,  -112,   194,   139,   140,   141,
     142,   143,   112,   195,   -15,  -112,    78,  -112,  -112,    34,
    -112,   196,   148,   197,  -112,   -14,  -112,  -112,  -112,  -112,
    -112,   198,  -112,  -112,    -2,  -112,  -112,    59,  -112,  -112,
     103,  -112,  -112,   131,   151,   200,   201,   202,   203,  -112,
    -112,  -112,  -112,    11,    11,    11,    11,  -112,  -112,   164,
     164,   204,   207,  -112,   205,  -112,   206,  -112,   209,  -112,
     208,   214,   213,   215,   149,   217,   145,   145,  -112,  -112,
    -112,  -112,   227,  -112,  -112,  -112,  -112,  -112,   151,   151,
     151,   151,   151,   210,   223,  -112,  -112,  -112,  -112,  -112,
    -112,   211,  -112
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     0,     6,     7,     8,     9,    10,    11,
       4,    12,     0,    13,    15,    14,    16,    17,    23,     0,
       0,     0,     1,     5,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,    35,    36,
      34,    37,     0,    38,    86,    18,    89,    19,    92,    22,
       0,     0,    98,    20,    95,    21,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,     0,     0,    39,
      57,    58,    59,    60,    61,     0,    42,    47,    43,    44,
      62,     0,     0,     0,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,    41,     0,     0,    24,
      55,     0,     0,     0,     0,    85,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,     0,    69,    68,     0,
      63,     0,     0,     0,    46,    52,    48,    50,    51,    49,
      99,     0,    87,    26,     0,    90,    28,     0,    93,    30,
       0,    96,    32,     0,     0,     0,     0,     0,     0,    75,
      76,    74,    83,     0,     0,     0,     0,    53,    54,     0,
       0,     0,     0,    25,     0,    27,     0,    29,     0,    31,
       0,    72,     0,     0,     0,     0,    65,    64,    66,    67,
      70,    71,     0,   100,    88,    91,    94,    97,     0,     0,
       0,     0,     0,     0,     0,    73,    79,    80,    78,    81,
      77,     0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,  -112,  -112,   228,     9,     1,    10,  -112,    60,
      93,   240,   -75,  -112,   122,  -112,   -58,  -111,  -112,  -112,
    -112,   -96,  -112,    95,  -112,  -112,  -112,    94,  -112,   147,
    -112,  -109,  -112,   153
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    80,    81,    82,    41,    83,
      84,    20,    53,    85,    86,    93,    87,   139,   140,   141,
      88,   109,    89,    90,    99,    55,   154,    57,   157,    59,
     160,    65,   163,    63
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     110,    16,   142,   145,   126,   148,   173,   155,    94,    15,
      17,   137,   169,   170,    16,    64,   138,   171,   156,   174,
     175,   176,    15,    17,   125,     2,     3,     4,     5,     6,
       7,     8,     9,    10,   135,   120,    22,   183,   137,    23,
     172,   184,    29,   138,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    72,   173,    73,    74,    75,   119,    76,
      18,    24,   196,   197,   198,   199,    77,   174,   175,   176,
     200,   201,    78,    18,   106,   177,   113,    79,   114,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    72,   191,
      73,    74,    75,    19,    76,    21,   161,   152,   185,    25,
     107,    77,   186,    26,   162,   158,    19,    78,    21,   153,
     108,    60,   115,    61,    27,   159,    28,   137,    56,    58,
      62,    64,   138,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,   215,   216,   217,   218,   219,    60,   165,
      61,   166,   187,    30,   167,    31,   188,    62,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    47,    48,    49,
      50,    51,   101,   102,   103,   104,   105,    42,    43,    44,
     189,    45,   179,   180,   190,    32,   211,   212,    35,   175,
     176,    36,    37,    38,    39,    40,    46,    52,    54,    58,
      56,    66,    95,    71,    91,    64,    92,    67,    68,    69,
      70,    96,   136,   117,   118,   134,   143,   116,   146,     0,
     127,    97,    98,   100,   111,   121,   112,   122,   123,   124,
     128,   129,   130,   131,   133,   132,   144,   168,   208,   181,
     182,   214,   204,   150,   205,   164,   151,   178,   206,   207,
     209,    33,   210,   192,   193,   194,   195,   202,   203,   213,
     221,   220,   222,    34,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,     0,     0,     0,   149
};

static const yytype_int16 yycheck[] =
{
      75,     0,   111,   114,   100,   114,    20,    28,    66,     0,
       0,    27,    27,    28,    13,    31,    32,    32,    39,    33,
      34,    35,    13,    13,    99,     4,     5,     6,     7,     8,
       9,    10,    11,    12,   109,    93,    40,    39,    27,    32,
     136,    43,    27,    32,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    20,    15,    16,    17,    37,    19,
       0,    32,   173,   174,   175,   176,    26,    33,    34,    35,
     179,   180,    32,    13,    73,    41,    40,    37,    42,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   164,
      15,    16,    17,     0,    19,     0,    31,    27,    39,    32,
      22,    26,    43,    32,    39,    29,    13,    32,    13,    39,
      32,    21,    37,    23,    32,    39,    32,    27,    28,    29,
      30,    31,    32,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   208,   209,   210,   211,   212,    21,    27,
      23,    29,    39,    32,    32,    32,    43,    30,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    27,    28,    29,
      30,    31,     4,     5,     6,     7,     8,     4,     5,     6,
      39,     8,    24,    25,    43,     0,    27,    28,    41,    34,
      35,    42,    42,    42,    42,    42,    40,    36,    27,    29,
      28,    36,    42,    41,    40,    31,    40,    32,    32,    32,
      32,    42,    16,    32,    32,    18,     7,    85,   114,    -1,
      32,    42,    42,    40,    40,    38,    40,    38,    38,    38,
      32,    32,    32,    32,    40,    43,    41,    32,    14,    32,
      32,     4,    27,    41,    28,    41,    43,    41,    29,    31,
      27,    13,    27,    43,    43,    43,    43,    43,    41,    32,
      27,    41,    41,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   114,    -1,    -1,    -1,    -1,    -1,   114
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    45,    46,    47,    48,    49,    50,    51,    53,    54,
      55,    67,    40,    32,    32,    32,    32,    32,    32,    27,
      32,    32,     0,    48,    55,    41,    42,    42,    42,    42,
      42,    52,     4,     5,     6,     8,    40,    27,    28,    29,
      30,    31,    36,    56,    27,    69,    28,    71,    29,    73,
      21,    23,    30,    77,    31,    75,    36,    32,    32,    32,
      32,    41,    13,    15,    16,    17,    19,    26,    32,    37,
      49,    50,    51,    53,    54,    57,    58,    60,    64,    66,
      67,    40,    40,    59,    60,    42,    42,    42,    42,    68,
      40,     4,     5,     6,     7,     8,    50,    22,    32,    65,
      56,    40,    40,    40,    42,    37,    58,    32,    32,    37,
      60,    38,    38,    38,    38,    56,    65,    32,    32,    32,
      32,    32,    43,    40,    18,    56,    16,    27,    32,    61,
      62,    63,    75,     7,    41,    61,    71,    73,    75,    77,
      41,    43,    27,    39,    70,    28,    39,    72,    29,    39,
      74,    31,    39,    76,    41,    27,    29,    32,    32,    27,
      28,    32,    65,    20,    33,    34,    35,    41,    41,    24,
      25,    32,    32,    39,    43,    39,    43,    39,    43,    39,
      43,    56,    43,    43,    43,    43,    61,    61,    61,    61,
      75,    75,    43,    41,    27,    28,    29,    31,    14,    27,
      27,    27,    28,    32,     4,    56,    56,    56,    56,    56,
      41,    27,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    48,
      48,    48,    48,    49,    49,    49,    49,    49,    50,    50,
      50,    50,    50,    52,    51,    53,    53,    53,    53,    53,
      53,    53,    53,    54,    54,    54,    54,    54,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    65,    65,    66,    66,
      66,    66,    66,    66,    68,    67,    69,    70,    70,    71,
      72,    72,    73,    74,    74,    75,    76,    76,    77,    77,
      77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     4,     4,
       4,     4,     4,     0,     6,     8,     7,     8,     7,     8,
       7,     8,     7,     3,     3,     3,     3,     3,     4,     2,
       3,     2,     1,     1,     1,     8,     3,     1,     3,     3,
       3,     3,     3,     4,     4,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     1,     1,
       3,     3,     5,     7,     3,     3,     3,     6,     7,     7,
       7,     7,     3,     4,     0,     6,     1,     1,     3,     1,
       1,     3,     1,     1,     3,     1,     1,     3,     1,     4,
       6
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 80 "lfac.y"
{     
      if(correct_compilation== 1)
            printf("Limbaj acceptat!\n");
      else printf("Eroare de compilare! \n");
}
#line 1574 "y.tab.c"
    break;

  case 5:
#line 90 "lfac.y"
                                                      {write(fd1, "global\n", strlen("global\n"));}
#line 1580 "y.tab.c"
    break;

  case 6:
#line 91 "lfac.y"
                                                      {write(fd1, "global\n", strlen("global\n"));}
#line 1586 "y.tab.c"
    break;

  case 13:
#line 103 "lfac.y"
                                                              { if(cautaNume((yyvsp[0].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "nat %s ", (yyvsp[0].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1592 "y.tab.c"
    break;

  case 14:
#line 104 "lfac.y"
                                                              { if(cautaNume((yyvsp[0].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "character %s ", (yyvsp[0].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1598 "y.tab.c"
    break;

  case 15:
#line 105 "lfac.y"
                                                              { if(cautaNume((yyvsp[0].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "real %s ", (yyvsp[0].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1604 "y.tab.c"
    break;

  case 16:
#line 106 "lfac.y"
                                                              { if(cautaNume((yyvsp[0].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "sir %s ", (yyvsp[0].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1610 "y.tab.c"
    break;

  case 17:
#line 107 "lfac.y"
                                                              { if(cautaNume((yyvsp[0].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "BOOL %s ", (yyvsp[0].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1616 "y.tab.c"
    break;

  case 18:
#line 110 "lfac.y"
                                                              { if(cautaNume((yyvsp[-2].nameVar))) correct_compilation= 0;  snprintf(buffer, 100, "nat %s = %d ", (yyvsp[-2].nameVar), (yyvsp[0].natVal)); write(fd1, buffer, strlen(buffer)); }
#line 1622 "y.tab.c"
    break;

  case 19:
#line 111 "lfac.y"
                                                              { if(cautaNume((yyvsp[-2].nameVar))) correct_compilation= 0;  snprintf(buffer, 100, "real %s = %.3f ", (yyvsp[-2].nameVar), (yyvsp[0].realVal)); write(fd1, buffer, strlen(buffer)); }
#line 1628 "y.tab.c"
    break;

  case 20:
#line 112 "lfac.y"
                                                              { if(cautaNume((yyvsp[-2].nameVar))) correct_compilation= 0;  snprintf(buffer, 100, "sir %s = %s ", (yyvsp[-2].nameVar), (yyvsp[0].sirVal)); write(fd1, buffer, strlen(buffer)); }
#line 1634 "y.tab.c"
    break;

  case 21:
#line 113 "lfac.y"
                                                              { if(cautaNume((yyvsp[-2].nameVar))) correct_compilation= 0;  snprintf(buffer, 100, "BOOL %s = %s ", (yyvsp[-2].nameVar), (yyvsp[0].bolVal)); write(fd1, buffer, strlen(buffer)); }
#line 1640 "y.tab.c"
    break;

  case 22:
#line 114 "lfac.y"
                                                               { if(cautaNume((yyvsp[-2].nameVar))) correct_compilation= 0;  snprintf(buffer, 100, "character %s = %c ", (yyvsp[-2].nameVar), (yyvsp[0].charactVal)); write(fd1, buffer, strlen(buffer)); }
#line 1646 "y.tab.c"
    break;

  case 23:
#line 116 "lfac.y"
                           { if(cautaNume((yyvsp[0].nameVar))) correct_compilation= 0; snprintf(buffer2, 100, "CLASS %s \n", (yyvsp[0].nameVar)); write(fd2, buffer2, strlen(buffer2));write(fd2, "local\n", strlen("local\n")); }
#line 1652 "y.tab.c"
    break;

  case 25:
#line 118 "lfac.y"
                                                                              { if(cautaNume((yyvsp[-4].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-4].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1658 "y.tab.c"
    break;

  case 26:
#line 119 "lfac.y"
                                                                              { if(cautaNume((yyvsp[-3].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-3].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1664 "y.tab.c"
    break;

  case 27:
#line 120 "lfac.y"
                                                                              { if(cautaNume((yyvsp[-4].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-4].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1670 "y.tab.c"
    break;

  case 28:
#line 121 "lfac.y"
                                                                              { if(cautaNume((yyvsp[-3].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-3].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1676 "y.tab.c"
    break;

  case 29:
#line 122 "lfac.y"
                                                                                { if(cautaNume((yyvsp[-4].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-4].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1682 "y.tab.c"
    break;

  case 30:
#line 123 "lfac.y"
                                                                                { if(cautaNume((yyvsp[-3].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-3].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1688 "y.tab.c"
    break;

  case 31:
#line 124 "lfac.y"
                                                                              { if(cautaNume((yyvsp[-4].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-4].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1694 "y.tab.c"
    break;

  case 32:
#line 125 "lfac.y"
                                                                              { if(cautaNume((yyvsp[-3].nameVar))) correct_compilation= 0; snprintf(buffer, 100, "vec %s ", (yyvsp[-3].nameVar)); write(fd1, buffer, strlen(buffer)); }
#line 1700 "y.tab.c"
    break;

  case 45:
#line 147 "lfac.y"
                                                    { Print((yyvsp[-4].nameVar),(yyvsp[-1].natVal));}
#line 1706 "y.tab.c"
    break;

  case 46:
#line 151 "lfac.y"
      {     
            if(cautare("function",(yyvsp[-2].nameVar)) == 0) 
            {
                  printf("functia %s nu a fost declarata \n", (yyvsp[-2].nameVar)); 
                  correct_compilation= 0;
            } 
      }
#line 1718 "y.tab.c"
    break;

  case 48:
#line 173 "lfac.y"
      {
            if(cautare("real", (yyvsp[-2].nameVar)) == 0) 
                  {correct_compilation= 0; printf("eroare la variabila %s \n", (yyvsp[-2].nameVar));}
            schimbaValoareaReal("real", (yyvsp[-2].nameVar), (yyvsp[0].realVal));
      
      }
#line 1729 "y.tab.c"
    break;

  case 49:
#line 182 "lfac.y"
      {
                  if(cautare("sir", (yyvsp[-2].nameVar)) == 0)
                        {correct_compilation= 0; printf("eroare la variabila %s \n", (yyvsp[-2].nameVar));} 
                  schimbaValoareaSir("sir", (yyvsp[-2].nameVar), (yyvsp[0].sirVal));
      }
#line 1739 "y.tab.c"
    break;

  case 50:
#line 190 "lfac.y"
      {
                  if(cautare("character", (yyvsp[-2].nameVar)) == 0) 
                        {correct_compilation= 0; printf("eroare la variabila %s \n", (yyvsp[-2].nameVar));} 
                  schimbaValoareaCara("character", (yyvsp[-2].nameVar), (yyvsp[0].charactVal));
      }
#line 1749 "y.tab.c"
    break;

  case 51:
#line 198 "lfac.y"
      {
                  if(cautare("BOOL", (yyvsp[-2].nameVar)) == 0) 
                        {correct_compilation= 0; printf("eroare la variabila %s \n", (yyvsp[-2].nameVar));}
                  schimbaValoareabool("BOOL", (yyvsp[-2].nameVar), (yyvsp[0].bolVal));
      }
#line 1759 "y.tab.c"
    break;

  case 52:
#line 205 "lfac.y"
      {       
                  if(cautare("nat", (yyvsp[-2].nameVar)) == 0) 
                        {correct_compilation = 0; printf("eroare la variabila %s \n", (yyvsp[-2].nameVar));} 
                  schimbaValoareaNat("nat", (yyvsp[-2].nameVar), (yyvsp[0].natVal));
      }
#line 1769 "y.tab.c"
    break;

  case 53:
#line 212 "lfac.y"
                                           {if(correct_compilation==1) printf("avem valoarea %d \n", (yyvsp[-1].natVal));}
#line 1775 "y.tab.c"
    break;

  case 54:
#line 213 "lfac.y"
                                           {if(correct_compilation==1) printf("avem valoarea %s \n", (yyvsp[-1].bolVal));}
#line 1781 "y.tab.c"
    break;

  case 55:
#line 216 "lfac.y"
                                                          {write(fd1, "local\n", strlen("local\n")); }
#line 1787 "y.tab.c"
    break;

  case 56:
#line 217 "lfac.y"
                                                                   {write(fd1, "local\n", strlen("local\n"));}
#line 1793 "y.tab.c"
    break;

  case 63:
#line 229 "lfac.y"
                                      { (yyval.natVal) = (yyvsp[0].natVal);}
#line 1799 "y.tab.c"
    break;

  case 64:
#line 230 "lfac.y"
                                                            { (yyval.natVal) = (yyvsp[-2].natVal) + (yyvsp[0].natVal); }
#line 1805 "y.tab.c"
    break;

  case 65:
#line 231 "lfac.y"
                                                              { (yyval.natVal) = (yyvsp[-2].natVal) - (yyvsp[0].natVal);}
#line 1811 "y.tab.c"
    break;

  case 66:
#line 232 "lfac.y"
                                                            { (yyval.natVal) = (yyvsp[-2].natVal) * (yyvsp[0].natVal);}
#line 1817 "y.tab.c"
    break;

  case 67:
#line 233 "lfac.y"
                                                            { (yyval.natVal) = (yyvsp[-2].natVal) / (yyvsp[0].natVal);}
#line 1823 "y.tab.c"
    break;

  case 68:
#line 238 "lfac.y"
                  {
                        char *tip = obtineTipul((yyvsp[0].nameVar)); 
                        if (tip == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", (yyvsp[0].nameVar));
                              correct_compilation= 0;
                        }
                        if (tip && strcmp(tip, "nat") != 0)
                        {
                              printf("variabila %s nu este de tipul natural\n", (yyvsp[0].nameVar));
                              correct_compilation= 0;
                        }
                        if (tip && strcmp(tip, "nat") == 0 ) 
                        {
			      (yyval.natVal) =  cautaVal((yyvsp[0].nameVar));
			      if( correct_compilation ==1)
                              printf("vom returna %d\n", (yyval.natVal));
                              
                        }
                  }
#line 1848 "y.tab.c"
    break;

  case 69:
#line 260 "lfac.y"
                            {(yyval.natVal) = (yyvsp[0].natVal);}
#line 1854 "y.tab.c"
    break;

  case 70:
#line 263 "lfac.y"
                  { char *tip1 = obtineTipul((yyvsp[-2].bolVal)); 
                        if (tip1 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", (yyvsp[-2].bolVal));
                              correct_compilation= 0;
                        }
                        if (tip1 && strcmp(tip1, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", (yyvsp[-2].bolVal));
                              correct_compilation= 0;
                        }
                        char *tip2 = obtineTipul((yyvsp[0].bolVal)); 
                        if (tip2 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", (yyvsp[0].bolVal));
                              correct_compilation= 0;
                        }
                        if (tip2 && strcmp(tip2, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", (yyvsp[0].bolVal));
                              correct_compilation= 0;
                        }
                        if (tip1 && tip2 && strcmp(tip1, "BOOL") == 0 && strcmp(tip2, "BOOL") == 0 ) 
                        {
			      (yyval.bolVal) = (yyvsp[-2].bolVal) && (yyvsp[0].bolVal);
			      if( correct_compilation ==1)
                              printf("vom returna %s\n", (yyval.bolVal));
                              
                        }
                  }
#line 1889 "y.tab.c"
    break;

  case 71:
#line 294 "lfac.y"
                  {char *tip1 = obtineTipul((yyvsp[-2].bolVal)); 
                        if (tip1 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", (yyvsp[-2].bolVal));
                              correct_compilation= 0;
                        }
                        if (tip1 && strcmp(tip1, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", (yyvsp[-2].bolVal));
                              correct_compilation= 0;
                        }
                        char *tip2 = obtineTipul((yyvsp[0].bolVal)); 
                        if (tip2 == NULL)
                        {
                              printf("variabila %s nu a fost initializata\n", (yyvsp[0].bolVal));
                              correct_compilation= 0;
                        }
                        if (tip2 && strcmp(tip2, "BOOL") != 0)
                        {
                              printf("variabila %s nu este de tipul bool\n", (yyvsp[0].bolVal));
                              correct_compilation= 0;
                        }
                        if (tip1 && tip2 && strcmp(tip1, "BOOL") == 0 && strcmp(tip2, "BOOL") == 0 ) 
                        {
			      (yyval.bolVal) = (yyvsp[-2].bolVal) || (yyvsp[0].bolVal);
			      if( correct_compilation ==1)
                              printf("vom returna %s\n", (yyval.bolVal));
                              
                        }
                  }
#line 1924 "y.tab.c"
    break;

  case 84:
#line 349 "lfac.y"
      {
            if(cautaNume((yyvsp[-2].nameVar)) == 1) 
                  correct_compilation= 0;
            snprintf(buffer2, 100,"function %s: \n", (yyvsp[-2].nameVar)); 
            write(fd2, buffer2, strlen(buffer2));
            write(fd2, "global\n", strlen("global\n"));
      }
#line 1936 "y.tab.c"
    break;

  case 86:
#line 372 "lfac.y"
                      { (yyval.natVal)=(yyvsp[0].natVal); }
#line 1942 "y.tab.c"
    break;

  case 89:
#line 379 "lfac.y"
                      { (yyval.realVal)=(yyvsp[0].realVal); }
#line 1948 "y.tab.c"
    break;

  case 92:
#line 386 "lfac.y"
                          { (yyval.charactVal)=(yyvsp[0].charactVal); }
#line 1954 "y.tab.c"
    break;

  case 95:
#line 394 "lfac.y"
                      { (yyval.bolVal)=(yyvsp[0].bolVal); }
#line 1960 "y.tab.c"
    break;

  case 98:
#line 402 "lfac.y"
                { (yyval.sirVal)=(yyvsp[0].sirVal); }
#line 1966 "y.tab.c"
    break;

  case 99:
#line 403 "lfac.y"
                                       {(yyval.sirVal)=identifier;}
#line 1972 "y.tab.c"
    break;

  case 100:
#line 404 "lfac.y"
                                                       {(yyval.sirVal)+=identifier;}
#line 1978 "y.tab.c"
    break;


#line 1982 "y.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 407 "lfac.y"


/*a function that is called by the YACC when an error is encountered during parsing. 
It prints the error message "eroare de sintaxa" 
and the line number on which the error occurred. */
int yyerror(char *e){
      printf("eroare de sintaxa: %s la linia:%d\n",e,yylineno);
}
/* a function that searches for a variable with the given name and type in a file 
and returns 1 if found or 0 if not found. */
int cautare(char* tip, char* numeVar)  
{     
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET); //setez cursorul la inceputul fis
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  linie[strlen(linie) - 6] = '\0';      
            else if(strstr(linie, "global"))  
                  linie[strlen(linie) - 7] = '\0';   
            else linie[strlen(linie) - 2] = '\0';

            //Scoatem "="
            if(strstr(linie,"="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Comparam
            //printf("comparam [%s] cu [%s] \n", linie, variabila);
            if (strcmp(linie, variabila) == 0)
                  gasit = 1;
      }

      return gasit;
}

/*a function that checks if a variable with the given name has already been declared 
and returns 1 if it has been declared and 0 if it has not been declared. */
int cautaNume(char *numeVar) //verifica daca variabila a fost deja declarata
{
      int flag = 0;
      flag += cautare("nat",numeVar);
      flag += cautare("real",numeVar);
      flag += cautare("sir",numeVar);
      flag += cautare("character",numeVar);
      flag += cautare("BOOL",numeVar);
      flag += cautare("function", numeVar);
      flag += cautare("vec", numeVar);
      flag += cautare("CLASS", numeVar);
      if(flag == 0)
            return 0;
      printf("variabila %s deja exista \n" ,numeVar);
      return 1;
}
/*a function that takes a string and an integer as arguments
and prints the value of the expression "string + value" */
void Print(char *str, int value)
{
      int int_str=cautaVal(str);
      printf("valoarea expresiei %s+%d este %d\n", str,value,int_str+value);
}
/*a function that checks the type of a variable 
and returns the type of the variable. */
char *obtineTipul(char *numeVar) // verifica ce tip are numeVar si daca exista acest tip (daca variabila e initializata) si returneaza tipul 
{
      char *p = (char *)malloc(20);

      if( cautare("nat",numeVar) )
            strcpy(p, "nat");
      else if( cautare("real",numeVar) )
            strcpy(p, "real");
      else if( cautare("sir",numeVar) )
            strcpy(p, "sir");
      else if( cautare("BOOL",numeVar) )
            strcpy(p, "BOOL");
      else if( cautare("character",numeVar) )
            strcpy(p, "character");
      else if ( cautare("function",numeVar) )
            strcpy(p, "function");
      else if( cautare("vec",numeVar) )
            strcpy(p, "vec");
      else if( cautare("CLASS", numeVar) )
            strcpy(p, "CLASS");
      else  p = NULL;

      return p;
}

int schimbaValoareaNat(char *tip, char *numeVar, int valoareNat)  // x = 6
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %d %s",temp, valoareNat, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}

int schimbaValoareaReal(char *tip, char *numeVar, float valoareReal)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %.2f %s",temp, valoareReal, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}
int schimbaValoareaSir(char *tip, char *numeVar, char *valoareSir)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %s %s",temp, valoareSir, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}

int schimbaValoareaCara(char *tip, char *numeVar, char valoareCara)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %c %s",temp, valoareCara, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}

int schimbaValoareabool(char *tip, char *numeVar, char *valoareBool)
{
      //(copiat de la cautare codul)
      char linie[100]="";
      int index = 0;
      char  c;
      int gasit = 0;
      char scope[10];

      char variabila[100];
      strcpy(variabila, tip);
      strcat(variabila, " ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;

            //Vrem sa stim cat dam cursorul inapoi
            int inapoi = strlen(linie) + 1;
            
            //Remove the local/global part
            if(strstr(linie,"local"))
                  {linie[strlen(linie) - 6] = '\0'; strcpy(scope,"local");}     
            else if(strstr(linie, "global"))  
                  {linie[strlen(linie) - 7] = '\0'; strcpy(scope,"global");}

            //Scoatem "="
            if( strstr(linie, "="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Daca am gasit variabila in fisier
            if (strcmp(linie, variabila) == 0)
            {
                  //Copiem tot ce e dupa linie (si are potential sa fie suprascris)
                  char rest[10000];
                  bzero(rest, 10000);
                  pread(fd1, rest, 10000, lseek(fd1,0,SEEK_CUR));

                  //Creem noua linie
                  lseek(fd1, -inapoi, SEEK_CUR);
                  char temp[50];
                  strcpy(temp, linie);
                  snprintf(linie,100,"%s = %s %s",temp, valoareBool, scope);

                  //Suprascriem
                  write(fd1, linie, strlen(linie));
                  write(fd1,"\n",1);
                  write(fd1, rest, strlen(rest));
                  return 0;
            }
      }
}


/*a function that searches for a variable with the given name in a file, 
finds the value assigned to the variable 
and returns the value. */
int cautaVal(char *numeVar)
{
      char linie[100]="";
      int index = 0;
      char  c;
      char copie[100];

      char variabila[100];
      strcpy(variabila, "natural ");
      strcat(variabila, numeVar);      

      //Citit fisier
      lseek(fd1, 0, SEEK_SET);
      while(1)
      {
            bzero(linie, 100);
            index = 0;
            //Citit o linie
            while(1)
            {
                  int r = read(fd1, &c, 1);
                  if( r == 0 || c == '\n')
                        break;     
                  linie[index++] = (char )c;                   
            }

            //Am terminat de citit din fisier
            if (index == 0)
                  break;
            
            //facem o copie a liniei
            strcpy(copie, linie);

            //Remove the local/global part
            if(strstr(linie,"local"))
                  linie[strlen(linie) - 6] = '\0';      
            else if(strstr(linie, "global"))  
                  linie[strlen(linie) - 7] = '\0';   
            else linie[strlen(linie) - 2] = '\0';

            //Scoatem "="
            if(strstr(linie,"="))
            {
                  char *temp = strtok(linie, "=");
                  temp[strlen(temp) - 1] = '\0';
                  strcpy(linie, temp);
            }

            //Comparam
            //printf("comparam [%s] cu [%s] \n", linie, variabila);
            if (strcmp(linie, variabila) == 0)
            {
                  strtok(copie, "=");
                  char *valoare = strtok(NULL, " ");
                  return atoi(valoare);
            }
      }
      return 0;
}

int main(int argc, char** argv){
fd1 = open("symbol_table.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
fd2 = open("symbol_table_functions.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
yyin=fopen(argv[1],"r");
yyparse();
} 
