// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file /Users/herzog/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.h
 ** Define the KerML::Parser::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_USERS_HERZOG_DOCUMENTS_PROJEKTE_CPP_SYSMLV2_FILEHANDLING_SRC_KERML_KERMLBISONPARSER_H_INCLUDED
# define YY_YY_USERS_HERZOG_DOCUMENTS_PROJEKTE_CPP_SYSMLV2_FILEHANDLING_SRC_KERML_KERMLBISONPARSER_H_INCLUDED
// "%code requires" blocks.
#line 16 "/Users/herzog/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.y"

    #include "KerMLFlexScanner.h"

#line 53 "/Users/herzog/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.h"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 5 "/Users/herzog/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.y"
namespace KerML { namespace Parser {
#line 189 "/Users/herzog/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.h"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // abstract_modifier
      // all_modifier
      char dummy1[sizeof (bool)];

      // DECIMAL_VALUE
      // EXPONENTIAL_VALUE
      char dummy2[sizeof (double)];

      // NUMBER
      char dummy3[sizeof (int)];

      // BASIC_NAME
      // SINGLE_LINE_COMMENT
      // UNRESTRICTED_NAME
      // BLOCK_COMMENT
      // STRING
      // type_prefix
      // prefix_metadata_annotation
      // qualified_name
      // qualified_name_tail
      // identification
      // mutliplicity_bounds
      // specialization_option
      // conjugation_option
      // type_body
      // relationship_body
      // from_option
      // comment_option
      // specific_type
      // general_type
      char dummy4[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    BASIC_NAME = 258,              // BASIC_NAME
    SINGLE_LINE_COMMENT = 259,     // SINGLE_LINE_COMMENT
    UNRESTRICTED_NAME = 260,       // UNRESTRICTED_NAME
    BLOCK_COMMENT = 261,           // BLOCK_COMMENT
    DECIMAL_VALUE = 262,           // DECIMAL_VALUE
    EXPONENTIAL_VALUE = 263,       // EXPONENTIAL_VALUE
    NUMBER = 264,                  // NUMBER
    SYMBOL_DOT_QUESTION = 265,     // SYMBOL_DOT_QUESTION
    SYMBOL_DQUESTION = 266,        // SYMBOL_DQUESTION
    SYMBOL_QUESTION = 267,         // SYMBOL_QUESTION
    SYMBOL_GREATER_EQUALS = 268,   // SYMBOL_GREATER_EQUALS
    SYMBOL_GREATER = 269,          // SYMBOL_GREATER
    SYMBOL_IFF_NOT_EQUALS = 270,   // SYMBOL_IFF_NOT_EQUALS
    SYMBOL_NOT_EQUALS = 271,       // SYMBOL_NOT_EQUALS
    SYMBOL_IFF_EQUALS = 272,       // SYMBOL_IFF_EQUALS
    SYMBOL_EQUALS = 273,           // SYMBOL_EQUALS
    SYMBOL_DEF_ASSIGN = 274,       // SYMBOL_DEF_ASSIGN
    SYMBOL_ASSIGN = 275,           // SYMBOL_ASSIGN
    SYMBOL_SMALLER_EQUAL = 276,    // SYMBOL_SMALLER_EQUAL
    SYMBOL_SMALLER = 277,          // SYMBOL_SMALLER
    SYMBOL_DDOT = 278,             // SYMBOL_DDOT
    SYMBOL_DOT = 279,              // SYMBOL_DOT
    SYMBOL_ARROOW = 280,           // SYMBOL_ARROOW
    SYMBOL_SLASH = 281,            // SYMBOL_SLASH
    SYMBOL_MINUS = 282,            // SYMBOL_MINUS
    SYMBOL_PLUS = 283,             // SYMBOL_PLUS
    SYMBOL_DOUBLE_STAR = 284,      // SYMBOL_DOUBLE_STAR
    SYMBOL_VERTICAL_LINE = 285,    // SYMBOL_VERTICAL_LINE
    SYMBOL_UPPER = 286,            // SYMBOL_UPPER
    SYMBOL_AND = 287,              // SYMBOL_AND
    SYMBOL_MOD = 288,              // SYMBOL_MOD
    SYMBOL_HASHTAG = 289,          // SYMBOL_HASHTAG
    SYMBOL_AT = 290,               // SYMBOL_AT
    SYMBOL_COMMA = 291,            // SYMBOL_COMMA
    SYMBOL_SQUARE_BRACKET_CLOSE = 292, // SYMBOL_SQUARE_BRACKET_CLOSE
    SYMBOL_SQUARE_BRACKET_OPEN = 293, // SYMBOL_SQUARE_BRACKET_OPEN
    SYMBOL_CURLY_BRACKET_CLOSE = 294, // SYMBOL_CURLY_BRACKET_CLOSE
    SYMBOL_CURLY_BRACKET_OPEN = 295, // SYMBOL_CURLY_BRACKET_OPEN
    SYMBOL_ROUND_BRACKET_CLOSE = 296, // SYMBOL_ROUND_BRACKET_CLOSE
    SYMBOL_ROUND_BRACKET_OPEN = 297, // SYMBOL_ROUND_BRACKET_OPEN
    SYMBOL_CONJUNGATES = 298,      // SYMBOL_CONJUNGATES
    SYMBOL_REDEFINES = 299,        // SYMBOL_REDEFINES
    SYMBOL_REFERENCES = 300,       // SYMBOL_REFERENCES
    SYMBOL_SPECIALIZES = 301,      // SYMBOL_SPECIALIZES
    SYMBOL_TYPED_BY = 302,         // SYMBOL_TYPED_BY
    SYMBOL_NAMESPACE_SUBSET = 303, // SYMBOL_NAMESPACE_SUBSET
    SYMBOL_STAR = 304,             // SYMBOL_STAR
    SYMBOL_STATEMENT_DELIMITER = 305, // SYMBOL_STATEMENT_DELIMITER
    STRING = 306,                  // STRING
    KEYWORD_CONJUGATION = 307,     // KEYWORD_CONJUGATION
    KEYWORD_META = 308,            // KEYWORD_META
    KEYWORD_CONSTANT = 309,        // KEYWORD_CONSTANT
    KEYWORD_LIBRARY = 310,         // KEYWORD_LIBRARY
    KEYWORD_STANDARD = 311,        // KEYWORD_STANDARD
    KEYWORD_LOCALE = 312,          // KEYWORD_LOCALE
    KEYWORD_VAR = 313,             // KEYWORD_VAR
    KEYWORD_XOR = 314,             // KEYWORD_XOR
    KEYWORD_UNIONS = 315,          // KEYWORD_UNIONS
    KEYWORD_TYPING = 316,          // KEYWORD_TYPING
    KEYWORD_TYPED = 317,           // KEYWORD_TYPED
    KEYWORD_TYPE = 318,            // KEYWORD_TYPE
    KEYWORD_TRUE = 319,            // KEYWORD_TRUE
    KEYWORD_TO = 320,              // KEYWORD_TO
    KEYWORD_THEN = 321,            // KEYWORD_THEN
    KEYWORD_SUCCSESSION = 322,     // KEYWORD_SUCCSESSION
    KEYWORD_SUBTYPE = 323,         // KEYWORD_SUBTYPE
    KEYWORD_SUBSETS = 324,         // KEYWORD_SUBSETS
    KEYWORD_SUBSET = 325,          // KEYWORD_SUBSET
    KEYWORD_SUBCLASSIFIER = 326,   // KEYWORD_SUBCLASSIFIER
    KEYWORD_STRUCT = 327,          // KEYWORD_STRUCT
    KEYWORD_STEP = 328,            // KEYWORD_STEP
    KEYWORD_SPECIALIZES = 329,     // KEYWORD_SPECIALIZES
    KEYWORD_SPECILIZATION = 330,   // KEYWORD_SPECILIZATION
    KEYWORD_RETURN = 331,          // KEYWORD_RETURN
    KEYWORD_REP = 332,             // KEYWORD_REP
    KEYWORD_REFERENCES = 333,      // KEYWORD_REFERENCES
    KEYWORD_REDEFINITION = 334,    // KEYWORD_REDEFINITION
    KEYWORD_REDEFINES = 335,       // KEYWORD_REDEFINES
    KEYWORD_READONLY = 336,        // KEYWORD_READONLY
    KEYWORD_PUBLIC = 337,          // KEYWORD_PUBLIC
    KEYWORD_PROTECTED = 338,       // KEYWORD_PROTECTED
    KEYWORD_PRIVATE = 339,         // KEYWORD_PRIVATE
    KEYWORD_PREDICATE = 340,       // KEYWORD_PREDICATE
    KEYWORD_PORTION = 341,         // KEYWORD_PORTION
    KEYWORD_PACKAGE = 342,         // KEYWORD_PACKAGE
    KEYWORD_OUT = 343,             // KEYWORD_OUT
    KEYWORD_ORDERED = 344,         // KEYWORD_ORDERED
    KEYWORD_OR = 345,              // KEYWORD_OR
    KEYWORD_OF = 346,              // KEYWORD_OF
    KEYWORD_NULL = 347,            // KEYWORD_NULL
    KEYWORD_NOT = 348,             // KEYWORD_NOT
    KEYWORD_NONUNIQUE = 349,       // KEYWORD_NONUNIQUE
    KEYWORD_NAMESPACE = 350,       // KEYWORD_NAMESPACE
    KEYWORD_MULTIPLICITY = 351,    // KEYWORD_MULTIPLICITY
    KEYWORD_METADATA = 352,        // KEYWORD_METADATA
    KEYWORD_METACLASS = 353,       // KEYWORD_METACLASS
    KEYWORD_MEMBER = 354,          // KEYWORD_MEMBER
    KEYWORD_LANGUAGE = 355,        // KEYWORD_LANGUAGE
    KEYWORD_ISTYPE = 356,          // KEYWORD_ISTYPE
    KEYWORD_INVERTING = 357,       // KEYWORD_INVERTING
    KEYWORD_INVERSE = 358,         // KEYWORD_INVERSE
    KEYWORD_INV = 359,             // KEYWORD_INV
    KEYWORD_INTERACTION = 360,     // KEYWORD_INTERACTION
    KEYWORD_INOUT = 361,           // KEYWORD_INOUT
    KEYWORD_IN = 362,              // KEYWORD_IN
    KEYWORD_IMPORT = 363,          // KEYWORD_IMPORT
    KEYWORD_IMPLIES = 364,         // KEYWORD_IMPLIES
    KEYWORD_INTERSECTS = 365,      // KEYWORD_INTERSECTS
    KEYWORD_IF = 366,              // KEYWORD_IF
    KEYWORD_HASTYPE = 367,         // KEYWORD_HASTYPE
    KEYWORD_FUNCTION = 368,        // KEYWORD_FUNCTION
    KEYWORD_FROM = 369,            // KEYWORD_FROM
    KEYWORD_FOR = 370,             // KEYWORD_FOR
    KEYWORD_FLOW = 371,            // KEYWORD_FLOW
    KEYWORD_FIRST = 372,           // KEYWORD_FIRST
    KEYWORD_FILTER = 373,          // KEYWORD_FILTER
    KEYWORD_FEATURING = 374,       // KEYWORD_FEATURING
    KEYWORD_FEATURED = 375,        // KEYWORD_FEATURED
    KEYWORD_FEATURE = 376,         // KEYWORD_FEATURE
    KEYWORD_FALSE = 377,           // KEYWORD_FALSE
    KEYWORD_EXPR = 378,            // KEYWORD_EXPR
    KEYWORD_END = 379,             // KEYWORD_END
    KEYWORD_ELSE = 380,            // KEYWORD_ELSE
    KEYWORD_DOC = 381,             // KEYWORD_DOC
    KEYWORD_DISJOINT = 382,        // KEYWORD_DISJOINT
    KEYWORD_DISJOINING = 383,      // KEYWORD_DISJOINING
    KEYWORD_DIFFERENCES = 384,     // KEYWORD_DIFFERENCES
    KEYWORD_DERIVED = 385,         // KEYWORD_DERIVED
    KEYWORD_DEPENDENCY = 386,      // KEYWORD_DEPENDENCY
    KEYWORD_DEFAULT = 387,         // KEYWORD_DEFAULT
    KEYWORD_DATATYPE = 388,        // KEYWORD_DATATYPE
    KEYWORD_CONNECTOR = 389,       // KEYWORD_CONNECTOR
    KEYWORD_CONJUGATES = 390,      // KEYWORD_CONJUGATES
    KEYWORD_CONJUGATE = 391,       // KEYWORD_CONJUGATE
    KEYWORD_COMPOSITE = 392,       // KEYWORD_COMPOSITE
    KEYWORD_COMMENT = 393,         // KEYWORD_COMMENT
    KEYWORD_CLASSIFIER = 394,      // KEYWORD_CLASSIFIER
    KEYWORD_CLASS = 395,           // KEYWORD_CLASS
    KEYWORD_CHAINS = 396,          // KEYWORD_CHAINS
    KEYWORD_BY = 397,              // KEYWORD_BY
    KEYWORD_BOOL = 398,            // KEYWORD_BOOL
    KEYWORD_BINDING = 399,         // KEYWORD_BINDING
    KEYWORD_BEHAVIOR = 400,        // KEYWORD_BEHAVIOR
    KEYWORD_ASSOC = 401,           // KEYWORD_ASSOC
    KEYWORD_AS = 402,              // KEYWORD_AS
    KEYWORD_AND = 403,             // KEYWORD_AND
    KEYWORD_ALL = 404,             // KEYWORD_ALL
    KEYWORD_ALIAS = 405,           // KEYWORD_ALIAS
    KEYWORD_ABSTRACT = 406,        // KEYWORD_ABSTRACT
    KEYWORD_ABOUT = 407,           // KEYWORD_ABOUT
    TPLUS = 408,                   // TPLUS
    TMINUS = 409,                  // TMINUS
    TMUL = 410,                    // TMUL
    TDIV = 411                     // TDIV
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 158, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_BASIC_NAME = 3,                        // BASIC_NAME
        S_SINGLE_LINE_COMMENT = 4,               // SINGLE_LINE_COMMENT
        S_UNRESTRICTED_NAME = 5,                 // UNRESTRICTED_NAME
        S_BLOCK_COMMENT = 6,                     // BLOCK_COMMENT
        S_DECIMAL_VALUE = 7,                     // DECIMAL_VALUE
        S_EXPONENTIAL_VALUE = 8,                 // EXPONENTIAL_VALUE
        S_NUMBER = 9,                            // NUMBER
        S_SYMBOL_DOT_QUESTION = 10,              // SYMBOL_DOT_QUESTION
        S_SYMBOL_DQUESTION = 11,                 // SYMBOL_DQUESTION
        S_SYMBOL_QUESTION = 12,                  // SYMBOL_QUESTION
        S_SYMBOL_GREATER_EQUALS = 13,            // SYMBOL_GREATER_EQUALS
        S_SYMBOL_GREATER = 14,                   // SYMBOL_GREATER
        S_SYMBOL_IFF_NOT_EQUALS = 15,            // SYMBOL_IFF_NOT_EQUALS
        S_SYMBOL_NOT_EQUALS = 16,                // SYMBOL_NOT_EQUALS
        S_SYMBOL_IFF_EQUALS = 17,                // SYMBOL_IFF_EQUALS
        S_SYMBOL_EQUALS = 18,                    // SYMBOL_EQUALS
        S_SYMBOL_DEF_ASSIGN = 19,                // SYMBOL_DEF_ASSIGN
        S_SYMBOL_ASSIGN = 20,                    // SYMBOL_ASSIGN
        S_SYMBOL_SMALLER_EQUAL = 21,             // SYMBOL_SMALLER_EQUAL
        S_SYMBOL_SMALLER = 22,                   // SYMBOL_SMALLER
        S_SYMBOL_DDOT = 23,                      // SYMBOL_DDOT
        S_SYMBOL_DOT = 24,                       // SYMBOL_DOT
        S_SYMBOL_ARROOW = 25,                    // SYMBOL_ARROOW
        S_SYMBOL_SLASH = 26,                     // SYMBOL_SLASH
        S_SYMBOL_MINUS = 27,                     // SYMBOL_MINUS
        S_SYMBOL_PLUS = 28,                      // SYMBOL_PLUS
        S_SYMBOL_DOUBLE_STAR = 29,               // SYMBOL_DOUBLE_STAR
        S_SYMBOL_VERTICAL_LINE = 30,             // SYMBOL_VERTICAL_LINE
        S_SYMBOL_UPPER = 31,                     // SYMBOL_UPPER
        S_SYMBOL_AND = 32,                       // SYMBOL_AND
        S_SYMBOL_MOD = 33,                       // SYMBOL_MOD
        S_SYMBOL_HASHTAG = 34,                   // SYMBOL_HASHTAG
        S_SYMBOL_AT = 35,                        // SYMBOL_AT
        S_SYMBOL_COMMA = 36,                     // SYMBOL_COMMA
        S_SYMBOL_SQUARE_BRACKET_CLOSE = 37,      // SYMBOL_SQUARE_BRACKET_CLOSE
        S_SYMBOL_SQUARE_BRACKET_OPEN = 38,       // SYMBOL_SQUARE_BRACKET_OPEN
        S_SYMBOL_CURLY_BRACKET_CLOSE = 39,       // SYMBOL_CURLY_BRACKET_CLOSE
        S_SYMBOL_CURLY_BRACKET_OPEN = 40,        // SYMBOL_CURLY_BRACKET_OPEN
        S_SYMBOL_ROUND_BRACKET_CLOSE = 41,       // SYMBOL_ROUND_BRACKET_CLOSE
        S_SYMBOL_ROUND_BRACKET_OPEN = 42,        // SYMBOL_ROUND_BRACKET_OPEN
        S_SYMBOL_CONJUNGATES = 43,               // SYMBOL_CONJUNGATES
        S_SYMBOL_REDEFINES = 44,                 // SYMBOL_REDEFINES
        S_SYMBOL_REFERENCES = 45,                // SYMBOL_REFERENCES
        S_SYMBOL_SPECIALIZES = 46,               // SYMBOL_SPECIALIZES
        S_SYMBOL_TYPED_BY = 47,                  // SYMBOL_TYPED_BY
        S_SYMBOL_NAMESPACE_SUBSET = 48,          // SYMBOL_NAMESPACE_SUBSET
        S_SYMBOL_STAR = 49,                      // SYMBOL_STAR
        S_SYMBOL_STATEMENT_DELIMITER = 50,       // SYMBOL_STATEMENT_DELIMITER
        S_STRING = 51,                           // STRING
        S_KEYWORD_CONJUGATION = 52,              // KEYWORD_CONJUGATION
        S_KEYWORD_META = 53,                     // KEYWORD_META
        S_KEYWORD_CONSTANT = 54,                 // KEYWORD_CONSTANT
        S_KEYWORD_LIBRARY = 55,                  // KEYWORD_LIBRARY
        S_KEYWORD_STANDARD = 56,                 // KEYWORD_STANDARD
        S_KEYWORD_LOCALE = 57,                   // KEYWORD_LOCALE
        S_KEYWORD_VAR = 58,                      // KEYWORD_VAR
        S_KEYWORD_XOR = 59,                      // KEYWORD_XOR
        S_KEYWORD_UNIONS = 60,                   // KEYWORD_UNIONS
        S_KEYWORD_TYPING = 61,                   // KEYWORD_TYPING
        S_KEYWORD_TYPED = 62,                    // KEYWORD_TYPED
        S_KEYWORD_TYPE = 63,                     // KEYWORD_TYPE
        S_KEYWORD_TRUE = 64,                     // KEYWORD_TRUE
        S_KEYWORD_TO = 65,                       // KEYWORD_TO
        S_KEYWORD_THEN = 66,                     // KEYWORD_THEN
        S_KEYWORD_SUCCSESSION = 67,              // KEYWORD_SUCCSESSION
        S_KEYWORD_SUBTYPE = 68,                  // KEYWORD_SUBTYPE
        S_KEYWORD_SUBSETS = 69,                  // KEYWORD_SUBSETS
        S_KEYWORD_SUBSET = 70,                   // KEYWORD_SUBSET
        S_KEYWORD_SUBCLASSIFIER = 71,            // KEYWORD_SUBCLASSIFIER
        S_KEYWORD_STRUCT = 72,                   // KEYWORD_STRUCT
        S_KEYWORD_STEP = 73,                     // KEYWORD_STEP
        S_KEYWORD_SPECIALIZES = 74,              // KEYWORD_SPECIALIZES
        S_KEYWORD_SPECILIZATION = 75,            // KEYWORD_SPECILIZATION
        S_KEYWORD_RETURN = 76,                   // KEYWORD_RETURN
        S_KEYWORD_REP = 77,                      // KEYWORD_REP
        S_KEYWORD_REFERENCES = 78,               // KEYWORD_REFERENCES
        S_KEYWORD_REDEFINITION = 79,             // KEYWORD_REDEFINITION
        S_KEYWORD_REDEFINES = 80,                // KEYWORD_REDEFINES
        S_KEYWORD_READONLY = 81,                 // KEYWORD_READONLY
        S_KEYWORD_PUBLIC = 82,                   // KEYWORD_PUBLIC
        S_KEYWORD_PROTECTED = 83,                // KEYWORD_PROTECTED
        S_KEYWORD_PRIVATE = 84,                  // KEYWORD_PRIVATE
        S_KEYWORD_PREDICATE = 85,                // KEYWORD_PREDICATE
        S_KEYWORD_PORTION = 86,                  // KEYWORD_PORTION
        S_KEYWORD_PACKAGE = 87,                  // KEYWORD_PACKAGE
        S_KEYWORD_OUT = 88,                      // KEYWORD_OUT
        S_KEYWORD_ORDERED = 89,                  // KEYWORD_ORDERED
        S_KEYWORD_OR = 90,                       // KEYWORD_OR
        S_KEYWORD_OF = 91,                       // KEYWORD_OF
        S_KEYWORD_NULL = 92,                     // KEYWORD_NULL
        S_KEYWORD_NOT = 93,                      // KEYWORD_NOT
        S_KEYWORD_NONUNIQUE = 94,                // KEYWORD_NONUNIQUE
        S_KEYWORD_NAMESPACE = 95,                // KEYWORD_NAMESPACE
        S_KEYWORD_MULTIPLICITY = 96,             // KEYWORD_MULTIPLICITY
        S_KEYWORD_METADATA = 97,                 // KEYWORD_METADATA
        S_KEYWORD_METACLASS = 98,                // KEYWORD_METACLASS
        S_KEYWORD_MEMBER = 99,                   // KEYWORD_MEMBER
        S_KEYWORD_LANGUAGE = 100,                // KEYWORD_LANGUAGE
        S_KEYWORD_ISTYPE = 101,                  // KEYWORD_ISTYPE
        S_KEYWORD_INVERTING = 102,               // KEYWORD_INVERTING
        S_KEYWORD_INVERSE = 103,                 // KEYWORD_INVERSE
        S_KEYWORD_INV = 104,                     // KEYWORD_INV
        S_KEYWORD_INTERACTION = 105,             // KEYWORD_INTERACTION
        S_KEYWORD_INOUT = 106,                   // KEYWORD_INOUT
        S_KEYWORD_IN = 107,                      // KEYWORD_IN
        S_KEYWORD_IMPORT = 108,                  // KEYWORD_IMPORT
        S_KEYWORD_IMPLIES = 109,                 // KEYWORD_IMPLIES
        S_KEYWORD_INTERSECTS = 110,              // KEYWORD_INTERSECTS
        S_KEYWORD_IF = 111,                      // KEYWORD_IF
        S_KEYWORD_HASTYPE = 112,                 // KEYWORD_HASTYPE
        S_KEYWORD_FUNCTION = 113,                // KEYWORD_FUNCTION
        S_KEYWORD_FROM = 114,                    // KEYWORD_FROM
        S_KEYWORD_FOR = 115,                     // KEYWORD_FOR
        S_KEYWORD_FLOW = 116,                    // KEYWORD_FLOW
        S_KEYWORD_FIRST = 117,                   // KEYWORD_FIRST
        S_KEYWORD_FILTER = 118,                  // KEYWORD_FILTER
        S_KEYWORD_FEATURING = 119,               // KEYWORD_FEATURING
        S_KEYWORD_FEATURED = 120,                // KEYWORD_FEATURED
        S_KEYWORD_FEATURE = 121,                 // KEYWORD_FEATURE
        S_KEYWORD_FALSE = 122,                   // KEYWORD_FALSE
        S_KEYWORD_EXPR = 123,                    // KEYWORD_EXPR
        S_KEYWORD_END = 124,                     // KEYWORD_END
        S_KEYWORD_ELSE = 125,                    // KEYWORD_ELSE
        S_KEYWORD_DOC = 126,                     // KEYWORD_DOC
        S_KEYWORD_DISJOINT = 127,                // KEYWORD_DISJOINT
        S_KEYWORD_DISJOINING = 128,              // KEYWORD_DISJOINING
        S_KEYWORD_DIFFERENCES = 129,             // KEYWORD_DIFFERENCES
        S_KEYWORD_DERIVED = 130,                 // KEYWORD_DERIVED
        S_KEYWORD_DEPENDENCY = 131,              // KEYWORD_DEPENDENCY
        S_KEYWORD_DEFAULT = 132,                 // KEYWORD_DEFAULT
        S_KEYWORD_DATATYPE = 133,                // KEYWORD_DATATYPE
        S_KEYWORD_CONNECTOR = 134,               // KEYWORD_CONNECTOR
        S_KEYWORD_CONJUGATES = 135,              // KEYWORD_CONJUGATES
        S_KEYWORD_CONJUGATE = 136,               // KEYWORD_CONJUGATE
        S_KEYWORD_COMPOSITE = 137,               // KEYWORD_COMPOSITE
        S_KEYWORD_COMMENT = 138,                 // KEYWORD_COMMENT
        S_KEYWORD_CLASSIFIER = 139,              // KEYWORD_CLASSIFIER
        S_KEYWORD_CLASS = 140,                   // KEYWORD_CLASS
        S_KEYWORD_CHAINS = 141,                  // KEYWORD_CHAINS
        S_KEYWORD_BY = 142,                      // KEYWORD_BY
        S_KEYWORD_BOOL = 143,                    // KEYWORD_BOOL
        S_KEYWORD_BINDING = 144,                 // KEYWORD_BINDING
        S_KEYWORD_BEHAVIOR = 145,                // KEYWORD_BEHAVIOR
        S_KEYWORD_ASSOC = 146,                   // KEYWORD_ASSOC
        S_KEYWORD_AS = 147,                      // KEYWORD_AS
        S_KEYWORD_AND = 148,                     // KEYWORD_AND
        S_KEYWORD_ALL = 149,                     // KEYWORD_ALL
        S_KEYWORD_ALIAS = 150,                   // KEYWORD_ALIAS
        S_KEYWORD_ABSTRACT = 151,                // KEYWORD_ABSTRACT
        S_KEYWORD_ABOUT = 152,                   // KEYWORD_ABOUT
        S_TPLUS = 153,                           // TPLUS
        S_TMINUS = 154,                          // TMINUS
        S_TMUL = 155,                            // TMUL
        S_TDIV = 156,                            // TDIV
        S_157_ = 157,                            // ';'
        S_YYACCEPT = 158,                        // $accept
        S_model = 159,                           // model
        S_elements = 160,                        // elements
        S_element = 161,                         // element
        S_non_feature_element = 162,             // non_feature_element
        S_feature_element = 163,                 // feature_element
        S_additional_options = 164,              // additional_options
        S_type_prefix = 165,                     // type_prefix
        S_prefix_metadata_annotation = 166,      // prefix_metadata_annotation
        S_abstract_modifier = 167,               // abstract_modifier
        S_qualified_name = 168,                  // qualified_name
        S_qualified_name_tail = 169,             // qualified_name_tail
        S_all_modifier = 170,                    // all_modifier
        S_identification = 171,                  // identification
        S_mutliplicity_bounds = 172,             // mutliplicity_bounds
        S_specialization_option = 173,           // specialization_option
        S_conjugation_option = 174,              // conjugation_option
        S_type_body = 175,                       // type_body
        S_type_body_elements = 176,              // type_body_elements
        S_type_body_element = 177,               // type_body_element
        S_type = 178,                            // type
        S_type_relationship_part_option = 179,   // type_relationship_part_option
        S_type_relationship_part = 180,          // type_relationship_part
        S_disjoining_part = 181,                 // disjoining_part
        S_disjoining_part_multiplicity = 182,    // disjoining_part_multiplicity
        S_unioning_part = 183,                   // unioning_part
        S_unioning_part_multiplicity = 184,      // unioning_part_multiplicity
        S_intersecting_part = 185,               // intersecting_part
        S_intersecting_part_multiplicity = 186,  // intersecting_part_multiplicity
        S_differencing_part = 187,               // differencing_part
        S_differencing_part_multiplicity = 188,  // differencing_part_multiplicity
        S_relationship_body = 189,               // relationship_body
        S_relationship_body_elements = 190,      // relationship_body_elements
        S_relationship_body_element = 191,       // relationship_body_element
        S_owned_related_element = 192,           // owned_related_element
        S_from_option = 193,                     // from_option
        S_dependency = 194,                      // dependency
        S_owned_annotation = 195,                // owned_annotation
        S_about_option = 196,                    // about_option
        S_locale_option = 197,                   // locale_option
        S_annotating_element = 198,              // annotating_element
        S_comment_option = 199,                  // comment_option
        S_comment = 200,                         // comment
        S_documentation = 201,                   // documentation
        S_textual_representation = 202,          // textual_representation
        S_namespace = 203,                       // namespace
        S_namespace_body = 204,                  // namespace_body
        S_namesapce_body_elements = 205,         // namesapce_body_elements
        S_member_prefix = 206,                   // member_prefix
        S_visiblity_indicator = 207,             // visiblity_indicator
        S_import = 208,                          // import
        S_import_declaration = 209,              // import_declaration
        S_complete_namespace_import = 210,       // complete_namespace_import
        S_non_feature_member = 211,              // non_feature_member
        S_alias_member = 212,                    // alias_member
        S_specializes = 213,                     // specializes
        S_specialization = 214,                  // specialization
        S_specific_type = 215,                   // specific_type
        S_general_type = 216,                    // general_type
        S_conjunction = 217,                     // conjunction
        S_owned_conjungation = 218,              // owned_conjungation
        S_conjugation_part = 219,                // conjugation_part
        S_disjoining = 220,                      // disjoining
        S_owned_disjoining = 221,                // owned_disjoining
        S_unioning = 222,                        // unioning
        S_intersecting = 223,                    // intersecting
        S_differencing = 224,                    // differencing
        S_feature_member = 225,                  // feature_member
        S_type_feature_member = 226,             // type_feature_member
        S_owned_feature_member = 227,            // owned_feature_member
        S_classifier = 228,                      // classifier
        S_superclassing_conjunction_option = 229, // superclassing_conjunction_option
        S_classifier_declaration = 230,          // classifier_declaration
        S_subclassification = 231,               // subclassification
        S_superclassing_part = 232,              // superclassing_part
        S_multible_superclasses_option = 233,    // multible_superclasses_option
        S_owned_subclassification = 234,         // owned_subclassification
        S_feature = 235,                         // feature
        S_feature_prefix = 236,                  // feature_prefix
        S_abstract_option = 237,                 // abstract_option
        S_readonly_option = 238,                 // readonly_option
        S_derived_option = 239,                  // derived_option
        S_end_option = 240,                      // end_option
        S_feature_type_option = 241,             // feature_type_option
        S_feature_descriptor = 242,              // feature_descriptor
        S_subsettings_option = 243,              // subsettings_option
        S_feature_assignment_option = 244,       // feature_assignment_option
        S_feature_value_option = 245,            // feature_value_option
        S_feature_direction_option = 246,        // feature_direction_option
        S_feature_declaration = 247,             // feature_declaration
        S_feature_identification = 248,          // feature_identification
        S_feature_specialization_conjungation_option = 249, // feature_specialization_conjungation_option
        S_feature_relationship_part_option = 250, // feature_relationship_part_option
        S_feature_relationship_part = 251,       // feature_relationship_part
        S_chaining_part = 252,                   // chaining_part
        S_inverting_part = 253,                  // inverting_part
        S_type_featuring_part = 254,             // type_featuring_part
        S_type_featuting_part_multiplicity = 255, // type_featuting_part_multiplicity
        S_feature_specialization_part = 256,     // feature_specialization_part
        S_feature_specialization_option = 257,   // feature_specialization_option
        S_typings = 258,                         // typings
        S_typed_by = 259,                        // typed_by
        S_typed_by_mutliplicity = 260,           // typed_by_mutliplicity
        S_subsettings = 261,                     // subsettings
        S_subsets = 262,                         // subsets
        S_subsetting_multiplictiy = 263,         // subsetting_multiplictiy
        S_multiplicity_part = 264,               // multiplicity_part
        S_references = 265,                      // references
        S_feature_typing = 266,                  // feature_typing
        S_typing_option = 267,                   // typing_option
        S_owned_feature_typing = 268,            // owned_feature_typing
        S_subsetting = 269,                      // subsetting
        S_subset_option = 270,                   // subset_option
        S_typed_by_option = 271,                 // typed_by_option
        S_owned_subsetting_option = 272,         // owned_subsetting_option
        S_owned_subsetting = 273,                // owned_subsetting
        S_owned_reference_subsettings = 274,     // owned_reference_subsettings
        S_redefinition = 275,                    // redefinition
        S_redefinition_option = 276,             // redefinition_option
        S_subsets_option = 277,                  // subsets_option
        S_owned_feature_chain = 278,             // owned_feature_chain
        S_feature_chain = 279,                   // feature_chain
        S_feature_chain_part = 280,              // feature_chain_part
        S_feature_inverting = 281,               // feature_inverting
        S_inverting_option = 282,                // inverting_option
        S_type_featuring = 283,                  // type_featuring
        S_of_option = 284,                       // of_option
        S_owned_type_featuring = 285,            // owned_type_featuring
        S_data_type = 286,                       // data_type
        S_class = 287,                           // class
        S_structure = 288,                       // structure
        S_association = 289,                     // association
        S_association_structure = 290,           // association_structure
        S_type_prefix_option = 291,              // type_prefix_option
        S_connector = 292,                       // connector
        S_connector_declaration = 293,           // connector_declaration
        S_binary_connector_declaration = 294,    // binary_connector_declaration
        S_nary_connector_declaration = 295,      // nary_connector_declaration
        S_nary_connector_declaration_additional_member = 296, // nary_connector_declaration_additional_member
        S_connector_end_member = 297,            // connector_end_member
        S_connector_end = 298,                   // connector_end
        S_name_reference_option = 299,           // name_reference_option
        S_binding_connector = 300,               // binding_connector
        S_binding_connector_declaration = 301,   // binding_connector_declaration
        S_connector_end_member_of_option = 302,  // connector_end_member_of_option
        S_succession = 303,                      // succession
        S_succession_declaration = 304,          // succession_declaration
        S_connector_end_member_first_option = 305, // connector_end_member_first_option
        S_behavior = 306,                        // behavior
        S_step = 307,                            // step
        S_function = 308,                        // function
        S_function_body = 309,                   // function_body
        S_function_body_part_multiplicity = 310, // function_body_part_multiplicity
        S_function_body_part = 311,              // function_body_part
        S_return_feature_element = 312,          // return_feature_element
        S_result_expression_member = 313,        // result_expression_member
        S_expression = 314,                      // expression
        S_value_part_option = 315,               // value_part_option
        S_predicate = 316,                       // predicate
        S_boolean_expression = 317,              // boolean_expression
        S_invariant = 318,                       // invariant
        S_invariant_option = 319,                // invariant_option
        S_owned_expression_reference = 320,      // owned_expression_reference
        S_owned_expression_member = 321,         // owned_expression_member
        S_owned_expressions = 322,               // owned_expressions
        S_owned_expression = 323,                // owned_expression
        S_conditional_expression = 324,          // conditional_expression
        S_conditional_binary_operator_expression = 325, // conditional_binary_operator_expression
        S_conditional_binary_operator = 326,     // conditional_binary_operator
        S_binary_operator_expression = 327,      // binary_operator_expression
        S_binary_operator = 328,                 // binary_operator
        S_unary_operator_expression = 329,       // unary_operator_expression
        S_unary_operator = 330,                  // unary_operator
        S_classification_expression = 331,       // classification_expression
        S_classification_test_operator = 332,    // classification_test_operator
        S_metaclassification_expression = 333,   // metaclassification_expression
        S_argument_member = 334,                 // argument_member
        S_argument = 335,                        // argument
        S_argument_value = 336,                  // argument_value
        S_argument_expression_member = 337,      // argument_expression_member
        S_argument_expression = 338,             // argument_expression
        S_argument_expression_value = 339,       // argument_expression_value
        S_metadata_argument_member = 340,        // metadata_argument_member
        S_metadata_argument = 341,               // metadata_argument
        S_metadata_value = 342,                  // metadata_value
        S_metadata_reference = 343,              // metadata_reference
        S_metadataclassification_test_operator = 344, // metadataclassification_test_operator
        S_extend_expression = 345,               // extend_expression
        S_type_reference_member = 346,           // type_reference_member
        S_type_result_member = 347,              // type_result_member
        S_type_reference = 348,                  // type_reference
        S_reference_typing = 349,                // reference_typing
        S_primary_expression = 350,              // primary_expression
        S_non_feature_chain_primary_expression = 351, // non_feature_chain_primary_expression
        S_bracket_expression = 352,              // bracket_expression
        S_index_expression = 353,                // index_expression
        S_sequence_expression = 354,             // sequence_expression
        S_sequence_expression_list = 355,        // sequence_expression_list
        S_sequence_operator_expression = 356,    // sequence_operator_expression
        S_sequence_expression_list_member = 357, // sequence_expression_list_member
        S_feature_chain_expression = 358,        // feature_chain_expression
        S_collect_expression = 359,              // collect_expression
        S_select_expression = 360,               // select_expression
        S_function_operation_expression = 361,   // function_operation_expression
        S_body_argument_member = 362,            // body_argument_member
        S_body_argument = 363,                   // body_argument
        S_body_argument_value = 364,             // body_argument_value
        S_body_expression_member = 365,          // body_expression_member
        S_function_reference_argument_member = 366, // function_reference_argument_member
        S_function_reference_argument = 367,     // function_reference_argument
        S_function_reference_member = 368,       // function_reference_member
        S_function_reference = 369,              // function_reference
        S_feature_chain_member = 370,            // feature_chain_member
        S_owned_feature_chain_member = 371,      // owned_feature_chain_member
        S_base_expression = 372,                 // base_expression
        S_null_expression = 373,                 // null_expression
        S_feature_reference_expression = 374,    // feature_reference_expression
        S_feature_reference_member = 375,        // feature_reference_member
        S_feature_reference = 376,               // feature_reference
        S_metadata_access_expression = 377,      // metadata_access_expression
        S_invocation_expression = 378,           // invocation_expression
        S_internal_invocation_expression = 379,  // internal_invocation_expression
        S_argument_list = 380,                   // argument_list
        S_named_argument_list_option = 381,      // named_argument_list_option
        S_named_argument_list_mutliplicity = 382, // named_argument_list_mutliplicity
        S_positional_argument_list = 383,        // positional_argument_list
        S_positional_argument_list_multible = 384, // positional_argument_list_multible
        S_named_argument_member = 385,           // named_argument_member
        S_named_argument = 386,                  // named_argument
        S_paramenter_redefinition = 387,         // paramenter_redefinition
        S_body_expression = 388,                 // body_expression
        S_expression_body_member = 389,          // expression_body_member
        S_expression_body = 390,                 // expression_body
        S_literal_expression = 391,              // literal_expression
        S_literal_boolean = 392,                 // literal_boolean
        S_boolean_value = 393,                   // boolean_value
        S_literal_string = 394,                  // literal_string
        S_literal_integer = 395,                 // literal_integer
        S_literal_real = 396,                    // literal_real
        S_real_value = 397,                      // real_value
        S_literal_infinity = 398,                // literal_infinity
        S_interaction = 399,                     // interaction
        S_item_flow = 400,                       // item_flow
        S_succession_item_flow = 401,            // succession_item_flow
        S_item_flow_declaration = 402,           // item_flow_declaration
        S_item_flow_of_option = 403,             // item_flow_of_option
        S_item_flow_from_to_option = 404,        // item_flow_from_to_option
        S_item_feature_member = 405,             // item_feature_member
        S_item_feature = 406,                    // item_feature
        S_owned_feature_typing_option = 407,     // owned_feature_typing_option
        S_item_feature_specilization_part = 408, // item_feature_specilization_part
        S_item_flow_end_member = 409,            // item_flow_end_member
        S_item_flow_end = 410,                   // item_flow_end
        S_item_flow_feature_member = 411,        // item_flow_feature_member
        S_item_flow_feature = 412,               // item_flow_feature
        S_item_flow_redefinition = 413,          // item_flow_redefinition
        S_value_part = 414,                      // value_part
        S_feature_value = 415,                   // feature_value
        S_euqals_assign_option = 416,            // euqals_assign_option
        S_feature_assignment = 417,              // feature_assignment
        S_multiplicity = 418,                    // multiplicity
        S_multiplicity_subset = 419,             // multiplicity_subset
        S_multiplicity_range = 420,              // multiplicity_range
        S_multiplicity_bounds = 421,             // multiplicity_bounds
        S_multiplicity_expression_member = 422,  // multiplicity_expression_member
        S_internal_multiplicity_expression_member = 423, // internal_multiplicity_expression_member
        S_metaclass = 424,                       // metaclass
        S_name_option = 425,                     // name_option
        S_meta_specialization_option = 426,      // meta_specialization_option
        S_prefix_metadata_member = 427,          // prefix_metadata_member
        S_prefix_metadata_feature = 428,         // prefix_metadata_feature
        S_metadata_feature = 429,                // metadata_feature
        S_prefix_metadata_member_multiplicity = 430, // prefix_metadata_member_multiplicity
        S_about_annotation = 431,                // about_annotation
        S_about_annotation_mutliplicity = 432,   // about_annotation_mutliplicity
        S_metadata_feature_declaration = 433,    // metadata_feature_declaration
        S_identification_annotation = 434,       // identification_annotation
        S_package = 435,                         // package
        S_library_package = 436,                 // library_package
        S_standard_option = 437,                 // standard_option
        S_package_declaration = 438,             // package_declaration
        S_package_body = 439,                    // package_body
        S_element_filter_members = 440,          // element_filter_members
        S_element_filter_member = 441,           // element_filter_member
        S_meta_assignment = 442                  // meta_assignment
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_abstract_modifier: // abstract_modifier
      case symbol_kind::S_all_modifier: // all_modifier
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_DECIMAL_VALUE: // DECIMAL_VALUE
      case symbol_kind::S_EXPONENTIAL_VALUE: // EXPONENTIAL_VALUE
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_BASIC_NAME: // BASIC_NAME
      case symbol_kind::S_SINGLE_LINE_COMMENT: // SINGLE_LINE_COMMENT
      case symbol_kind::S_UNRESTRICTED_NAME: // UNRESTRICTED_NAME
      case symbol_kind::S_BLOCK_COMMENT: // BLOCK_COMMENT
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_type_prefix: // type_prefix
      case symbol_kind::S_prefix_metadata_annotation: // prefix_metadata_annotation
      case symbol_kind::S_qualified_name: // qualified_name
      case symbol_kind::S_qualified_name_tail: // qualified_name_tail
      case symbol_kind::S_identification: // identification
      case symbol_kind::S_mutliplicity_bounds: // mutliplicity_bounds
      case symbol_kind::S_specialization_option: // specialization_option
      case symbol_kind::S_conjugation_option: // conjugation_option
      case symbol_kind::S_type_body: // type_body
      case symbol_kind::S_relationship_body: // relationship_body
      case symbol_kind::S_from_option: // from_option
      case symbol_kind::S_comment_option: // comment_option
      case symbol_kind::S_specific_type: // specific_type
      case symbol_kind::S_general_type: // general_type
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_abstract_modifier: // abstract_modifier
      case symbol_kind::S_all_modifier: // all_modifier
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_DECIMAL_VALUE: // DECIMAL_VALUE
      case symbol_kind::S_EXPONENTIAL_VALUE: // EXPONENTIAL_VALUE
        value.template destroy< double > ();
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.template destroy< int > ();
        break;

      case symbol_kind::S_BASIC_NAME: // BASIC_NAME
      case symbol_kind::S_SINGLE_LINE_COMMENT: // SINGLE_LINE_COMMENT
      case symbol_kind::S_UNRESTRICTED_NAME: // UNRESTRICTED_NAME
      case symbol_kind::S_BLOCK_COMMENT: // BLOCK_COMMENT
      case symbol_kind::S_STRING: // STRING
      case symbol_kind::S_type_prefix: // type_prefix
      case symbol_kind::S_prefix_metadata_annotation: // prefix_metadata_annotation
      case symbol_kind::S_qualified_name: // qualified_name
      case symbol_kind::S_qualified_name_tail: // qualified_name_tail
      case symbol_kind::S_identification: // identification
      case symbol_kind::S_mutliplicity_bounds: // mutliplicity_bounds
      case symbol_kind::S_specialization_option: // specialization_option
      case symbol_kind::S_conjugation_option: // conjugation_option
      case symbol_kind::S_type_body: // type_body
      case symbol_kind::S_relationship_body: // relationship_body
      case symbol_kind::S_from_option: // from_option
      case symbol_kind::S_comment_option: // comment_option
      case symbol_kind::S_specific_type: // specific_type
      case symbol_kind::S_general_type: // general_type
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const double& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const int& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::string& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    parser (KerMLFlexScanner* lexer_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#else
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BASIC_NAME (std::string v)
      {
        return symbol_type (token::BASIC_NAME, std::move (v));
      }
#else
      static
      symbol_type
      make_BASIC_NAME (const std::string& v)
      {
        return symbol_type (token::BASIC_NAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SINGLE_LINE_COMMENT (std::string v)
      {
        return symbol_type (token::SINGLE_LINE_COMMENT, std::move (v));
      }
#else
      static
      symbol_type
      make_SINGLE_LINE_COMMENT (const std::string& v)
      {
        return symbol_type (token::SINGLE_LINE_COMMENT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNRESTRICTED_NAME (std::string v)
      {
        return symbol_type (token::UNRESTRICTED_NAME, std::move (v));
      }
#else
      static
      symbol_type
      make_UNRESTRICTED_NAME (const std::string& v)
      {
        return symbol_type (token::UNRESTRICTED_NAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BLOCK_COMMENT (std::string v)
      {
        return symbol_type (token::BLOCK_COMMENT, std::move (v));
      }
#else
      static
      symbol_type
      make_BLOCK_COMMENT (const std::string& v)
      {
        return symbol_type (token::BLOCK_COMMENT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DECIMAL_VALUE (double v)
      {
        return symbol_type (token::DECIMAL_VALUE, std::move (v));
      }
#else
      static
      symbol_type
      make_DECIMAL_VALUE (const double& v)
      {
        return symbol_type (token::DECIMAL_VALUE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXPONENTIAL_VALUE (double v)
      {
        return symbol_type (token::EXPONENTIAL_VALUE, std::move (v));
      }
#else
      static
      symbol_type
      make_EXPONENTIAL_VALUE (const double& v)
      {
        return symbol_type (token::EXPONENTIAL_VALUE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUMBER (int v)
      {
        return symbol_type (token::NUMBER, std::move (v));
      }
#else
      static
      symbol_type
      make_NUMBER (const int& v)
      {
        return symbol_type (token::NUMBER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_DOT_QUESTION ()
      {
        return symbol_type (token::SYMBOL_DOT_QUESTION);
      }
#else
      static
      symbol_type
      make_SYMBOL_DOT_QUESTION ()
      {
        return symbol_type (token::SYMBOL_DOT_QUESTION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_DQUESTION ()
      {
        return symbol_type (token::SYMBOL_DQUESTION);
      }
#else
      static
      symbol_type
      make_SYMBOL_DQUESTION ()
      {
        return symbol_type (token::SYMBOL_DQUESTION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_QUESTION ()
      {
        return symbol_type (token::SYMBOL_QUESTION);
      }
#else
      static
      symbol_type
      make_SYMBOL_QUESTION ()
      {
        return symbol_type (token::SYMBOL_QUESTION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_GREATER_EQUALS ()
      {
        return symbol_type (token::SYMBOL_GREATER_EQUALS);
      }
#else
      static
      symbol_type
      make_SYMBOL_GREATER_EQUALS ()
      {
        return symbol_type (token::SYMBOL_GREATER_EQUALS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_GREATER ()
      {
        return symbol_type (token::SYMBOL_GREATER);
      }
#else
      static
      symbol_type
      make_SYMBOL_GREATER ()
      {
        return symbol_type (token::SYMBOL_GREATER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_IFF_NOT_EQUALS ()
      {
        return symbol_type (token::SYMBOL_IFF_NOT_EQUALS);
      }
#else
      static
      symbol_type
      make_SYMBOL_IFF_NOT_EQUALS ()
      {
        return symbol_type (token::SYMBOL_IFF_NOT_EQUALS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_NOT_EQUALS ()
      {
        return symbol_type (token::SYMBOL_NOT_EQUALS);
      }
#else
      static
      symbol_type
      make_SYMBOL_NOT_EQUALS ()
      {
        return symbol_type (token::SYMBOL_NOT_EQUALS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_IFF_EQUALS ()
      {
        return symbol_type (token::SYMBOL_IFF_EQUALS);
      }
#else
      static
      symbol_type
      make_SYMBOL_IFF_EQUALS ()
      {
        return symbol_type (token::SYMBOL_IFF_EQUALS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_EQUALS ()
      {
        return symbol_type (token::SYMBOL_EQUALS);
      }
#else
      static
      symbol_type
      make_SYMBOL_EQUALS ()
      {
        return symbol_type (token::SYMBOL_EQUALS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_DEF_ASSIGN ()
      {
        return symbol_type (token::SYMBOL_DEF_ASSIGN);
      }
#else
      static
      symbol_type
      make_SYMBOL_DEF_ASSIGN ()
      {
        return symbol_type (token::SYMBOL_DEF_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_ASSIGN ()
      {
        return symbol_type (token::SYMBOL_ASSIGN);
      }
#else
      static
      symbol_type
      make_SYMBOL_ASSIGN ()
      {
        return symbol_type (token::SYMBOL_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_SMALLER_EQUAL ()
      {
        return symbol_type (token::SYMBOL_SMALLER_EQUAL);
      }
#else
      static
      symbol_type
      make_SYMBOL_SMALLER_EQUAL ()
      {
        return symbol_type (token::SYMBOL_SMALLER_EQUAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_SMALLER ()
      {
        return symbol_type (token::SYMBOL_SMALLER);
      }
#else
      static
      symbol_type
      make_SYMBOL_SMALLER ()
      {
        return symbol_type (token::SYMBOL_SMALLER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_DDOT ()
      {
        return symbol_type (token::SYMBOL_DDOT);
      }
#else
      static
      symbol_type
      make_SYMBOL_DDOT ()
      {
        return symbol_type (token::SYMBOL_DDOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_DOT ()
      {
        return symbol_type (token::SYMBOL_DOT);
      }
#else
      static
      symbol_type
      make_SYMBOL_DOT ()
      {
        return symbol_type (token::SYMBOL_DOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_ARROOW ()
      {
        return symbol_type (token::SYMBOL_ARROOW);
      }
#else
      static
      symbol_type
      make_SYMBOL_ARROOW ()
      {
        return symbol_type (token::SYMBOL_ARROOW);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_SLASH ()
      {
        return symbol_type (token::SYMBOL_SLASH);
      }
#else
      static
      symbol_type
      make_SYMBOL_SLASH ()
      {
        return symbol_type (token::SYMBOL_SLASH);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_MINUS ()
      {
        return symbol_type (token::SYMBOL_MINUS);
      }
#else
      static
      symbol_type
      make_SYMBOL_MINUS ()
      {
        return symbol_type (token::SYMBOL_MINUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_PLUS ()
      {
        return symbol_type (token::SYMBOL_PLUS);
      }
#else
      static
      symbol_type
      make_SYMBOL_PLUS ()
      {
        return symbol_type (token::SYMBOL_PLUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_DOUBLE_STAR ()
      {
        return symbol_type (token::SYMBOL_DOUBLE_STAR);
      }
#else
      static
      symbol_type
      make_SYMBOL_DOUBLE_STAR ()
      {
        return symbol_type (token::SYMBOL_DOUBLE_STAR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_VERTICAL_LINE ()
      {
        return symbol_type (token::SYMBOL_VERTICAL_LINE);
      }
#else
      static
      symbol_type
      make_SYMBOL_VERTICAL_LINE ()
      {
        return symbol_type (token::SYMBOL_VERTICAL_LINE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_UPPER ()
      {
        return symbol_type (token::SYMBOL_UPPER);
      }
#else
      static
      symbol_type
      make_SYMBOL_UPPER ()
      {
        return symbol_type (token::SYMBOL_UPPER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_AND ()
      {
        return symbol_type (token::SYMBOL_AND);
      }
#else
      static
      symbol_type
      make_SYMBOL_AND ()
      {
        return symbol_type (token::SYMBOL_AND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_MOD ()
      {
        return symbol_type (token::SYMBOL_MOD);
      }
#else
      static
      symbol_type
      make_SYMBOL_MOD ()
      {
        return symbol_type (token::SYMBOL_MOD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_HASHTAG ()
      {
        return symbol_type (token::SYMBOL_HASHTAG);
      }
#else
      static
      symbol_type
      make_SYMBOL_HASHTAG ()
      {
        return symbol_type (token::SYMBOL_HASHTAG);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_AT ()
      {
        return symbol_type (token::SYMBOL_AT);
      }
#else
      static
      symbol_type
      make_SYMBOL_AT ()
      {
        return symbol_type (token::SYMBOL_AT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_COMMA ()
      {
        return symbol_type (token::SYMBOL_COMMA);
      }
#else
      static
      symbol_type
      make_SYMBOL_COMMA ()
      {
        return symbol_type (token::SYMBOL_COMMA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_SQUARE_BRACKET_CLOSE ()
      {
        return symbol_type (token::SYMBOL_SQUARE_BRACKET_CLOSE);
      }
#else
      static
      symbol_type
      make_SYMBOL_SQUARE_BRACKET_CLOSE ()
      {
        return symbol_type (token::SYMBOL_SQUARE_BRACKET_CLOSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_SQUARE_BRACKET_OPEN ()
      {
        return symbol_type (token::SYMBOL_SQUARE_BRACKET_OPEN);
      }
#else
      static
      symbol_type
      make_SYMBOL_SQUARE_BRACKET_OPEN ()
      {
        return symbol_type (token::SYMBOL_SQUARE_BRACKET_OPEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_CURLY_BRACKET_CLOSE ()
      {
        return symbol_type (token::SYMBOL_CURLY_BRACKET_CLOSE);
      }
#else
      static
      symbol_type
      make_SYMBOL_CURLY_BRACKET_CLOSE ()
      {
        return symbol_type (token::SYMBOL_CURLY_BRACKET_CLOSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_CURLY_BRACKET_OPEN ()
      {
        return symbol_type (token::SYMBOL_CURLY_BRACKET_OPEN);
      }
#else
      static
      symbol_type
      make_SYMBOL_CURLY_BRACKET_OPEN ()
      {
        return symbol_type (token::SYMBOL_CURLY_BRACKET_OPEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_ROUND_BRACKET_CLOSE ()
      {
        return symbol_type (token::SYMBOL_ROUND_BRACKET_CLOSE);
      }
#else
      static
      symbol_type
      make_SYMBOL_ROUND_BRACKET_CLOSE ()
      {
        return symbol_type (token::SYMBOL_ROUND_BRACKET_CLOSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_ROUND_BRACKET_OPEN ()
      {
        return symbol_type (token::SYMBOL_ROUND_BRACKET_OPEN);
      }
#else
      static
      symbol_type
      make_SYMBOL_ROUND_BRACKET_OPEN ()
      {
        return symbol_type (token::SYMBOL_ROUND_BRACKET_OPEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_CONJUNGATES ()
      {
        return symbol_type (token::SYMBOL_CONJUNGATES);
      }
#else
      static
      symbol_type
      make_SYMBOL_CONJUNGATES ()
      {
        return symbol_type (token::SYMBOL_CONJUNGATES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_REDEFINES ()
      {
        return symbol_type (token::SYMBOL_REDEFINES);
      }
#else
      static
      symbol_type
      make_SYMBOL_REDEFINES ()
      {
        return symbol_type (token::SYMBOL_REDEFINES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_REFERENCES ()
      {
        return symbol_type (token::SYMBOL_REFERENCES);
      }
#else
      static
      symbol_type
      make_SYMBOL_REFERENCES ()
      {
        return symbol_type (token::SYMBOL_REFERENCES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_SPECIALIZES ()
      {
        return symbol_type (token::SYMBOL_SPECIALIZES);
      }
#else
      static
      symbol_type
      make_SYMBOL_SPECIALIZES ()
      {
        return symbol_type (token::SYMBOL_SPECIALIZES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_TYPED_BY ()
      {
        return symbol_type (token::SYMBOL_TYPED_BY);
      }
#else
      static
      symbol_type
      make_SYMBOL_TYPED_BY ()
      {
        return symbol_type (token::SYMBOL_TYPED_BY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_NAMESPACE_SUBSET ()
      {
        return symbol_type (token::SYMBOL_NAMESPACE_SUBSET);
      }
#else
      static
      symbol_type
      make_SYMBOL_NAMESPACE_SUBSET ()
      {
        return symbol_type (token::SYMBOL_NAMESPACE_SUBSET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_STAR ()
      {
        return symbol_type (token::SYMBOL_STAR);
      }
#else
      static
      symbol_type
      make_SYMBOL_STAR ()
      {
        return symbol_type (token::SYMBOL_STAR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL_STATEMENT_DELIMITER ()
      {
        return symbol_type (token::SYMBOL_STATEMENT_DELIMITER);
      }
#else
      static
      symbol_type
      make_SYMBOL_STATEMENT_DELIMITER ()
      {
        return symbol_type (token::SYMBOL_STATEMENT_DELIMITER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v)
      {
        return symbol_type (token::STRING, std::move (v));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v)
      {
        return symbol_type (token::STRING, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CONJUGATION ()
      {
        return symbol_type (token::KEYWORD_CONJUGATION);
      }
#else
      static
      symbol_type
      make_KEYWORD_CONJUGATION ()
      {
        return symbol_type (token::KEYWORD_CONJUGATION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_META ()
      {
        return symbol_type (token::KEYWORD_META);
      }
#else
      static
      symbol_type
      make_KEYWORD_META ()
      {
        return symbol_type (token::KEYWORD_META);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CONSTANT ()
      {
        return symbol_type (token::KEYWORD_CONSTANT);
      }
#else
      static
      symbol_type
      make_KEYWORD_CONSTANT ()
      {
        return symbol_type (token::KEYWORD_CONSTANT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_LIBRARY ()
      {
        return symbol_type (token::KEYWORD_LIBRARY);
      }
#else
      static
      symbol_type
      make_KEYWORD_LIBRARY ()
      {
        return symbol_type (token::KEYWORD_LIBRARY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_STANDARD ()
      {
        return symbol_type (token::KEYWORD_STANDARD);
      }
#else
      static
      symbol_type
      make_KEYWORD_STANDARD ()
      {
        return symbol_type (token::KEYWORD_STANDARD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_LOCALE ()
      {
        return symbol_type (token::KEYWORD_LOCALE);
      }
#else
      static
      symbol_type
      make_KEYWORD_LOCALE ()
      {
        return symbol_type (token::KEYWORD_LOCALE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_VAR ()
      {
        return symbol_type (token::KEYWORD_VAR);
      }
#else
      static
      symbol_type
      make_KEYWORD_VAR ()
      {
        return symbol_type (token::KEYWORD_VAR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_XOR ()
      {
        return symbol_type (token::KEYWORD_XOR);
      }
#else
      static
      symbol_type
      make_KEYWORD_XOR ()
      {
        return symbol_type (token::KEYWORD_XOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_UNIONS ()
      {
        return symbol_type (token::KEYWORD_UNIONS);
      }
#else
      static
      symbol_type
      make_KEYWORD_UNIONS ()
      {
        return symbol_type (token::KEYWORD_UNIONS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_TYPING ()
      {
        return symbol_type (token::KEYWORD_TYPING);
      }
#else
      static
      symbol_type
      make_KEYWORD_TYPING ()
      {
        return symbol_type (token::KEYWORD_TYPING);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_TYPED ()
      {
        return symbol_type (token::KEYWORD_TYPED);
      }
#else
      static
      symbol_type
      make_KEYWORD_TYPED ()
      {
        return symbol_type (token::KEYWORD_TYPED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_TYPE ()
      {
        return symbol_type (token::KEYWORD_TYPE);
      }
#else
      static
      symbol_type
      make_KEYWORD_TYPE ()
      {
        return symbol_type (token::KEYWORD_TYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_TRUE ()
      {
        return symbol_type (token::KEYWORD_TRUE);
      }
#else
      static
      symbol_type
      make_KEYWORD_TRUE ()
      {
        return symbol_type (token::KEYWORD_TRUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_TO ()
      {
        return symbol_type (token::KEYWORD_TO);
      }
#else
      static
      symbol_type
      make_KEYWORD_TO ()
      {
        return symbol_type (token::KEYWORD_TO);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_THEN ()
      {
        return symbol_type (token::KEYWORD_THEN);
      }
#else
      static
      symbol_type
      make_KEYWORD_THEN ()
      {
        return symbol_type (token::KEYWORD_THEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_SUCCSESSION ()
      {
        return symbol_type (token::KEYWORD_SUCCSESSION);
      }
#else
      static
      symbol_type
      make_KEYWORD_SUCCSESSION ()
      {
        return symbol_type (token::KEYWORD_SUCCSESSION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_SUBTYPE ()
      {
        return symbol_type (token::KEYWORD_SUBTYPE);
      }
#else
      static
      symbol_type
      make_KEYWORD_SUBTYPE ()
      {
        return symbol_type (token::KEYWORD_SUBTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_SUBSETS ()
      {
        return symbol_type (token::KEYWORD_SUBSETS);
      }
#else
      static
      symbol_type
      make_KEYWORD_SUBSETS ()
      {
        return symbol_type (token::KEYWORD_SUBSETS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_SUBSET ()
      {
        return symbol_type (token::KEYWORD_SUBSET);
      }
#else
      static
      symbol_type
      make_KEYWORD_SUBSET ()
      {
        return symbol_type (token::KEYWORD_SUBSET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_SUBCLASSIFIER ()
      {
        return symbol_type (token::KEYWORD_SUBCLASSIFIER);
      }
#else
      static
      symbol_type
      make_KEYWORD_SUBCLASSIFIER ()
      {
        return symbol_type (token::KEYWORD_SUBCLASSIFIER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_STRUCT ()
      {
        return symbol_type (token::KEYWORD_STRUCT);
      }
#else
      static
      symbol_type
      make_KEYWORD_STRUCT ()
      {
        return symbol_type (token::KEYWORD_STRUCT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_STEP ()
      {
        return symbol_type (token::KEYWORD_STEP);
      }
#else
      static
      symbol_type
      make_KEYWORD_STEP ()
      {
        return symbol_type (token::KEYWORD_STEP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_SPECIALIZES ()
      {
        return symbol_type (token::KEYWORD_SPECIALIZES);
      }
#else
      static
      symbol_type
      make_KEYWORD_SPECIALIZES ()
      {
        return symbol_type (token::KEYWORD_SPECIALIZES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_SPECILIZATION ()
      {
        return symbol_type (token::KEYWORD_SPECILIZATION);
      }
#else
      static
      symbol_type
      make_KEYWORD_SPECILIZATION ()
      {
        return symbol_type (token::KEYWORD_SPECILIZATION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_RETURN ()
      {
        return symbol_type (token::KEYWORD_RETURN);
      }
#else
      static
      symbol_type
      make_KEYWORD_RETURN ()
      {
        return symbol_type (token::KEYWORD_RETURN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_REP ()
      {
        return symbol_type (token::KEYWORD_REP);
      }
#else
      static
      symbol_type
      make_KEYWORD_REP ()
      {
        return symbol_type (token::KEYWORD_REP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_REFERENCES ()
      {
        return symbol_type (token::KEYWORD_REFERENCES);
      }
#else
      static
      symbol_type
      make_KEYWORD_REFERENCES ()
      {
        return symbol_type (token::KEYWORD_REFERENCES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_REDEFINITION ()
      {
        return symbol_type (token::KEYWORD_REDEFINITION);
      }
#else
      static
      symbol_type
      make_KEYWORD_REDEFINITION ()
      {
        return symbol_type (token::KEYWORD_REDEFINITION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_REDEFINES ()
      {
        return symbol_type (token::KEYWORD_REDEFINES);
      }
#else
      static
      symbol_type
      make_KEYWORD_REDEFINES ()
      {
        return symbol_type (token::KEYWORD_REDEFINES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_READONLY ()
      {
        return symbol_type (token::KEYWORD_READONLY);
      }
#else
      static
      symbol_type
      make_KEYWORD_READONLY ()
      {
        return symbol_type (token::KEYWORD_READONLY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_PUBLIC ()
      {
        return symbol_type (token::KEYWORD_PUBLIC);
      }
#else
      static
      symbol_type
      make_KEYWORD_PUBLIC ()
      {
        return symbol_type (token::KEYWORD_PUBLIC);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_PROTECTED ()
      {
        return symbol_type (token::KEYWORD_PROTECTED);
      }
#else
      static
      symbol_type
      make_KEYWORD_PROTECTED ()
      {
        return symbol_type (token::KEYWORD_PROTECTED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_PRIVATE ()
      {
        return symbol_type (token::KEYWORD_PRIVATE);
      }
#else
      static
      symbol_type
      make_KEYWORD_PRIVATE ()
      {
        return symbol_type (token::KEYWORD_PRIVATE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_PREDICATE ()
      {
        return symbol_type (token::KEYWORD_PREDICATE);
      }
#else
      static
      symbol_type
      make_KEYWORD_PREDICATE ()
      {
        return symbol_type (token::KEYWORD_PREDICATE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_PORTION ()
      {
        return symbol_type (token::KEYWORD_PORTION);
      }
#else
      static
      symbol_type
      make_KEYWORD_PORTION ()
      {
        return symbol_type (token::KEYWORD_PORTION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_PACKAGE ()
      {
        return symbol_type (token::KEYWORD_PACKAGE);
      }
#else
      static
      symbol_type
      make_KEYWORD_PACKAGE ()
      {
        return symbol_type (token::KEYWORD_PACKAGE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_OUT ()
      {
        return symbol_type (token::KEYWORD_OUT);
      }
#else
      static
      symbol_type
      make_KEYWORD_OUT ()
      {
        return symbol_type (token::KEYWORD_OUT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ORDERED ()
      {
        return symbol_type (token::KEYWORD_ORDERED);
      }
#else
      static
      symbol_type
      make_KEYWORD_ORDERED ()
      {
        return symbol_type (token::KEYWORD_ORDERED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_OR ()
      {
        return symbol_type (token::KEYWORD_OR);
      }
#else
      static
      symbol_type
      make_KEYWORD_OR ()
      {
        return symbol_type (token::KEYWORD_OR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_OF ()
      {
        return symbol_type (token::KEYWORD_OF);
      }
#else
      static
      symbol_type
      make_KEYWORD_OF ()
      {
        return symbol_type (token::KEYWORD_OF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_NULL ()
      {
        return symbol_type (token::KEYWORD_NULL);
      }
#else
      static
      symbol_type
      make_KEYWORD_NULL ()
      {
        return symbol_type (token::KEYWORD_NULL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_NOT ()
      {
        return symbol_type (token::KEYWORD_NOT);
      }
#else
      static
      symbol_type
      make_KEYWORD_NOT ()
      {
        return symbol_type (token::KEYWORD_NOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_NONUNIQUE ()
      {
        return symbol_type (token::KEYWORD_NONUNIQUE);
      }
#else
      static
      symbol_type
      make_KEYWORD_NONUNIQUE ()
      {
        return symbol_type (token::KEYWORD_NONUNIQUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_NAMESPACE ()
      {
        return symbol_type (token::KEYWORD_NAMESPACE);
      }
#else
      static
      symbol_type
      make_KEYWORD_NAMESPACE ()
      {
        return symbol_type (token::KEYWORD_NAMESPACE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_MULTIPLICITY ()
      {
        return symbol_type (token::KEYWORD_MULTIPLICITY);
      }
#else
      static
      symbol_type
      make_KEYWORD_MULTIPLICITY ()
      {
        return symbol_type (token::KEYWORD_MULTIPLICITY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_METADATA ()
      {
        return symbol_type (token::KEYWORD_METADATA);
      }
#else
      static
      symbol_type
      make_KEYWORD_METADATA ()
      {
        return symbol_type (token::KEYWORD_METADATA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_METACLASS ()
      {
        return symbol_type (token::KEYWORD_METACLASS);
      }
#else
      static
      symbol_type
      make_KEYWORD_METACLASS ()
      {
        return symbol_type (token::KEYWORD_METACLASS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_MEMBER ()
      {
        return symbol_type (token::KEYWORD_MEMBER);
      }
#else
      static
      symbol_type
      make_KEYWORD_MEMBER ()
      {
        return symbol_type (token::KEYWORD_MEMBER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_LANGUAGE ()
      {
        return symbol_type (token::KEYWORD_LANGUAGE);
      }
#else
      static
      symbol_type
      make_KEYWORD_LANGUAGE ()
      {
        return symbol_type (token::KEYWORD_LANGUAGE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ISTYPE ()
      {
        return symbol_type (token::KEYWORD_ISTYPE);
      }
#else
      static
      symbol_type
      make_KEYWORD_ISTYPE ()
      {
        return symbol_type (token::KEYWORD_ISTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_INVERTING ()
      {
        return symbol_type (token::KEYWORD_INVERTING);
      }
#else
      static
      symbol_type
      make_KEYWORD_INVERTING ()
      {
        return symbol_type (token::KEYWORD_INVERTING);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_INVERSE ()
      {
        return symbol_type (token::KEYWORD_INVERSE);
      }
#else
      static
      symbol_type
      make_KEYWORD_INVERSE ()
      {
        return symbol_type (token::KEYWORD_INVERSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_INV ()
      {
        return symbol_type (token::KEYWORD_INV);
      }
#else
      static
      symbol_type
      make_KEYWORD_INV ()
      {
        return symbol_type (token::KEYWORD_INV);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_INTERACTION ()
      {
        return symbol_type (token::KEYWORD_INTERACTION);
      }
#else
      static
      symbol_type
      make_KEYWORD_INTERACTION ()
      {
        return symbol_type (token::KEYWORD_INTERACTION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_INOUT ()
      {
        return symbol_type (token::KEYWORD_INOUT);
      }
#else
      static
      symbol_type
      make_KEYWORD_INOUT ()
      {
        return symbol_type (token::KEYWORD_INOUT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_IN ()
      {
        return symbol_type (token::KEYWORD_IN);
      }
#else
      static
      symbol_type
      make_KEYWORD_IN ()
      {
        return symbol_type (token::KEYWORD_IN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_IMPORT ()
      {
        return symbol_type (token::KEYWORD_IMPORT);
      }
#else
      static
      symbol_type
      make_KEYWORD_IMPORT ()
      {
        return symbol_type (token::KEYWORD_IMPORT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_IMPLIES ()
      {
        return symbol_type (token::KEYWORD_IMPLIES);
      }
#else
      static
      symbol_type
      make_KEYWORD_IMPLIES ()
      {
        return symbol_type (token::KEYWORD_IMPLIES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_INTERSECTS ()
      {
        return symbol_type (token::KEYWORD_INTERSECTS);
      }
#else
      static
      symbol_type
      make_KEYWORD_INTERSECTS ()
      {
        return symbol_type (token::KEYWORD_INTERSECTS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_IF ()
      {
        return symbol_type (token::KEYWORD_IF);
      }
#else
      static
      symbol_type
      make_KEYWORD_IF ()
      {
        return symbol_type (token::KEYWORD_IF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_HASTYPE ()
      {
        return symbol_type (token::KEYWORD_HASTYPE);
      }
#else
      static
      symbol_type
      make_KEYWORD_HASTYPE ()
      {
        return symbol_type (token::KEYWORD_HASTYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FUNCTION ()
      {
        return symbol_type (token::KEYWORD_FUNCTION);
      }
#else
      static
      symbol_type
      make_KEYWORD_FUNCTION ()
      {
        return symbol_type (token::KEYWORD_FUNCTION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FROM ()
      {
        return symbol_type (token::KEYWORD_FROM);
      }
#else
      static
      symbol_type
      make_KEYWORD_FROM ()
      {
        return symbol_type (token::KEYWORD_FROM);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FOR ()
      {
        return symbol_type (token::KEYWORD_FOR);
      }
#else
      static
      symbol_type
      make_KEYWORD_FOR ()
      {
        return symbol_type (token::KEYWORD_FOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FLOW ()
      {
        return symbol_type (token::KEYWORD_FLOW);
      }
#else
      static
      symbol_type
      make_KEYWORD_FLOW ()
      {
        return symbol_type (token::KEYWORD_FLOW);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FIRST ()
      {
        return symbol_type (token::KEYWORD_FIRST);
      }
#else
      static
      symbol_type
      make_KEYWORD_FIRST ()
      {
        return symbol_type (token::KEYWORD_FIRST);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FILTER ()
      {
        return symbol_type (token::KEYWORD_FILTER);
      }
#else
      static
      symbol_type
      make_KEYWORD_FILTER ()
      {
        return symbol_type (token::KEYWORD_FILTER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FEATURING ()
      {
        return symbol_type (token::KEYWORD_FEATURING);
      }
#else
      static
      symbol_type
      make_KEYWORD_FEATURING ()
      {
        return symbol_type (token::KEYWORD_FEATURING);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FEATURED ()
      {
        return symbol_type (token::KEYWORD_FEATURED);
      }
#else
      static
      symbol_type
      make_KEYWORD_FEATURED ()
      {
        return symbol_type (token::KEYWORD_FEATURED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FEATURE ()
      {
        return symbol_type (token::KEYWORD_FEATURE);
      }
#else
      static
      symbol_type
      make_KEYWORD_FEATURE ()
      {
        return symbol_type (token::KEYWORD_FEATURE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_FALSE ()
      {
        return symbol_type (token::KEYWORD_FALSE);
      }
#else
      static
      symbol_type
      make_KEYWORD_FALSE ()
      {
        return symbol_type (token::KEYWORD_FALSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_EXPR ()
      {
        return symbol_type (token::KEYWORD_EXPR);
      }
#else
      static
      symbol_type
      make_KEYWORD_EXPR ()
      {
        return symbol_type (token::KEYWORD_EXPR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_END ()
      {
        return symbol_type (token::KEYWORD_END);
      }
#else
      static
      symbol_type
      make_KEYWORD_END ()
      {
        return symbol_type (token::KEYWORD_END);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ELSE ()
      {
        return symbol_type (token::KEYWORD_ELSE);
      }
#else
      static
      symbol_type
      make_KEYWORD_ELSE ()
      {
        return symbol_type (token::KEYWORD_ELSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DOC ()
      {
        return symbol_type (token::KEYWORD_DOC);
      }
#else
      static
      symbol_type
      make_KEYWORD_DOC ()
      {
        return symbol_type (token::KEYWORD_DOC);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DISJOINT ()
      {
        return symbol_type (token::KEYWORD_DISJOINT);
      }
#else
      static
      symbol_type
      make_KEYWORD_DISJOINT ()
      {
        return symbol_type (token::KEYWORD_DISJOINT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DISJOINING ()
      {
        return symbol_type (token::KEYWORD_DISJOINING);
      }
#else
      static
      symbol_type
      make_KEYWORD_DISJOINING ()
      {
        return symbol_type (token::KEYWORD_DISJOINING);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DIFFERENCES ()
      {
        return symbol_type (token::KEYWORD_DIFFERENCES);
      }
#else
      static
      symbol_type
      make_KEYWORD_DIFFERENCES ()
      {
        return symbol_type (token::KEYWORD_DIFFERENCES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DERIVED ()
      {
        return symbol_type (token::KEYWORD_DERIVED);
      }
#else
      static
      symbol_type
      make_KEYWORD_DERIVED ()
      {
        return symbol_type (token::KEYWORD_DERIVED);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DEPENDENCY ()
      {
        return symbol_type (token::KEYWORD_DEPENDENCY);
      }
#else
      static
      symbol_type
      make_KEYWORD_DEPENDENCY ()
      {
        return symbol_type (token::KEYWORD_DEPENDENCY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DEFAULT ()
      {
        return symbol_type (token::KEYWORD_DEFAULT);
      }
#else
      static
      symbol_type
      make_KEYWORD_DEFAULT ()
      {
        return symbol_type (token::KEYWORD_DEFAULT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_DATATYPE ()
      {
        return symbol_type (token::KEYWORD_DATATYPE);
      }
#else
      static
      symbol_type
      make_KEYWORD_DATATYPE ()
      {
        return symbol_type (token::KEYWORD_DATATYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CONNECTOR ()
      {
        return symbol_type (token::KEYWORD_CONNECTOR);
      }
#else
      static
      symbol_type
      make_KEYWORD_CONNECTOR ()
      {
        return symbol_type (token::KEYWORD_CONNECTOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CONJUGATES ()
      {
        return symbol_type (token::KEYWORD_CONJUGATES);
      }
#else
      static
      symbol_type
      make_KEYWORD_CONJUGATES ()
      {
        return symbol_type (token::KEYWORD_CONJUGATES);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CONJUGATE ()
      {
        return symbol_type (token::KEYWORD_CONJUGATE);
      }
#else
      static
      symbol_type
      make_KEYWORD_CONJUGATE ()
      {
        return symbol_type (token::KEYWORD_CONJUGATE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_COMPOSITE ()
      {
        return symbol_type (token::KEYWORD_COMPOSITE);
      }
#else
      static
      symbol_type
      make_KEYWORD_COMPOSITE ()
      {
        return symbol_type (token::KEYWORD_COMPOSITE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_COMMENT ()
      {
        return symbol_type (token::KEYWORD_COMMENT);
      }
#else
      static
      symbol_type
      make_KEYWORD_COMMENT ()
      {
        return symbol_type (token::KEYWORD_COMMENT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CLASSIFIER ()
      {
        return symbol_type (token::KEYWORD_CLASSIFIER);
      }
#else
      static
      symbol_type
      make_KEYWORD_CLASSIFIER ()
      {
        return symbol_type (token::KEYWORD_CLASSIFIER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CLASS ()
      {
        return symbol_type (token::KEYWORD_CLASS);
      }
#else
      static
      symbol_type
      make_KEYWORD_CLASS ()
      {
        return symbol_type (token::KEYWORD_CLASS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_CHAINS ()
      {
        return symbol_type (token::KEYWORD_CHAINS);
      }
#else
      static
      symbol_type
      make_KEYWORD_CHAINS ()
      {
        return symbol_type (token::KEYWORD_CHAINS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_BY ()
      {
        return symbol_type (token::KEYWORD_BY);
      }
#else
      static
      symbol_type
      make_KEYWORD_BY ()
      {
        return symbol_type (token::KEYWORD_BY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_BOOL ()
      {
        return symbol_type (token::KEYWORD_BOOL);
      }
#else
      static
      symbol_type
      make_KEYWORD_BOOL ()
      {
        return symbol_type (token::KEYWORD_BOOL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_BINDING ()
      {
        return symbol_type (token::KEYWORD_BINDING);
      }
#else
      static
      symbol_type
      make_KEYWORD_BINDING ()
      {
        return symbol_type (token::KEYWORD_BINDING);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_BEHAVIOR ()
      {
        return symbol_type (token::KEYWORD_BEHAVIOR);
      }
#else
      static
      symbol_type
      make_KEYWORD_BEHAVIOR ()
      {
        return symbol_type (token::KEYWORD_BEHAVIOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ASSOC ()
      {
        return symbol_type (token::KEYWORD_ASSOC);
      }
#else
      static
      symbol_type
      make_KEYWORD_ASSOC ()
      {
        return symbol_type (token::KEYWORD_ASSOC);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_AS ()
      {
        return symbol_type (token::KEYWORD_AS);
      }
#else
      static
      symbol_type
      make_KEYWORD_AS ()
      {
        return symbol_type (token::KEYWORD_AS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_AND ()
      {
        return symbol_type (token::KEYWORD_AND);
      }
#else
      static
      symbol_type
      make_KEYWORD_AND ()
      {
        return symbol_type (token::KEYWORD_AND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ALL ()
      {
        return symbol_type (token::KEYWORD_ALL);
      }
#else
      static
      symbol_type
      make_KEYWORD_ALL ()
      {
        return symbol_type (token::KEYWORD_ALL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ALIAS ()
      {
        return symbol_type (token::KEYWORD_ALIAS);
      }
#else
      static
      symbol_type
      make_KEYWORD_ALIAS ()
      {
        return symbol_type (token::KEYWORD_ALIAS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ABSTRACT ()
      {
        return symbol_type (token::KEYWORD_ABSTRACT);
      }
#else
      static
      symbol_type
      make_KEYWORD_ABSTRACT ()
      {
        return symbol_type (token::KEYWORD_ABSTRACT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_KEYWORD_ABOUT ()
      {
        return symbol_type (token::KEYWORD_ABOUT);
      }
#else
      static
      symbol_type
      make_KEYWORD_ABOUT ()
      {
        return symbol_type (token::KEYWORD_ABOUT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TPLUS ()
      {
        return symbol_type (token::TPLUS);
      }
#else
      static
      symbol_type
      make_TPLUS ()
      {
        return symbol_type (token::TPLUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TMINUS ()
      {
        return symbol_type (token::TMINUS);
      }
#else
      static
      symbol_type
      make_TMINUS ()
      {
        return symbol_type (token::TMINUS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TMUL ()
      {
        return symbol_type (token::TMUL);
      }
#else
      static
      symbol_type
      make_TMUL ()
      {
        return symbol_type (token::TMUL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TDIV ()
      {
        return symbol_type (token::TDIV);
      }
#else
      static
      symbol_type
      make_TDIV ()
      {
        return symbol_type (token::TDIV);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const short yypact_ninf_;
    static const short yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const short yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const short yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const short yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 1862,     ///< Last index in yytable_.
      yynnts_ = 285,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };


    // User arguments.
    KerMLFlexScanner* lexer;

  };


#line 5 "/Users/herzog/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.y"
} } // KerML::Parser
#line 4134 "/Users/herzog/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.h"




#endif // !YY_YY_USERS_HERZOG_DOCUMENTS_PROJEKTE_CPP_SYSMLV2_FILEHANDLING_SRC_KERML_KERMLBISONPARSER_H_INCLUDED
