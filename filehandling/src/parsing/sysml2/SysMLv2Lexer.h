
// Generated from SysMLv2.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  SysMLv2Lexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, DEPENDENCY = 12, REPRESENTATION = 13, 
    LANGUAGE_DESCRIPTOR = 14, DOCUMENTATION = 15, COMMENT = 16, ABOUT = 17, 
    PART = 18, BLOCK_COMMENT = 19, LINE_COMMENT = 20, TO = 21, FROM = 22, 
    FOR = 23, DELIMITER = 24, PORT = 25, ITEM = 26, PACKAGE = 27, DEFINITION = 28, 
    ATTRIBUTE = 29, MEASURABLE = 30, CONTROLLABLE = 31, ASSERT = 32, ACTION = 33, 
    ALIAS = 34, PRIVATE = 35, PROTECTED = 36, PUBLIC = 37, IMPORT = 38, 
    ABSTRACT = 39, VARIATION = 40, VARIANT = 41, STAR = 42, CALC = 43, IN = 44, 
    OUT = 45, RETURN = 46, HASHTAG = 47, COMMAND = 48, VARIABLE = 49, CONNECT_TO = 50, 
    INSTANCE = 51, INDIVIDUAL = 52, SUPERCLASS = 53, NUMBER = 54, NAME = 55, 
    INT = 56, WS = 57
  };

  explicit SysMLv2Lexer(antlr4::CharStream *input);

  ~SysMLv2Lexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

