// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 10 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"

    #include <string>
    #include <vector>
    #include <iostream>
    #include <root/namespaces/Namespace.h>
    #include <root/elements/Element.h>

#line 49 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"


#include "KerMLBisonParser.h"


// Unqualified %code blocks.
#line 22 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"

    #include "KerMLFlexScanner.h"

#line 60 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 7 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
namespace KerML { namespace Parser {
#line 134 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"

  /// Build a parser object.
  parser::parser (KerMLFlexScanner* lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_abstract_modifier: // abstract_modifier
      case symbol_kind::S_all_modifier: // all_modifier
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DECIMAL_VALUE: // DECIMAL_VALUE
      case symbol_kind::S_EXPONENTIAL_VALUE: // EXPONENTIAL_VALUE
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_abstract_modifier: // abstract_modifier
      case symbol_kind::S_all_modifier: // all_modifier
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DECIMAL_VALUE: // DECIMAL_VALUE
      case symbol_kind::S_EXPONENTIAL_VALUE: // EXPONENTIAL_VALUE
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (YY_MOVE (that.value));
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
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_abstract_modifier: // abstract_modifier
      case symbol_kind::S_all_modifier: // all_modifier
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_DECIMAL_VALUE: // DECIMAL_VALUE
      case symbol_kind::S_EXPONENTIAL_VALUE: // EXPONENTIAL_VALUE
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.copy< int > (that.value);
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
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_abstract_modifier: // abstract_modifier
      case symbol_kind::S_all_modifier: // all_modifier
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_DECIMAL_VALUE: // DECIMAL_VALUE
      case symbol_kind::S_EXPONENTIAL_VALUE: // EXPONENTIAL_VALUE
        value.move< double > (that.value);
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        value.move< int > (that.value);
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
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (lexer));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_abstract_modifier: // abstract_modifier
      case symbol_kind::S_all_modifier: // all_modifier
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_DECIMAL_VALUE: // DECIMAL_VALUE
      case symbol_kind::S_EXPONENTIAL_VALUE: // EXPONENTIAL_VALUE
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_NUMBER: // NUMBER
        yylhs.value.emplace< int > ();
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
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 47: // type_prefix: abstract_modifier prefix_metadata_annotation
#line 100 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                              {
        if(yystack_[1].value.as < bool > ()) std::cout<<"isAbstract: true \n"<<std::endl;
        if(!yystack_[0].value.as < std::string > ().empty()) std::cout<<"metadata_member: "<<yystack_[0].value.as < std::string > ()<<std::endl;
    }
#line 699 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 48: // type_prefix: abstract_modifier
#line 104 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                        {
        if(yystack_[0].value.as < bool > ()) std::cout<<"isAbstract: true"<<std::endl;
    }
#line 707 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 49: // type_prefix: %empty
#line 107 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                  {}
#line 713 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 50: // prefix_metadata_annotation: SYMBOL_HASHTAG qualified_name
#line 109 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                              {
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 721 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 51: // prefix_metadata_annotation: %empty
#line 112 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                {yylhs.value.as < std::string > () = "";}
#line 727 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 52: // abstract_modifier: KEYWORD_ABSTRACT
#line 115 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                     {yylhs.value.as < bool > () = true;}
#line 733 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 53: // abstract_modifier: %empty
#line 116 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                {yylhs.value.as < bool > () = false;}
#line 739 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 54: // qualified_name: BASIC_NAME qualified_name_tail
#line 121 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
    {
        if (!yystack_[0].value.as < std::string > ().empty()) {
            yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > ().append(yystack_[0].value.as < std::string > ());
        } else {
            yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > ();
        }
    }
#line 751 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 55: // qualified_name: UNRESTRICTED_NAME qualified_name_tail
#line 128 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                            {
        if (!yystack_[0].value.as < std::string > ().empty()) {
            yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > ().append(yystack_[0].value.as < std::string > ());
        } else {
            yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > ();
        }
    }
#line 763 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 56: // qualified_name: %empty
#line 135 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
               {
        yylhs.value.as < std::string > ()="";
    }
#line 771 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 57: // qualified_name_tail: SYMBOL_DDOT BASIC_NAME qualified_name_tail
#line 143 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
    {
        std::string full;
        if (!yystack_[0].value.as < std::string > ().empty()) {
            full = yystack_[1].value.as < std::string > ().append(yystack_[0].value.as < std::string > ());
        } else {
            full = yystack_[1].value.as < std::string > ();
        }
        yylhs.value.as < std::string > () = full;
    }
#line 785 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 58: // qualified_name_tail: SYMBOL_DDOT UNRESTRICTED_NAME qualified_name_tail
#line 152 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                        {
        std::string full;
        if (!yystack_[0].value.as < std::string > ().empty()) {
            full = yystack_[1].value.as < std::string > ().append(yystack_[0].value.as < std::string > ());
        } else {
            full = yystack_[1].value.as < std::string > ();
        }
        yylhs.value.as < std::string > () = full;
    }
#line 799 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 59: // qualified_name_tail: %empty
#line 162 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
    {
        yylhs.value.as < std::string > () = "";
    }
#line 807 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 60: // all_modifier: KEYWORD_ALL
#line 168 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                {yylhs.value.as < bool > () = true;}
#line 813 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 61: // all_modifier: %empty
#line 169 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                {yylhs.value.as < bool > () = false;}
#line 819 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 62: // identification: SYMBOL_SMALLER BASIC_NAME SYMBOL_GREATER
#line 172 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                             {
        yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > ();
    }
#line 827 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 63: // identification: BASIC_NAME
#line 175 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                 {
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 835 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 64: // mutliplicity_bounds: SYMBOL_SQUARE_BRACKET_OPEN NUMBER SYMBOL_DDOT NUMBER SYMBOL_SQUARE_BRACKET_OPEN
#line 179 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                                                                         {
        std::cout<<"lower bound: "<< yystack_[3].value.as < int > () <<std::endl;
        std::cout<<"upper bound: "<< yystack_[3].value.as < int > () <<std::endl;
    }
#line 844 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 65: // mutliplicity_bounds: SYMBOL_SQUARE_BRACKET_OPEN NUMBER SYMBOL_SQUARE_BRACKET_OPEN
#line 183 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                                   {
        std::cout<<"multiplicity: "<< yystack_[1].value.as < int > () <<std::endl;
    }
#line 852 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 66: // mutliplicity_bounds: %empty
#line 186 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                  {yylhs.value.as < std::string > ()="";}
#line 858 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 67: // specialization_option: KEYWORD_SPECIALIZES identification
#line 188 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                              {
        std::cout<<"specialization: "<< yystack_[0].value.as < std::string > () <<std::endl;
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 867 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 68: // specialization_option: SYMBOL_SPECIALIZES identification
#line 192 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                        {
        std::cout<<"specialization: "<< yystack_[0].value.as < std::string > () <<std::endl;
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 876 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 69: // conjugation_option: KEYWORD_CONJUGATES qualified_name
#line 197 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                          {
         std::cout<< "conjugation: "<< yystack_[0].value.as < std::string > () <<std::endl;
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 885 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 70: // conjugation_option: SYMBOL_CONJUNGATES qualified_name
#line 201 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                        {
        std::cout<< "conjugation: "<< yystack_[0].value.as < std::string > () <<std::endl;
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 894 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 71: // type_body: SYMBOL_STATEMENT_DELIMITER
#line 206 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                          {yylhs.value.as < std::string > () = "";}
#line 900 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 72: // type_body: SYMBOL_CURLY_BRACKET_OPEN type_body_elements SYMBOL_CURLY_BRACKET_CLOSE
#line 207 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                                              {
        yylhs.value.as < std::string > () = "$2";
    }
#line 908 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 98: // relationship_body: SYMBOL_STATEMENT_DELIMITER
#line 239 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                  {yylhs.value.as < std::string > () = "";}
#line 914 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 99: // relationship_body: SYMBOL_CURLY_BRACKET_OPEN relationship_body_elements SYMBOL_CURLY_BRACKET_CLOSE
#line 240 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                                                                       {
        yylhs.value.as < std::string > ()="";
    }
#line 922 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 106: // from_option: KEYWORD_FROM qualified_name
#line 248 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                             {
        yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
    }
#line 930 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 107: // from_option: %empty
#line 250 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                  {yylhs.value.as < std::string > () = "";}
#line 936 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 117: // comment_option: SINGLE_LINE_COMMENT
#line 259 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                        {
        yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > ();
    }
#line 944 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 118: // comment_option: BLOCK_COMMENT
#line 262 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                  {
        yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > ();
    }
#line 952 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 145: // specific_type: general_type
#line 289 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                {
        yylhs.value.as < std::string > () = yystack_[1].value.as< std::string > ();
    }
#line 960 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 146: // general_type: qualified_name
#line 292 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                                 {
        yylhs.value.as < std::string > () = yystack_[1].value.as< std::string > ();
    }
#line 968 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;

  case 147: // general_type: owned_feature_chain
#line 294 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
                            {
        yylhs.value.as < std::string > ()="";
    }
#line 976 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"
    break;


#line 980 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short parser::yypact_ninf_ = -700;

  const short parser::yytable_ninf_ = -541;

  const short
  parser::yypact_[] =
  {
    -700,   128,   812,  -700,   129,   129,   435,   114,   114,  -700,
     112,   435,   114,   114,   114,  -700,  -700,  -700,  -700,   114,
     136,   114,  -700,  -700,   114,   114,   435,   114,   435,   435,
      30,  -700,  -700,  -700,  -700,  -700,   171,    -5,   228,   261,
     609,  -700,  -700,   439,  -700,  -700,  -700,  -700,  -700,   140,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,   232,    46,
    -700,  -700,  -700,  -700,   190,  -700,  -700,  -700,  -700,  -700,
    -700,   169,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
     210,  -700,  -700,   257,  -700,   448,  -700,  -700,  -700,  -700,
     329,  -700,   230,  -700,   350,   191,  -700,  -700,  -700,  -700,
     351,   324,   240,   439,  -700,   314,   382,   350,   330,  -700,
     345,   350,   338,  -700,   312,  -700,   114,   318,    30,    30,
      30,    30,    30,    30,    30,    30,    12,   114,   114,  -700,
     114,  -700,  -700,   435,   435,   435,  -700,  -700,  -700,    30,
     435,    29,    30,     9,    30,    30,    30,    30,    30,    63,
    -700,  -700,   399,    25,   435,    30,    79,    30,   114,   114,
     114,  -700,   337,  -700,   129,   129,   465,   435,   435,  -700,
    -700,  -700,   435,   435,   431,   282,   435,   435,   318,   318,
    -700,   435,   341,   439,   435,   435,   435,   435,   382,   446,
    -700,  -700,  -700,   114,   359,   318,   359,   318,   318,   318,
     318,    30,   318,   361,   374,   438,   214,   221,   291,   435,
    -700,  -700,  -700,    30,    56,    30,   318,    36,  -700,  -700,
      30,   237,    36,   318,  -700,    36,    36,    30,   318,   472,
    -700,   435,   435,   449,  -700,  -700,  -700,   414,   417,   318,
     506,   506,    20,   318,   279,   358,   435,  -700,   358,   393,
    -700,  -700,    69,  -700,  -700,  -700,   377,   350,   363,   191,
     439,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,    85,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,   435,  -700,   363,
     402,   363,  -700,   439,   509,    97,   339,   446,   353,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,   318,  -700,  -700,
    -700,  -700,   435,   456,   435,   435,   435,   435,   381,   435,
     435,   476,  -700,   318,  -700,   522,   435,   435,   305,   369,
     305,   528,   409,  -700,  1457,  1457,   437,   318,  -700,  -700,
      36,    62,   350,   503,   463,  -700,  -700,  -700,  -700,   450,
    -700,   359,   359,   451,  -700,  1457,    36,  -700,   494,  -700,
    -700,   435,  -700,   413,   435,  -700,  -700,   255,   255,   541,
     434,  -700,  -700,  -700,  -700,   403,   435,  -700,  -700,  -700,
     950,   378,   337,   435,  -700,  -700,  -700,  -700,   435,  -700,
     282,  -700,   363,  -700,   435,  -700,  -700,   292,   435,  -700,
     323,  -700,  -700,  -700,  1711,  -700,  -700,  -700,  -700,  -700,
    -700,    24,   353,   475,   353,   513,   353,  -700,  1088,  -700,
     435,   507,   363,   363,   446,   435,   446,   446,   104,  -700,
    -700,   542,  -700,  -700,   435,   467,   435,   418,   453,   435,
     435,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,   305,  -700,  -700,   435,   435,   435,    55,  -700,
     526,  -700,  -700,  -700,   541,  -700,   523,   233,   435,  -700,
    -700,   529,   611,  1341,  -700,  -700,  -700,  1457,   435,    81,
     530,    60,  -700,  -700,  -700,  -700,  1457,  -700,  -700,  1594,
    -700,  -700,   247,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,   530,   534,  -700,   546,  -700,  -700,  -700,  -700,
      66,  -700,  -700,  1457,  -700,   359,   435,   435,    99,   466,
    -700,  -700,   541,  -700,    26,   318,  -700,   435,  -700,   532,
    -700,   457,   363,   574,   580,   318,   318,   201,   550,  -700,
     446,   541,  -700,   551,  -700,  -700,   473,  -700,  -700,   363,
    1196,   363,   556,  -700,   363,   587,  -700,  -700,   566,  -700,
    -700,   143,   114,  -700,  -700,    69,   435,   435,   318,  1625,
    -700,  1457,  1457,  -700,  -700,  -700,  -700,  -700,   363,  -700,
    -700,  -700,   363,   446,   363,   363,  -700,  -700,   600,  -700,
    -700,   435,  -700,  -700,   435,   435,  -700,  -700,   350,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,   514,   518,   435,  -700,
     460,   545,   353,  -700,  -700,   350,  -700,  -700,  -700,  -700,
    -700,  -700,  1457,   713,   579,   581,  1457,  -700,  -700,   583,
    -700,   584,   586,  -700,  1543,  -700,  -700,  -700,    67,  1394,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,   435,  -700,  1457,
    1457,   435,  -700,   435,   435,  -700,   435,  -700,  1457,   304,
    -700,  -700,  -700,  -700,   268,  -700,   435,   446,  -700,  -700,
     435,  -700,   604,  -700,   435,  -700,   446,  -700,   228,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,   541,   588,   435,   559,
     435,  -700,  1457,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,   590,   435,  -700,  -700,  -700,   479,
     497,   506,  -700,  -700,   323,  -700,   426,  -700,  -700,   363,
    -700,  -700,  -700,   596,  -700,   601,  -700,  -700,  -700,   606,
    -700,  -700,   526,   541,    81,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,   602,
     512,   512,  -700,  -700,  -700,  -700,  1457,  -700,  -700,  1457,
     428,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
     534,  -700,   528,    36,  -700,  -700,  -700,   582,   541,  -700,
      63,  -700,   550,  -700,  -700,   541,   551,   613,  -700,   566,
     531,  -700,  -700,   435,   435,   615,   616,   435,  -700,  -700,
    -700,  -700,  -700,   525,  1594,   623,  -700,  -700,  -700,  -700,
     435,  -700,  -700,   472,  -700,  -700,  -700,  -700,  -700,   435,
    -700,  -700,   435,   435,  -700,  1457,   629,  -700,   460,  -700,
     363,   363,  -700,  -700,  -700,  1457,  -700,  -700,  -700
  };

  const short
  parser::yydefact_[] =
  {
       4,     0,   203,     1,    59,    59,    56,     0,     0,   532,
       0,    56,     0,     0,     0,   131,   132,   133,   201,     0,
       0,     0,   202,   200,     0,     0,    56,     0,    56,    56,
      61,    52,     3,     6,     7,     8,   282,     0,    48,     0,
     249,    10,     9,     0,     5,   113,   114,   115,    13,     0,
     129,    35,    26,    27,    29,    11,    28,    36,     0,   180,
      31,    32,    33,    30,     0,    34,    12,    14,    15,    17,
      18,     0,    41,    42,    43,    20,    37,    21,    38,    22,
      39,    40,    19,    44,    45,    23,   501,   502,    16,   116,
       0,    24,    25,     0,    46,     0,    54,    55,    50,    63,
       0,    68,     0,   111,   146,     0,   145,   147,   266,    67,
       0,     0,     0,     0,   271,   275,   112,   156,     0,   157,
       0,   150,     0,   151,     0,    60,     0,     0,    61,    61,
      61,    61,    61,    61,    61,    61,    61,     0,     0,    47,
       0,   248,   253,    56,    56,    56,   117,   118,   120,    61,
      56,    61,    61,   324,    61,    61,    61,    61,    61,   195,
     193,   179,   263,   190,    56,    61,     0,    61,   529,     0,
     529,   521,   536,   522,    59,    59,     0,    56,    56,   267,
     142,   141,    56,    56,     0,    56,    56,    56,     0,     0,
     123,    56,     0,     0,    56,    56,    56,    56,   112,    66,
      74,    71,   165,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,   107,     0,     0,     0,     0,    56,
     250,   518,   517,    61,   229,    61,     0,   318,   322,   323,
      61,   229,   318,     0,   191,   318,   318,    61,     0,   197,
     194,    56,    56,     0,   187,   189,   188,   182,     0,     0,
     513,   513,    61,     0,     0,     0,    56,   534,     0,     4,
     535,   530,     0,    57,    58,    62,     0,   269,     0,     0,
       0,   466,   469,   470,   465,   463,   464,   436,   509,   434,
     435,   508,   456,   462,   457,   458,   459,   467,   461,     0,
     507,   259,   235,   236,   503,   504,   274,    56,   121,     0,
       0,     0,   110,     0,     0,   169,   130,    66,    74,   307,
     319,   471,   306,   277,   166,   278,   304,     0,   280,   128,
     125,   124,    56,     0,    56,    56,    56,    56,     0,    56,
      56,   138,   134,     0,   209,     0,    56,    56,   214,   212,
     214,    66,   303,   300,    56,    56,   499,     0,   317,   493,
     318,   209,   492,     0,     0,   487,   488,   490,   491,   477,
     472,     0,     0,   299,   296,    56,   199,   196,   238,   257,
     262,    56,   181,   184,    56,   279,   512,   516,   516,   295,
       0,   285,   286,   284,   527,     0,    56,   520,   526,   519,
     203,   130,   536,    56,   268,   101,    98,   144,    56,   122,
      56,   505,     0,   155,    56,   149,   119,     0,    56,   168,
      81,   167,    72,    73,   203,    78,    75,    77,    76,   161,
     162,     0,    74,     0,   130,     0,    74,   281,   203,   106,
      56,     0,     0,     0,    66,    56,    66,    66,     0,   135,
     473,     0,   152,   153,    56,     0,    56,     0,     0,    56,
      56,   215,    82,    83,    84,    85,   206,   213,   216,   217,
     218,   211,   214,   210,   205,    56,    56,    56,   239,   226,
     233,   227,   229,   228,   295,   301,     0,    56,    56,   365,
     364,     0,    56,    74,   366,   432,   367,    56,    56,   436,
       0,   378,   329,   330,   331,   332,    56,   333,   334,     0,
     375,   377,     0,   382,   383,   384,   335,   336,   393,   394,
     395,   396,   392,   398,   397,   399,   400,   426,   428,   429,
     430,   438,     0,   446,   450,     0,   431,   453,   454,   427,
     378,   497,   498,    56,   305,     0,    56,    56,    56,   479,
     316,   320,   295,   297,   378,     0,   198,    56,   234,   256,
     183,   186,     0,     0,     0,     0,     0,     0,   290,   291,
      66,   295,   528,   525,   538,   537,     0,   539,   531,     0,
     203,     0,     0,   273,     0,     0,    65,   176,   175,   170,
      80,   203,     0,   139,   164,     0,    56,    56,     0,   203,
     309,    56,    56,   312,   308,   310,   126,   127,     0,   542,
     171,   172,     0,    66,     0,     0,   137,   136,   207,   158,
      91,    56,   159,    94,    56,    56,   160,    97,   269,   219,
     220,   204,   260,   244,   231,   245,   240,     0,    56,   230,
     225,     0,    74,   411,   418,   269,   425,   410,   409,   424,
     423,   391,    56,    56,     0,     0,    56,   408,   405,     0,
     433,     0,     0,   378,     0,   387,   388,   390,    56,    56,
     439,   363,   339,   354,   352,   351,   349,   350,   348,   355,
     353,   347,   359,   357,   356,   362,   344,   361,   345,   360,
     372,   358,   346,   340,   370,   342,   371,    56,   341,    56,
      56,    56,   386,    56,    56,   440,    56,   444,    56,   378,
     321,   492,   489,   475,    63,   229,    56,    66,   476,   480,
      56,   474,     0,   177,    56,   255,    66,   185,    51,   270,
     515,   514,   510,   511,   293,   294,   295,     0,    56,     0,
      56,   523,    56,   148,    99,   104,   105,   100,   102,   103,
     109,   143,   506,   154,     0,    56,   173,   163,   282,   180,
       0,   513,    70,    69,    81,   313,   378,   108,   246,     0,
     251,   252,   208,    89,   221,    92,   276,   224,    88,    95,
     241,   242,   233,   295,   391,   381,   325,   326,   414,   380,
     422,   412,   415,   416,   413,   419,   420,   421,   417,     0,
      56,    56,   327,   401,   455,   403,    56,   437,   443,    56,
       0,   369,   389,   338,   379,   343,   368,   374,   373,   452,
     446,   451,    66,   318,   484,   483,   482,     0,   295,   237,
     265,   178,   290,   288,   292,   295,   525,   378,    64,   175,
       0,    79,   247,    56,    56,   222,    86,    56,   232,   302,
     402,   407,   404,     0,   449,     0,   442,   445,   229,   481,
      56,   298,   264,   197,   289,   287,   524,   541,   174,    56,
      90,    93,    56,    56,    96,    56,   447,   441,   486,   478,
       0,     0,   223,    87,   337,    56,   261,   140,   448
  };

  const short
  parser::yypgoto_[] =
  {
    -700,  -700,   407,   239,  -374,  -354,  -700,    87,   -36,  -700,
      -2,    48,   614,    44,  -193,   610,  -700,  -114,   471,  -700,
    -700,   -82,  -393,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -212,  -700,  -700,  -700,  -700,  -700,  -700,  -700,   -68,
     106,   -64,  -700,  -700,  -700,  -700,  -700,  -700,  -276,  -700,
    -267,  -700,  -700,  -700,  -700,   405,  -700,  -104,    22,  -700,
    -135,  -192,  -700,  -186,  -152,  -151,  -153,  -700,  -700,  -700,
    -700,  -700,   367,  -700,  -700,  -143,   -55,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -160,  -700,   116,   443,
    -700,  -700,  -302,  -700,  -700,  -700,  -700,  -700,   356,  -451,
    -700,   149,   -73,   543,  -111,  -700,  -418,  -700,  -700,  -700,
    -138,  -700,  -700,  -700,   -14,  -158,  -432,  -700,  -700,  -700,
    -386,   -23,   440,  -700,  -700,  -700,  -700,  -161,  -700,  -700,
    -700,  -700,  -700,   124,  -700,  -700,  -700,  -700,  -116,  -454,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -162,  -101,   404,  -700,  -700,  -700,  -225,  -700,  -700,
    -700,  -700,  -700,  -608,  -416,  -322,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -472,  -700,  -700,  -699,
      68,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -344,    18,
    -308,  -428,  -700,  -700,  -700,  -700,  -700,  -452,  -700,  -566,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,   236,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -149,   238,  -700,  -700,
    -700,  -700,   224,    58,   -91,  -700,  -700,    28,  -700,  -700,
    -430,  -700,  -700,  -148,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,   502,  -700,  -700,  -700,  -700,  -700,
    -700,  -512,  -700,   193,  -700,  -700,  -700,   360,  -700,  -700,
    -700,  -700,  -700,  -700,   327,  -700,  -700,  -238,   357,   673,
    -700,  -700,  -159,   481,   -92,   575,  -700,  -700,  -700,  -700,
     482,   354,  -700,  -700,  -700
  };

  const short
  parser::yydefgoto_[] =
  {
       0,     1,     2,    32,    33,    34,    35,    36,    37,    38,
     104,    96,   126,   254,   468,    40,   588,   202,   422,   413,
      41,   579,   451,   452,   836,   453,   763,   454,   765,   455,
     769,   397,   570,   737,   738,   323,    42,   739,   198,    43,
      44,   148,    45,    46,    47,    48,   321,   428,    49,    50,
      51,   332,   439,   416,   417,   182,    52,   105,   220,    53,
     122,   338,    54,   118,   610,   613,   617,   418,   419,   420,
      55,   410,   127,    56,   411,   746,   578,    57,    58,   163,
     373,   551,   718,   247,   159,   239,   366,   545,    59,   232,
     339,   462,   456,   457,   458,   459,   460,   835,   340,   341,
     469,   470,   629,   471,   241,   548,   472,   473,    60,   144,
     490,    61,   145,   716,   368,   369,   623,    62,   243,   853,
     107,   108,   179,    63,    64,    65,   192,   767,    66,    67,
      68,    69,    70,    71,    72,   253,   381,   382,   727,   558,
     559,   560,    73,   238,   543,    74,   226,   475,    75,    76,
      77,   310,   424,   651,   426,   593,    78,   347,    79,    80,
      81,   230,   775,   644,   645,   646,   492,   493,   689,   494,
     690,   495,   496,   497,   691,   498,   499,   500,   501,   803,
     804,   779,   502,   503,   504,   505,   694,   506,   655,   801,
     656,   657,   507,   508,   509,   510,   511,   647,   648,   649,
     512,   513,   514,   515,   781,   782,   783,   633,   784,   785,
     786,   787,   638,   639,   516,   517,   518,   279,   280,   519,
     520,   521,   695,   522,   697,   845,   866,   523,   524,   525,
     526,   527,   528,   529,   282,   283,   284,   285,   286,   287,
     288,    82,    83,    84,   233,   539,   711,   708,   709,   815,
     813,   354,   355,   356,   357,   358,   348,   349,   533,   367,
      85,    86,    87,   189,   289,   290,    88,   377,   555,   171,
     222,    89,    90,   387,   731,   255,   256,    91,    92,    93,
     172,   261,   391,   567,    94
  };

  const short
  parser::yytable_[] =
  {
      39,   188,   139,   119,    98,   123,   305,   359,   299,   300,
     361,   362,   221,   378,   262,   654,   602,   580,   604,   605,
     631,   630,   491,   530,   117,   703,   121,   124,   292,   293,
     414,   652,   423,   106,   776,   625,   278,   281,   464,   415,
     583,   218,   266,   544,   312,  -500,   634,   634,   193,   190,
     642,   101,   102,    97,   344,   345,   109,   110,   111,   334,
     584,   301,   379,   112,   619,   114,  -500,   586,   115,   116,
       4,   120,     5,   228,   294,   295,  -500,   789,   335,   269,
     661,   776,    99,   244,   211,    95,   -59,   403,   712,   405,
     137,   311,     7,   313,   314,   315,   316,   843,   318,   336,
    -494,   100,   704,   150,     5,   658,  -495,   729,   400,   186,
    -494,   245,   343,   409,   421,   566,  -495,    99,   388,   360,
      12,   100,   401,  -146,   364,   535,   138,   -59,     3,   298,
     303,   229,   187,   606,  -385,   375,   100,   304,   370,   383,
     336,   216,   217,   408,   626,   223,   589,   461,   592,   627,
     423,  -494,    95,   607,   123,   415,   169,  -495,  -500,   587,
     621,   125,   246,   103,   797,   653,   874,   106,   346,   125,
     199,   119,   119,   123,  -494,   121,   267,   -53,   125,   125,
    -495,   213,   214,   277,   215,   759,   248,   113,   776,   296,
     573,   337,   117,   117,   121,   302,   735,   161,   817,   540,
     541,   442,   443,   427,   268,   106,   399,   423,   291,   291,
     250,   699,   788,   257,   780,   583,   736,   331,   574,   440,
     600,   601,   263,   264,   841,   764,   777,   747,   125,   352,
     792,    18,   337,   534,   128,   584,     4,   180,     5,   406,
     351,   165,     5,   799,   150,   168,   724,   307,   149,    22,
      23,   278,   281,   353,   812,   585,   129,   776,   569,   335,
     325,   -56,     6,   291,   106,   181,   150,   166,   327,   755,
     756,   692,   822,   777,   805,   632,   130,   -49,   185,   725,
     336,   140,   811,   328,   131,     4,   186,     5,   326,   271,
     272,    95,   -59,   164,    31,   402,   824,   169,   820,   151,
     693,   553,   -56,   167,   132,   152,   -59,   170,   -59,   187,
     133,   134,   173,   123,   123,   575,   135,   136,   -59,   839,
     429,   590,   431,   432,   433,   595,   384,   844,   624,   554,
     576,   273,   176,   274,   121,   121,   153,   329,   869,   842,
     719,   385,   489,   489,  -496,   706,   275,   806,   154,   434,
     808,   436,   437,   155,  -496,   156,   423,   733,   200,   741,
     330,   580,   743,   489,   851,   444,   177,   728,   201,   549,
     123,   855,   337,   700,   178,   157,   158,   259,   412,   802,
     777,   119,   -59,   444,   563,   802,   757,   260,    39,   714,
     758,   121,   760,   761,   848,  -496,   552,   868,   277,   308,
     707,   319,   117,   395,   276,   191,   577,  -229,   445,   309,
     827,   320,   336,   396,  -229,   446,  -229,   565,  -496,   183,
     571,    15,    16,    17,   184,   447,    39,   620,   598,   768,
     585,   713,   448,   446,   449,    15,    16,    17,     4,    10,
       5,   722,   723,   146,   194,   147,   450,  -229,   618,   777,
     448,   174,   449,   175,   636,   531,   532,   603,  -229,   878,
      15,    16,    17,  -229,   197,  -314,   609,  -314,   612,   846,
     659,   616,   195,   196,   754,   635,   641,   653,   242,   265,
     489,   489,   270,   297,   304,   489,   641,   622,   322,   622,
     772,   324,   365,   371,   489,   372,   204,   205,   206,   207,
     208,   209,   210,   212,   337,   465,   186,   466,   374,   376,
     386,  -540,   393,   830,   816,     4,   404,     5,   407,   271,
     272,   430,   476,   435,   438,   441,   474,   536,   537,   187,
     547,   489,   249,   251,   701,   352,   477,   478,   467,   479,
     480,   538,   542,   550,   557,   562,   481,   832,   561,  -406,
     482,   591,   594,  -406,   483,   484,   608,   599,   611,   353,
     614,   273,   628,   274,   698,   632,   304,   615,   814,   291,
     696,   643,   659,   465,   186,   466,   275,   720,   317,   466,
     710,   717,   705,   721,   752,   753,   726,   730,   849,   489,
     489,   732,   119,   742,   225,   227,   744,   187,   234,   235,
     236,   237,   745,   762,   485,   486,   467,   771,   770,   618,
     252,   773,   766,   117,     4,   790,     5,   791,   271,   272,
     793,   476,   818,   487,   825,   794,   751,   795,   828,   823,
     161,   167,   833,  -254,   276,   477,   478,   834,   479,   480,
     774,   489,   837,   840,   489,   481,   859,   850,  -406,   482,
     865,   862,   863,   483,   484,  -254,   267,   489,   876,   877,
     273,   488,   274,   857,   867,   875,   390,   597,   748,   162,
     141,   306,   831,   350,   398,   275,   740,   873,  -254,   142,
     143,   860,   821,   861,   864,   641,   858,   489,   489,   641,
     829,   641,   641,   870,   809,   463,   489,   749,   715,   838,
     819,   872,   240,   485,   486,   750,   854,   394,   352,   852,
     778,   807,   425,   637,   660,   640,     4,   800,     5,   847,
     271,   272,   487,   476,   810,   333,   546,   572,   826,   702,
     489,   160,   353,   276,   856,   556,   291,   477,   478,   389,
     479,   480,   203,   577,   392,   258,   568,   481,     0,     0,
     622,   482,     0,     0,  -406,   483,   484,     0,     0,     0,
     488,     0,   273,   219,   274,   224,   224,     0,   231,   224,
     224,   224,   224,     0,     0,     0,     0,   275,     0,     0,
       0,   224,     0,     0,     0,     0,     0,     0,   489,   489,
       0,     0,     0,     0,   489,     0,     0,   489,     0,     0,
       0,     0,     0,     0,     0,   485,   486,     0,     0,     0,
       0,     0,    -2,     0,     0,     4,  -112,     5,  -112,     0,
       0,     0,     0,     0,   487,     0,     0,     0,     0,     0,
       0,     0,   -56,     0,     0,   276,     0,   231,     0,   342,
     119,     0,     0,     0,   224,     0,     6,  -522,   352,     0,
       0,   363,     0,     0,     0,   609,   612,   871,     7,   616,
     766,   117,   488,   489,     8,     0,   380,  -533,     9,    10,
       0,     0,   353,   489,     0,   -49,     0,     0,     0,     0,
      11,     0,     0,     0,   -49,     0,    12,    13,     0,    14,
       0,     0,     0,     0,    15,    16,    17,   -49,     0,  -522,
      18,     0,     0,     0,     0,     0,     0,   -51,    19,  -522,
     -49,     0,    20,     0,    21,  -272,     0,   -49,    22,    23,
    -130,     0,     0,     0,     0,   -49,     0,     0,     0,     0,
       0,    24,     0,     0,     0,     0,     0,     0,    25,    26,
      27,     0,     0,   -51,     0,   -49,   -49,     0,    28,     0,
      29,    30,   -49,     4,  -112,     5,  -112,   -49,   -49,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
     -56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,  -522,     0,     0,     0,   564,
       0,     0,     0,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     8,     0,     0,  -533,     9,    10,     0,     0,
       0,     0,     0,   -49,     0,     0,     0,     0,    11,     0,
       0,     0,   -49,     0,    12,    13,     0,    14,     0,     0,
       0,     0,    15,    16,    17,   -49,     0,  -522,    18,     0,
       0,     0,     0,     0,     0,   -51,    19,  -522,   -49,     0,
      20,     0,    21,  -272,     0,   -49,    22,    23,  -130,     0,
       0,     0,     0,   -49,     0,     0,     0,     0,     0,    24,
       0,     0,     0,     0,     0,     0,    25,    26,    27,     0,
       0,   -51,     0,   -49,   -49,     0,    28,     0,    29,    30,
     -49,     4,  -112,     5,  -112,   -49,   -49,     0,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,   -56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     6,  -522,     0,     0,     0,   596,     0,     0,
       0,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       8,     0,     0,  -533,     9,    10,     0,     0,     0,     0,
       0,   -49,     0,     0,     0,     0,    11,     0,     0,     0,
     -49,     0,    12,    13,     0,    14,     0,     0,     0,     0,
      15,    16,    17,   -49,     0,  -522,    18,     0,     0,     0,
       0,     0,     0,   -51,    19,  -522,   -49,     0,    20,     0,
      21,  -272,     0,   -49,    22,    23,  -130,     0,     0,     0,
    -112,   -49,  -112,     0,     0,     0,     0,    24,     0,     0,
       0,     0,     0,     0,    25,    26,    27,     0,     0,   -51,
       0,   -49,   -49,     0,    28,     0,    29,    30,   -49,     0,
       6,  -522,     0,   -49,   -49,   734,     0,     0,     0,    31,
       0,     0,     7,     0,     0,     0,     0,     0,     8,     0,
       0,  -533,     9,    10,     0,     0,     0,     0,     0,   -49,
       0,     0,     0,     0,    11,     0,     0,     0,   -49,     0,
      12,    13,     0,    14,     0,     0,     0,     0,    15,    16,
      17,   -49,     0,  -522,    18,     0,     0,     0,     0,     0,
       0,   -51,    19,  -522,   -49,     0,    20,     0,    21,  -272,
       0,   -49,    22,    23,  -130,     0,     0,     0,     0,   -49,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
       0,     0,    25,    26,    27,     0,     0,   -51,     0,   -49,
     -49,     0,    28,     0,    29,    30,   -49,     0,     0,     0,
       0,   -49,   -49,     0,     4,     0,     5,    31,   271,   272,
       0,   476,   -56,     0,   -56,   -56,   -56,   -56,   -56,   -56,
       0,     0,   -56,   -56,   -56,   477,   478,   -56,   479,   480,
     -56,   -56,   -56,   -56,   -56,   481,   -56,   -56,     0,   482,
       0,     0,   650,   483,   484,     0,     0,     0,     0,     0,
     273,     0,   274,     0,   -56,     0,     0,     4,     0,     5,
     -56,   271,   272,     0,   476,   275,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   477,   478,
       0,   479,   480,    15,    16,    17,     0,     0,   481,     0,
       0,   -56,   482,   485,   486,   798,   483,   484,     0,     0,
       0,     0,   -56,   273,     0,   274,     0,     0,     0,     0,
     -56,     0,   487,   -56,     0,     0,     0,     0,   275,     0,
       4,     0,     5,   276,   271,   272,     0,   476,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   477,   478,     0,   479,   480,   485,   486,   -56,   -56,
     488,   481,     0,     0,     0,   482,     0,     0,     0,   483,
     484,     0,     0,     0,     0,   487,   273,     0,   274,     0,
       0,     0,     0,     0,     0,     0,   276,     0,     0,     0,
       0,   275,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   488,     0,     0,     0,     0,     0,   485,
     486,     0,     0,     0,   662,   796,   663,   664,   665,   666,
     667,   668,     0,     0,   669,   670,   671,     0,   487,   672,
     673,   674,   675,   676,   677,   678,   679,     0,   680,   276,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   681,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   682,     0,     0,   662,   488,   663,   664,   665,
     666,   667,   668,     0,     0,   669,   670,   671,     0,     0,
     672,   673,   674,   675,   676,   677,   678,   679,     0,   680,
       0,     0,     0,   683,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   681,   684,     0,     0,     0,     0,     0,
       0,     0,   685,   682,     0,   686,     0,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     0,     0,     0,     0,     0,     8,     0,     0,
    -533,     9,     0,     0,   683,     0,     0,     0,   -49,     0,
     687,   688,     0,    11,     0,   684,     0,   -49,     0,    12,
      13,   591,     0,   685,     0,     0,   686,    15,    16,    17,
     -49,     0,  -522,    18,     0,     0,     0,     0,     0,     0,
     -51,    19,     0,   -49,   581,     0,     0,    21,  -272,     0,
     -49,    22,    23,   149,     0,     0,     0,     0,   -49,     0,
       0,   687,   688,     0,    24,     6,     0,     0,     0,     0,
       0,     0,    26,    27,     0,     0,   -51,     7,   -49,   -49,
       0,    28,     0,     8,    30,   -49,  -533,     9,     0,     0,
     -49,   -49,     0,     0,   -49,   582,    31,     0,     0,    11,
       0,     0,     0,   -49,     0,    12,    13,     0,     0,     0,
       0,     0,     0,    15,    16,    17,   -49,     0,  -522,    18,
       0,     0,     0,     0,     0,     0,   -51,    19,     0,   -49,
     581,     0,     0,    21,  -272,     0,   -49,    22,    23,   149,
       0,     0,     0,     0,   -49,     0,     0,     0,     0,     0,
      24,     0,     0,     0,     0,     0,     0,     0,    26,    27,
       0,     0,   -51,     0,   -49,   -49,     0,    28,     0,     0,
      30,   -49,     0,     0,     0,     0,   -49,   -49,     0,     0,
       0,   582,    31
  };

  const short
  parser::yycheck_[] =
  {
       2,   112,    38,    26,     6,    28,   199,   232,   194,   195,
     235,   236,   150,   251,   173,   487,   434,   410,   436,   437,
     474,   472,   344,   345,    26,   537,    28,    29,   186,   187,
     306,   483,   308,    11,   642,   467,   185,   185,   340,   306,
     414,   145,   177,   365,   206,    19,   476,   477,   116,   113,
     478,     7,     8,     5,    18,    19,    12,    13,    14,     3,
     414,   196,    42,    19,   450,    21,    40,    43,    24,    25,
       3,    27,     5,    64,   188,   189,    50,   643,    22,   183,
     496,   689,     3,    58,    72,    23,    24,   299,   542,   301,
      95,   205,    46,   207,   208,   209,   210,   796,   212,    43,
      40,    22,     3,    34,     5,    24,    40,   561,    23,    46,
      50,    86,   226,   305,   307,   391,    50,     3,   256,   233,
      74,    22,    37,    42,   238,   350,   131,    65,     0,   193,
     198,   122,    69,    29,    53,   249,    22,    38,   242,   253,
      43,   143,   144,    46,    89,   116,   422,   339,   424,    94,
     426,    91,    23,    49,   177,   422,    87,    91,   132,   135,
     462,   149,   137,    51,    97,   487,   865,   145,   132,   149,
     126,   194,   195,   196,   114,   177,   178,    34,   149,   149,
     114,   137,   138,   185,   140,   603,   164,    51,   796,   191,
     402,   135,   194,   195,   196,   197,   570,   151,   710,   361,
     362,   336,   337,   317,   182,   183,   270,   483,   186,   187,
     166,   533,   642,   169,   642,   589,   570,   219,   404,   333,
     432,   433,   174,   175,   790,   611,   642,   581,   149,   231,
     646,    88,   135,   347,    63,   589,     3,    46,     5,   303,
       3,    72,     5,   659,    34,    35,    45,   203,   108,   106,
     107,   400,   400,   231,   705,   414,    85,   865,   393,    22,
      46,    24,    34,   241,   242,    74,    34,    98,    47,   591,
     592,    24,   726,   689,   690,    42,   105,   134,    38,    78,
      43,    20,   698,    62,   113,     3,    46,     5,    74,     7,
       8,    23,    24,   103,   151,   297,   728,    87,   716,    67,
      53,    46,    65,   134,   133,    73,    38,    97,    40,    69,
     139,   140,    55,   336,   337,    23,   145,   146,    50,   773,
     322,   422,   324,   325,   326,   426,    47,   799,   466,    74,
      38,    49,     3,    51,   336,   337,   104,    46,   850,   791,
     552,    62,   344,   345,    40,   538,    64,   691,   116,   327,
     694,   329,   330,   121,    50,   123,   632,   569,    40,   571,
      69,   754,   574,   365,   818,    60,   136,   560,    50,   371,
     393,   825,   135,   535,    24,   143,   144,    40,    39,   687,
     796,   404,   114,    60,   386,   693,   598,    50,   390,   547,
     602,   393,   604,   605,   812,    91,   374,   848,   400,    40,
     538,    40,   404,    40,   122,    91,   408,    38,   103,    50,
     732,    50,    43,    50,    45,   110,    47,    39,   114,    68,
     398,    82,    83,    84,   100,   120,   428,   450,   430,   615,
     589,   545,   127,   110,   129,    82,    83,    84,     3,    57,
       5,   555,   556,     4,   114,     6,   141,    78,   450,   865,
     127,     3,   129,     5,   477,    18,    19,   435,    89,   875,
      82,    83,    84,    94,   152,    39,   444,    41,   446,    41,
      42,   449,   127,   135,   588,   477,   478,   799,    79,    14,
     482,   483,    51,   142,    38,   487,   488,   465,   114,   467,
     628,    53,    20,    44,   496,    81,   129,   130,   131,   132,
     133,   134,   135,   136,   135,    45,    46,    47,    91,     3,
     152,   118,   135,   751,   707,     3,   114,     5,     9,     7,
       8,    65,    10,   142,    48,     3,   117,    24,    65,    69,
      36,   533,   165,   166,   536,   537,    24,    25,    78,    27,
      28,    91,    91,   130,     3,   142,    34,   759,   114,    37,
      38,    76,    39,    41,    42,    43,    14,    50,    91,   537,
     142,    49,    36,    51,    18,    42,    38,   114,   706,   547,
      36,    42,    42,    45,    46,    47,    64,     3,   211,    47,
     114,   124,   538,     3,   586,   587,    36,    36,   813,   591,
     592,   118,   615,    37,   151,   152,     9,    69,   155,   156,
     157,   158,    36,     3,    92,    93,    78,    89,    94,   611,
     167,    66,   614,   615,     3,    36,     5,    36,     7,     8,
      37,    10,    18,   111,    65,    41,   582,    41,    38,    41,
     151,   134,    36,    24,   122,    24,    25,    36,    27,    28,
     642,   643,    36,    41,   646,    34,   115,    65,    37,    38,
     125,    36,    36,    42,    43,    46,   658,   659,   870,   871,
      49,   149,    51,    50,    41,    36,   259,   428,   581,    59,
      61,   200,   754,   230,   269,    64,   570,   863,    69,    70,
      71,   833,   718,   834,   837,   687,   829,   689,   690,   691,
     745,   693,   694,   853,   696,   339,   698,   581,   549,   772,
     714,   862,   159,    92,    93,   581,   822,   267,   710,   820,
     642,   693,   308,   477,   490,   477,     3,   659,     5,   810,
       7,     8,   111,    10,   696,   223,   366,   400,   730,   536,
     732,    58,   710,   122,   826,   378,   714,    24,    25,   258,
      27,    28,   128,   745,   262,   170,   392,    34,    -1,    -1,
     728,    38,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
     149,    -1,    49,   149,    51,   151,   152,    -1,   154,   155,
     156,   157,   158,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,   790,   791,
      -1,    -1,    -1,    -1,   796,    -1,    -1,   799,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    93,    -1,    -1,    -1,
      -1,    -1,     0,    -1,    -1,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,   122,    -1,   223,    -1,   225,
     863,    -1,    -1,    -1,   230,    -1,    34,    35,   850,    -1,
      -1,   237,    -1,    -1,    -1,   833,   834,   859,    46,   837,
     862,   863,   149,   865,    52,    -1,   252,    55,    56,    57,
      -1,    -1,   850,   875,    -1,    63,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    72,    -1,    74,    75,    -1,    77,
      -1,    -1,    -1,    -1,    82,    83,    84,    85,    -1,    87,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,
      98,    -1,   100,    -1,   102,   103,    -1,   105,   106,   107,
     108,    -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,    -1,    -1,    -1,   126,   127,
     128,    -1,    -1,   131,    -1,   133,   134,    -1,   136,    -1,
     138,   139,   140,     3,     4,     5,     6,   145,   146,    -1,
      -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    72,    -1,    74,    75,    -1,    77,    -1,    -1,
      -1,    -1,    82,    83,    84,    85,    -1,    87,    88,    -1,
      -1,    -1,    -1,    -1,    -1,    95,    96,    97,    98,    -1,
     100,    -1,   102,   103,    -1,   105,   106,   107,   108,    -1,
      -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,   119,
      -1,    -1,    -1,    -1,    -1,    -1,   126,   127,   128,    -1,
      -1,   131,    -1,   133,   134,    -1,   136,    -1,   138,   139,
     140,     3,     4,     5,     6,   145,   146,    -1,    -1,    -1,
      -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      72,    -1,    74,    75,    -1,    77,    -1,    -1,    -1,    -1,
      82,    83,    84,    85,    -1,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    -1,   100,    -1,
     102,   103,    -1,   105,   106,   107,   108,    -1,    -1,    -1,
       4,   113,     6,    -1,    -1,    -1,    -1,   119,    -1,    -1,
      -1,    -1,    -1,    -1,   126,   127,   128,    -1,    -1,   131,
      -1,   133,   134,    -1,   136,    -1,   138,   139,   140,    -1,
      34,    35,    -1,   145,   146,    39,    -1,    -1,    -1,   151,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    72,    -1,
      74,    75,    -1,    77,    -1,    -1,    -1,    -1,    82,    83,
      84,    85,    -1,    87,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    96,    97,    98,    -1,   100,    -1,   102,   103,
      -1,   105,   106,   107,   108,    -1,    -1,    -1,    -1,   113,
      -1,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,    -1,
      -1,    -1,   126,   127,   128,    -1,    -1,   131,    -1,   133,
     134,    -1,   136,    -1,   138,   139,   140,    -1,    -1,    -1,
      -1,   145,   146,    -1,     3,    -1,     5,   151,     7,     8,
      -1,    10,    11,    -1,    13,    14,    15,    16,    17,    18,
      -1,    -1,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    38,
      -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    51,    -1,    53,    -1,    -1,     3,    -1,     5,
      59,     7,     8,    -1,    10,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      -1,    27,    28,    82,    83,    84,    -1,    -1,    34,    -1,
      -1,    90,    38,    92,    93,    41,    42,    43,    -1,    -1,
      -1,    -1,   101,    49,    -1,    51,    -1,    -1,    -1,    -1,
     109,    -1,   111,   112,    -1,    -1,    -1,    -1,    64,    -1,
       3,    -1,     5,   122,     7,     8,    -1,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    -1,    27,    28,    92,    93,   147,   148,
     149,    34,    -1,    -1,    -1,    38,    -1,    -1,    -1,    42,
      43,    -1,    -1,    -1,    -1,   111,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    92,
      93,    -1,    -1,    -1,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,    22,    23,    -1,   111,    26,
      27,    28,    29,    30,    31,    32,    33,    -1,    35,   122,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    11,   149,    13,    14,    15,
      16,    17,    18,    -1,    -1,    21,    22,    23,    -1,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    -1,    35,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,   101,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    59,    -1,   112,    -1,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      55,    56,    -1,    -1,    90,    -1,    -1,    -1,    63,    -1,
     147,   148,    -1,    68,    -1,   101,    -1,    72,    -1,    74,
      75,    76,    -1,   109,    -1,    -1,   112,    82,    83,    84,
      85,    -1,    87,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    96,    -1,    98,    99,    -1,    -1,   102,   103,    -1,
     105,   106,   107,   108,    -1,    -1,    -1,    -1,   113,    -1,
      -1,   147,   148,    -1,   119,    34,    -1,    -1,    -1,    -1,
      -1,    -1,   127,   128,    -1,    -1,   131,    46,   133,   134,
      -1,   136,    -1,    52,   139,   140,    55,    56,    -1,    -1,
     145,   146,    -1,    -1,    63,   150,   151,    -1,    -1,    68,
      -1,    -1,    -1,    72,    -1,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    82,    83,    84,    85,    -1,    87,    88,
      -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,    -1,   102,   103,    -1,   105,   106,   107,   108,
      -1,    -1,    -1,    -1,   113,    -1,    -1,    -1,    -1,    -1,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,   128,
      -1,    -1,   131,    -1,   133,   134,    -1,   136,    -1,    -1,
     139,   140,    -1,    -1,    -1,    -1,   145,   146,    -1,    -1,
      -1,   150,   151
  };

  const short
  parser::yystos_[] =
  {
       0,   158,   159,     0,     3,     5,    34,    46,    52,    56,
      57,    68,    74,    75,    77,    82,    83,    84,    88,    96,
     100,   102,   106,   107,   119,   126,   127,   128,   136,   138,
     139,   151,   160,   161,   162,   163,   164,   165,   166,   167,
     172,   177,   193,   196,   197,   199,   200,   201,   202,   205,
     206,   207,   213,   216,   219,   227,   230,   234,   235,   245,
     265,   268,   274,   280,   281,   282,   285,   286,   287,   288,
     289,   290,   291,   299,   302,   305,   306,   307,   313,   315,
     316,   317,   398,   399,   400,   417,   418,   419,   423,   428,
     429,   434,   435,   436,   441,    23,   168,   168,   167,     3,
      22,   170,   170,    51,   167,   214,   215,   277,   278,   170,
     170,   170,   170,    51,   170,   170,   170,   167,   220,   278,
     170,   167,   217,   278,   167,   149,   169,   229,    63,    85,
     105,   113,   133,   139,   140,   145,   146,    95,   131,   165,
      20,    61,    70,    71,   266,   269,     4,     6,   198,   108,
      34,    67,    73,   104,   116,   121,   123,   143,   144,   241,
     426,   151,   172,   236,   103,    72,    98,   134,    35,    87,
      97,   426,   437,    55,     3,     5,     3,   136,    24,   279,
      46,    74,   212,    68,   100,    38,    46,    69,   261,   420,
     198,    91,   283,   196,   114,   127,   135,   152,   195,   170,
      40,    50,   174,   169,   229,   229,   229,   229,   229,   229,
     229,    72,   229,   170,   170,   170,   167,   167,   214,   169,
     215,   267,   427,   116,   169,   246,   303,   246,    64,   122,
     318,   169,   246,   401,   246,   246,   246,   246,   300,   242,
     260,   261,    79,   275,    58,    86,   137,   240,   215,   229,
     170,   229,   246,   292,   170,   432,   433,   170,   432,    40,
      50,   438,   429,   168,   168,    14,   217,   167,   215,   214,
      51,     7,     8,    49,    51,    64,   122,   167,   373,   374,
     375,   390,   391,   392,   393,   394,   395,   396,   397,   421,
     422,   215,   272,   272,   174,   174,   167,   142,   198,   220,
     220,   217,   167,   196,    38,   171,   175,   170,    40,    50,
     308,   174,   308,   174,   174,   174,   174,   229,   174,    40,
      50,   203,   114,   192,    53,    46,    74,    47,    62,    46,
      69,   167,   208,   401,     3,    22,    43,   135,   218,   247,
     255,   256,   169,   174,    18,    19,   132,   314,   413,   414,
     246,     3,   167,   215,   408,   409,   410,   411,   412,   314,
     174,   314,   314,   169,   174,    20,   243,   416,   271,   272,
     214,    44,    81,   237,    91,   174,     3,   424,   424,    42,
     169,   293,   294,   174,    47,    62,   152,   430,   267,   430,
     159,   439,   437,   135,   279,    40,    50,   188,   212,   198,
      23,    37,   167,   188,   114,   188,   198,     9,    46,   218,
     228,   231,    39,   176,   205,   207,   210,   211,   224,   225,
     226,   171,   175,   205,   309,   310,   311,   174,   204,   167,
      65,   167,   167,   167,   215,   142,   215,   215,    48,   209,
     174,     3,   217,   217,    60,   103,   110,   120,   127,   129,
     141,   179,   180,   182,   184,   186,   249,   250,   251,   252,
     253,   218,   248,   255,   249,    45,    47,    78,   171,   257,
     258,   260,   263,   264,   117,   304,    10,    24,    25,    27,
      28,    34,    38,    42,    43,    92,    93,   111,   149,   167,
     267,   322,   323,   324,   326,   328,   329,   330,   332,   333,
     334,   335,   339,   340,   341,   342,   344,   349,   350,   351,
     352,   353,   357,   358,   359,   360,   371,   372,   373,   376,
     377,   378,   380,   384,   385,   386,   387,   388,   389,   390,
     322,    18,    19,   415,   174,   314,    24,    65,    91,   402,
     308,   308,    91,   301,   322,   244,   414,    36,   262,   167,
     130,   238,   215,    46,    74,   425,   425,     3,   296,   297,
     298,   114,   142,   167,    39,    39,   205,   440,   438,   217,
     189,   215,   421,   188,   220,    23,    38,   167,   233,   178,
     179,    99,   150,   161,   162,   429,    43,   135,   173,   205,
     309,    76,   205,   312,    39,   309,    39,   160,   167,    50,
     188,   188,   263,   215,   263,   263,    29,    49,    14,   215,
     221,    91,   215,   222,   142,   114,   215,   223,   167,   277,
     278,   249,   215,   273,   267,   273,    89,    94,    36,   259,
     256,   296,    42,   364,   387,   167,   278,   364,   369,   370,
     374,   167,   348,    42,   320,   321,   322,   354,   355,   356,
      41,   310,   354,   322,   333,   345,   347,   348,    24,    42,
     379,   321,    11,    13,    14,    15,    16,    17,    18,    21,
      22,    23,    26,    27,    28,    29,    30,    31,    32,    33,
      35,    49,    59,    90,   101,   109,   112,   147,   148,   325,
     327,   331,    24,    53,   343,   379,    36,   381,    18,   322,
     308,   167,   410,   408,     3,   170,   171,   267,   404,   405,
     114,   403,   296,   174,   272,   258,   270,   124,   239,   188,
       3,     3,   174,   174,    45,    78,    36,   295,   171,   296,
      36,   431,   118,   188,    39,   161,   162,   190,   191,   194,
     197,   188,    37,   188,     9,    36,   232,   162,   164,   245,
     290,   170,   167,   167,   174,   322,   322,   188,   188,   263,
     188,   188,     3,   183,   277,   185,   167,   284,   220,   187,
      94,    89,   267,    66,   167,   319,   320,   321,   337,   338,
     348,   361,   362,   363,   365,   366,   367,   368,   387,   356,
      36,    36,   321,    37,    41,    41,    12,    97,    41,   321,
     380,   346,   347,   336,   337,   321,   345,   346,   345,   167,
     384,   321,   256,   407,   267,   406,   171,   408,    18,   271,
     263,   165,   296,    41,   273,    65,   167,   322,    38,   233,
     424,   178,   188,    36,    36,   254,   181,    36,   259,   296,
      41,   356,   354,   336,   333,   382,    41,   381,   263,   314,
      65,   296,   261,   276,   295,   296,   431,    50,   232,   115,
     221,   222,    36,    36,   223,   125,   383,    41,   256,   408,
     243,   167,   284,   220,   336,    36,   188,   188,   321
  };

  const short
  parser::yyr1_[] =
  {
       0,   157,   158,   159,   159,   160,   160,   160,   160,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   163,   164,   164,   164,
     165,   165,   166,   166,   167,   167,   167,   168,   168,   168,
     169,   169,   170,   170,   171,   171,   171,   172,   172,   173,
     173,   174,   174,   175,   175,   176,   176,   176,   176,   177,
     178,   178,   179,   179,   179,   179,   180,   181,   181,   182,
     183,   183,   184,   185,   185,   186,   187,   187,   188,   188,
     189,   189,   190,   190,   191,   191,   192,   192,   193,   194,
     195,   196,   196,   197,   197,   197,   197,   198,   198,   199,
     199,   200,   201,   201,   202,   203,   203,   204,   204,   205,
     205,   206,   206,   206,   207,   208,   209,   209,   209,   210,
     211,   212,   212,   213,   213,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   219,   219,   220,   220,   221,   222,
     223,   224,   224,   225,   226,   227,   227,   228,   228,   228,
     229,   230,   230,   231,   232,   232,   233,   234,   235,   236,
     236,   237,   237,   238,   238,   239,   239,   240,   240,   240,
     240,   241,   241,   241,   242,   242,   243,   243,   244,   244,
     245,   245,   245,   245,   246,   246,   246,   247,   247,   247,
     248,   248,   248,   249,   249,   250,   250,   250,   250,   251,
     251,   252,   253,   254,   254,   255,   256,   256,   256,   256,
     257,   258,   259,   259,   260,   261,   261,   262,   262,   263,
     263,   263,   263,   263,   264,   264,   265,   265,   266,   266,
     267,   268,   268,   269,   269,   270,   270,   271,   271,   272,
     273,   274,   275,   275,   276,   276,   277,   278,   279,   279,
     280,   281,   281,   282,   283,   283,   284,   285,   286,   287,
     288,   289,   290,   290,   291,   292,   292,   293,   294,   295,
     295,   296,   297,   298,   298,   298,   299,   300,   301,   301,
     302,   303,   304,   304,   305,   306,   307,   308,   308,   309,
     309,   309,   310,   311,   312,   312,   313,   314,   314,   315,
     316,   317,   318,   318,   318,   319,   320,   321,   321,   322,
     322,   322,   322,   322,   322,   322,   322,   323,   324,   325,
     325,   325,   325,   326,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   328,   329,   329,   329,   329,   330,   330,
     331,   331,   331,   332,   332,   333,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   349,   350,   350,   350,   350,   350,   350,
     350,   351,   352,   353,   354,   354,   354,   355,   356,   357,
     358,   359,   360,   360,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   369,   370,   371,   371,   371,   371,
     371,   371,   372,   372,   373,   374,   375,   376,   377,   378,
     378,   379,   379,   379,   380,   381,   381,   382,   383,   383,
     384,   385,   386,   387,   388,   389,   390,   390,   390,   390,
     390,   390,   391,   392,   392,   393,   394,   395,   396,   396,
     397,   398,   399,   400,   401,   401,   402,   402,   403,   403,
     404,   405,   405,   405,   406,   406,   407,   408,   409,   409,
     410,   411,   412,   413,   414,   414,   414,   415,   415,   415,
     416,   417,   417,   418,   419,   420,   420,   421,   422,   422,
     423,   423,   424,   424,   425,   425,   425,   426,   427,   428,
     428,   429,   429,   430,   431,   431,   432,   433,   433,   433,
     434,   435,   436,   436,   437,   438,   438,   438,   438,   439,
     439,   440,   441
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     0,
       2,     0,     1,     0,     2,     2,     0,     3,     3,     0,
       1,     0,     3,     1,     5,     3,     0,     2,     2,     2,
       2,     1,     3,     2,     0,     1,     1,     1,     1,     8,
       1,     0,     1,     1,     1,     1,     4,     3,     0,     3,
       3,     0,     3,     3,     0,     3,     3,     0,     1,     3,
       2,     0,     1,     1,     1,     1,     2,     0,     7,     1,
       2,     2,     0,     1,     1,     1,     1,     1,     1,     5,
       2,     4,     5,     3,     4,     1,     3,     2,     0,     1,
       0,     1,     1,     1,     4,     2,     2,     2,     0,     2,
       7,     1,     1,     7,     5,     1,     1,     1,     7,     5,
       1,     1,     2,     2,     7,     5,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     3,     4,     1,     1,     0,
       5,     6,     6,     3,     3,     0,     1,     6,     7,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     1,     1,
       0,     2,     1,     1,     1,     0,     1,     0,     1,     0,
       1,     1,     1,     0,     4,     3,     3,     3,     4,     1,
       1,     1,     0,     1,     0,     1,     1,     1,     1,     2,
       2,     3,     4,     3,     0,     3,     2,     2,     2,     0,
       2,     2,     3,     0,     3,     2,     2,     3,     0,     1,
       2,     3,     3,     0,     2,     2,     7,     8,     1,     0,
       1,     7,     7,     1,     0,     1,     0,     1,     0,     1,
       1,    10,     2,     0,     1,     0,     1,     2,     3,     0,
       6,     2,     0,     6,     2,     0,     1,     4,     4,     4,
       4,     5,     1,     0,     4,     2,     2,     5,     4,     3,
       0,     1,     3,     2,     2,     0,     4,     3,     4,     0,
       4,     3,     4,     0,     4,     5,     4,     1,     3,     2,
       2,     0,     2,     3,     2,     0,     5,     1,     0,     4,
       5,     6,     1,     1,     0,     1,     1,     2,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     6,     3,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     3,     3,
       1,     1,     1,     3,     3,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     4,     3,     3,     1,     0,     3,     1,     2,
       2,     2,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     3,     1,     2,
       2,     4,     3,     2,     2,     3,     0,     2,     3,     0,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     5,     4,     4,     2,     0,     4,     0,
       1,     3,     2,     2,     1,     0,     3,     1,     1,     3,
       1,     1,     1,     1,     2,     2,     3,     1,     1,     0,
       2,     1,     1,     4,     4,     3,     5,     1,     1,     1,
       6,     6,     1,     0,     2,     2,     0,     2,     1,     4,
       4,     2,     0,     3,     3,     0,     2,     2,     3,     0,
       3,     5,     1,     0,     2,     1,     0,     3,     3,     2,
       0,     4,     6
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "BASIC_NAME",
  "SINGLE_LINE_COMMENT", "UNRESTRICTED_NAME", "BLOCK_COMMENT",
  "DECIMAL_VALUE", "EXPONENTIAL_VALUE", "NUMBER", "SYMBOL_DOT_QUESTION",
  "SYMBOL_DQUESTION", "SYMBOL_QUESTION", "SYMBOL_GREATER_EQUALS",
  "SYMBOL_GREATER", "SYMBOL_IFF_NOT_EQUALS", "SYMBOL_NOT_EQUALS",
  "SYMBOL_IFF_EQUALS", "SYMBOL_EQUALS", "SYMBOL_DEF_ASSIGN",
  "SYMBOL_ASSIGN", "SYMBOL_SMALLER_EQUAL", "SYMBOL_SMALLER", "SYMBOL_DDOT",
  "SYMBOL_DOT", "SYMBOL_ARROOW", "SYMBOL_SLASH", "SYMBOL_MINUS",
  "SYMBOL_PLUS", "SYMBOL_DOUBLE_STAR", "SYMBOL_VERTICAL_LINE",
  "SYMBOL_UPPER", "SYMBOL_AND", "SYMBOL_MOD", "SYMBOL_HASHTAG",
  "SYMBOL_AT", "SYMBOL_COMMA", "SYMBOL_SQUARE_BRACKET_CLOSE",
  "SYMBOL_SQUARE_BRACKET_OPEN", "SYMBOL_CURLY_BRACKET_CLOSE",
  "SYMBOL_CURLY_BRACKET_OPEN", "SYMBOL_ROUND_BRACKET_CLOSE",
  "SYMBOL_ROUND_BRACKET_OPEN", "SYMBOL_CONJUNGATES", "SYMBOL_REDEFINES",
  "SYMBOL_REFERENCES", "SYMBOL_SPECIALIZES", "SYMBOL_TYPED_BY",
  "SYMBOL_NAMESPACE_SUBSET", "SYMBOL_STAR", "SYMBOL_STATEMENT_DELIMITER",
  "STRING", "KEYWORD_CONJUGATION", "KEYWORD_META", "KEYWORD_CONSTANT",
  "KEYWORD_LIBRARY", "KEYWORD_STANDARD", "KEYWORD_LOCALE", "KEYWORD_VAR",
  "KEYWORD_XOR", "KEYWORD_UNIONS", "KEYWORD_TYPING", "KEYWORD_TYPED",
  "KEYWORD_TYPE", "KEYWORD_TRUE", "KEYWORD_TO", "KEYWORD_THEN",
  "KEYWORD_SUCCSESSION", "KEYWORD_SUBTYPE", "KEYWORD_SUBSETS",
  "KEYWORD_SUBSET", "KEYWORD_SUBCLASSIFIER", "KEYWORD_STRUCT",
  "KEYWORD_STEP", "KEYWORD_SPECIALIZES", "KEYWORD_SPECILIZATION",
  "KEYWORD_RETURN", "KEYWORD_REP", "KEYWORD_REFERENCES",
  "KEYWORD_REDEFINITION", "KEYWORD_REDEFINES", "KEYWORD_READONLY",
  "KEYWORD_PUBLIC", "KEYWORD_PROTECTED", "KEYWORD_PRIVATE",
  "KEYWORD_PREDICATE", "KEYWORD_PORTION", "KEYWORD_PACKAGE", "KEYWORD_OUT",
  "KEYWORD_ORDERED", "KEYWORD_OR", "KEYWORD_OF", "KEYWORD_NULL",
  "KEYWORD_NOT", "KEYWORD_NONUNIQUE", "KEYWORD_NAMESPACE",
  "KEYWORD_MULTIPLICITY", "KEYWORD_METADATA", "KEYWORD_METACLASS",
  "KEYWORD_MEMBER", "KEYWORD_LANGUAGE", "KEYWORD_ISTYPE",
  "KEYWORD_INVERTING", "KEYWORD_INVERSE", "KEYWORD_INV",
  "KEYWORD_INTERACTION", "KEYWORD_INOUT", "KEYWORD_IN", "KEYWORD_IMPORT",
  "KEYWORD_IMPLIES", "KEYWORD_INTERSECTS", "KEYWORD_IF", "KEYWORD_HASTYPE",
  "KEYWORD_FUNCTION", "KEYWORD_FROM", "KEYWORD_FOR", "KEYWORD_FLOW",
  "KEYWORD_FIRST", "KEYWORD_FILTER", "KEYWORD_FEATURING",
  "KEYWORD_FEATURED", "KEYWORD_FEATURE", "KEYWORD_FALSE", "KEYWORD_EXPR",
  "KEYWORD_END", "KEYWORD_ELSE", "KEYWORD_DOC", "KEYWORD_DISJOINT",
  "KEYWORD_DISJOINING", "KEYWORD_DIFFERENCES", "KEYWORD_DERIVED",
  "KEYWORD_DEPENDENCY", "KEYWORD_DEFAULT", "KEYWORD_DATATYPE",
  "KEYWORD_CONNECTOR", "KEYWORD_CONJUGATES", "KEYWORD_CONJUGATE",
  "KEYWORD_COMPOSITE", "KEYWORD_COMMENT", "KEYWORD_CLASSIFIER",
  "KEYWORD_CLASS", "KEYWORD_CHAINS", "KEYWORD_BY", "KEYWORD_BOOL",
  "KEYWORD_BINDING", "KEYWORD_BEHAVIOR", "KEYWORD_ASSOC", "KEYWORD_AS",
  "KEYWORD_AND", "KEYWORD_ALL", "KEYWORD_ALIAS", "KEYWORD_ABSTRACT",
  "KEYWORD_ABOUT", "TPLUS", "TMINUS", "TMUL", "TDIV", "$accept", "model",
  "elements", "element", "non_feature_element", "feature_element",
  "additional_options", "type_prefix", "prefix_metadata_annotation",
  "abstract_modifier", "qualified_name", "qualified_name_tail",
  "all_modifier", "identification", "mutliplicity_bounds",
  "specialization_option", "conjugation_option", "type_body",
  "type_body_elements", "type_body_element", "type",
  "type_relationship_part_option", "type_relationship_part",
  "disjoining_part", "disjoining_part_multiplicity", "unioning_part",
  "unioning_part_multiplicity", "intersecting_part",
  "intersecting_part_multiplicity", "differencing_part",
  "differencing_part_multiplicity", "relationship_body",
  "relationship_body_elements", "relationship_body_element",
  "owned_related_element", "from_option", "dependency", "owned_annotation",
  "about_option", "locale_option", "annotating_element", "comment_option",
  "comment", "documentation", "textual_representation", "namespace",
  "namespace_body", "namesapce_body_elements", "member_prefix",
  "visiblity_indicator", "import", "import_declaration",
  "complete_namespace_import", "non_feature_member", "alias_member",
  "specializes", "specialization", "specific_type", "general_type",
  "conjunction", "owned_conjungation", "conjugation_part", "disjoining",
  "owned_disjoining", "unioning", "intersecting", "differencing",
  "feature_member", "type_feature_member", "owned_feature_member",
  "classifier", "superclassing_conjunction_option",
  "classifier_declaration", "subclassification", "superclassing_part",
  "multible_superclasses_option", "owned_subclassification", "feature",
  "feature_prefix", "abstract_option", "readonly_option", "derived_option",
  "end_option", "feature_type_option", "feature_descriptor",
  "subsettings_option", "feature_assignment_option",
  "feature_value_option", "feature_direction_option",
  "feature_declaration", "feature_identification",
  "feature_specialization_conjungation_option",
  "feature_relationship_part_option", "feature_relationship_part",
  "chaining_part", "inverting_part", "type_featuring_part",
  "type_featuting_part_multiplicity", "feature_specialization_part",
  "feature_specialization_option", "typings", "typed_by",
  "typed_by_mutliplicity", "subsettings", "subsets",
  "subsetting_multiplictiy", "multiplicity_part", "references",
  "feature_typing", "typing_option", "owned_feature_typing", "subsetting",
  "subset_option", "typed_by_option", "owned_subsetting_option",
  "owned_subsetting", "owned_reference_subsettings", "redefinition",
  "redefinition_option", "subsets_option", "owned_feature_chain",
  "feature_chain", "feature_chain_part", "feature_inverting",
  "inverting_option", "type_featuring", "of_option",
  "owned_type_featuring", "data_type", "class", "structure", "association",
  "association_structure", "type_prefix_option", "connector",
  "connector_declaration", "binary_connector_declaration",
  "nary_connector_declaration",
  "nary_connector_declaration_additional_member", "connector_end_member",
  "connector_end", "name_reference_option", "binding_connector",
  "binding_connector_declaration", "connector_end_member_of_option",
  "succession", "succession_declaration",
  "connector_end_member_first_option", "behavior", "step", "function",
  "function_body", "function_body_part_multiplicity", "function_body_part",
  "return_feature_element", "result_expression_member", "expression",
  "value_part_option", "predicate", "boolean_expression", "invariant",
  "invariant_option", "owned_expression_reference",
  "owned_expression_member", "owned_expressions", "owned_expression",
  "conditional_expression", "conditional_binary_operator_expression",
  "conditional_binary_operator", "binary_operator_expression",
  "binary_operator", "unary_operator_expression", "unary_operator",
  "classification_expression", "classification_test_operator",
  "metaclassification_expression", "argument_member", "argument",
  "argument_value", "argument_expression_member", "argument_expression",
  "argument_expression_value", "metadata_argument_member",
  "metadata_argument", "metadata_value", "metadata_reference",
  "metadataclassification_test_operator", "extend_expression",
  "type_reference_member", "type_result_member", "type_reference",
  "reference_typing", "primary_expression",
  "non_feature_chain_primary_expression", "bracket_expression",
  "index_expression", "sequence_expression", "sequence_expression_list",
  "sequence_operator_expression", "sequence_expression_list_member",
  "feature_chain_expression", "collect_expression", "select_expression",
  "function_operation_expression", "body_argument_member", "body_argument",
  "body_argument_value", "body_expression_member",
  "function_reference_argument_member", "function_reference_argument",
  "function_reference_member", "function_reference",
  "feature_chain_member", "owned_feature_chain_member", "base_expression",
  "null_expression", "feature_reference_expression",
  "feature_reference_member", "feature_reference",
  "metadata_access_expression", "invocation_expression",
  "internal_invocation_expression", "argument_list",
  "named_argument_list_option", "named_argument_list_mutliplicity",
  "positional_argument_list", "positional_argument_list_multible",
  "named_argument_member", "named_argument", "paramenter_redefinition",
  "body_expression", "expression_body_member", "expression_body",
  "literal_expression", "literal_boolean", "boolean_value",
  "literal_string", "literal_integer", "literal_real", "real_value",
  "literal_infinity", "interaction", "item_flow", "succession_item_flow",
  "item_flow_declaration", "item_flow_of_option",
  "item_flow_from_to_option", "item_feature_member", "item_feature",
  "owned_feature_typing_option", "item_feature_specilization_part",
  "item_flow_end_member", "item_flow_end", "item_flow_feature_member",
  "item_flow_feature", "item_flow_redefinition", "value_part",
  "feature_value", "euqals_assign_option", "feature_assignment",
  "multiplicity", "multiplicity_subset", "multiplicity_range",
  "multiplicity_bounds", "multiplicity_expression_member",
  "internal_multiplicity_expression_member", "metaclass", "name_option",
  "meta_specialization_option", "prefix_metadata_member",
  "prefix_metadata_feature", "metadata_feature",
  "prefix_metadata_member_multiplicity", "about_annotation",
  "about_annotation_mutliplicity", "metadata_feature_declaration",
  "identification_annotation", "package", "library_package",
  "standard_option", "package_declaration", "package_body",
  "element_filter_members", "element_filter_member", "meta_assignment", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    46,    46,    49,    50,    52,    53,    54,    55,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    96,   100,   104,   107,
     109,   112,   115,   116,   120,   128,   135,   142,   152,   162,
     168,   169,   172,   175,   179,   183,   186,   188,   192,   197,
     201,   206,   207,   212,   213,   215,   216,   217,   218,   221,
     223,   223,   225,   226,   227,   228,   230,   231,   231,   232,
     233,   233,   234,   235,   235,   236,   237,   237,   239,   240,
     244,   244,   245,   245,   246,   246,   248,   250,   252,   254,
     255,   256,   257,   258,   258,   258,   258,   259,   262,   265,
     266,   267,   268,   269,   270,   271,   271,   272,   272,   273,
     273,   274,   274,   274,   275,   276,   277,   277,   277,   280,
     282,   286,   286,   287,   288,   289,   292,   294,   298,   299,
     300,   300,   301,   302,   303,   304,   305,   305,   307,   308,
     309,   311,   311,   312,   313,   315,   316,   317,   317,   317,
     318,   319,   320,   321,   322,   322,   323,   325,   326,   327,
     327,   328,   328,   329,   329,   330,   330,   331,   331,   331,
     331,   332,   333,   334,   335,   335,   336,   336,   337,   337,
     338,   338,   338,   338,   339,   340,   341,   343,   343,   343,
     344,   344,   344,   345,   345,   346,   346,   346,   346,   347,
     348,   349,   350,   351,   351,   352,   353,   353,   353,   353,
     354,   355,   356,   356,   357,   358,   358,   359,   359,   360,
     361,   362,   363,   364,   365,   366,   373,   374,   375,   375,
     376,   378,   379,   380,   380,   381,   381,   382,   382,   383,
     384,   386,   387,   387,   388,   388,   391,   392,   393,   393,
     396,   397,   397,   400,   401,   401,   402,   404,   406,   408,
     410,   411,   412,   412,   414,   415,   416,   417,   418,   419,
     419,   420,   421,   422,   423,   424,   426,   427,   428,   428,
     430,   431,   432,   432,   434,   436,   438,   439,   439,   440,
     441,   442,   443,   444,   445,   446,   448,   449,   449,   451,
     453,   454,   455,   455,   455,   458,   459,   460,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     471,   471,   471,   472,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   474,   475,   475,   475,   475,   476,   477,
     480,   480,   480,   481,   482,   483,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   501,   501,   505,   506,   507,   508,   509,   510,
     511,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   537,   538,   539,   539,   540,   542,   543,   544,   545,
     546,   547,   548,   548,   549,   550,   551,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   561,   562,   563,   563,
     564,   565,   566,   567,   568,   569,   571,   572,   573,   574,
     575,   576,   577,   578,   578,   579,   580,   581,   582,   582,
     583,   585,   587,   588,   589,   590,   591,   591,   592,   592,
     593,   594,   595,   596,   597,   597,   598,   599,   600,   601,
     602,   603,   604,   606,   607,   608,   609,   610,   610,   610,
     611,   613,   613,   614,   615,   618,   619,   620,   621,   621,
     623,   624,   625,   625,   626,   626,   626,   628,   629,   630,
     631,   632,   632,   633,   634,   634,   635,   636,   636,   636,
     649,   650,   651,   651,   652,   653,   653,   654,   655,   656,
     656,   657,   659
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 7 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"
} } // KerML::Parser
#line 2435 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/kerml/KerMLBisonParser.cpp"

#line 660 "/home/parallels/Documents/Projekte/CPP-SysMLv2/filehandling/src/grammars/KerML.yy"


void KerML::Parser::parser::error(const std::string& msg) {
        std::cerr << "Parser-Fehler: " << msg << std::endl;
    }
