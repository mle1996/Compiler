#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "lexer.h"
#include "ast.h"
#include "parser.h"

#include "parser_tools.c"

static struct TranslationUnit *program();
static struct  Block *block();
static struct  TypedIdentList *vardecls();
static struct  Token *type();
static struct  FuncDeclList *funcdecls();
static struct  TypedIdentList *formals();
static struct  Statement *statement();
static struct  ExpressionList *exprlist();
static struct  Expression *expr();
static struct  Expression *simpleexpr();
static struct  Expression *term();
static struct  Expression *factor();
bool static is_relop();
bool static is_termop();
bool static is_factorop();

struct TranslationUnit* parser(struct Token** token_list_in) {
  token_list = token_list_in;
  token_i = -1;

  return program();
}

// program      ::= block PERIOD
static struct  TranslationUnit *program() {
  // given
  struct TranslationUnit *node = newTranslationUnit();

  node->block = block();

  next();
  ensure_token(EOT);

  return node;
}

// block        ::= vardecls funcdecls statement
static struct  Block *block() {
  struct Block *node = newBlock();

  // TODO: classroom exercise

  return node;
}

// vardecls     ::= { VAR IDENT COLON type }
static struct  TypedIdentList *vardecls() {
  struct TypedIdentList *list = newTypedIdentList();

  // TODO: classroom exercise

  return list;
}

// funcdelcs    ::= { FUNC IDENT LPAREN [ formals ] RPAREN [ COLON type ] block }
static struct  FuncDeclList *funcdecls() {
  struct FuncDeclList *list = newFuncDeclList();

  // TODO

  return list;
}

// formals      ::= IDENT COLON type { COMMA IDENT COLON type }
static struct  TypedIdentList *formals() {
  struct TypedIdentList *list = newTypedIdentList();

  // TODO

  return list;
}

// type         ::= INT | BOOL
static struct  Token *type() {
  // given
  next();
  if (is_token(INT) || is_token(BOOL)) {
    return token();
  } else {
    parse_error();
    return NULL;
  }
}

/*
statement    ::= [ IDENT ASSIGN expr
                 | IDENT LPAREN exprlist RPAREN
                 | RETURN expression
                 | BEGIN { statement } END
                 | IF expr THEN statement [ELSE expr]
                 | WHILE expr DO statement
                 | READ IDENT
                 | WRITE expression
                 ]
*/
static struct  Statement *statement() {
  // skeleton given to select which statement
  next();
  if (is_token(IDENT)) {

    char *name = token()->identifier;
    
    next();
    if (is_token(ASSIGN)) {
      struct Statement *node = newStatement(ASSIGNSTATEMENT);

      // TODO

      return node;
    } else if (is_token(LPAREN)) {
      struct Statement *node = newStatement(CALLSTATEMENT);

      // TODO

      return node;
    } else {
      parse_error();
      return NULL;
    }
  } else if (is_token(RETURN)) {
    struct Statement *node = newStatement(RETURNSTATEMENT);

    // TODO

    return node;
  } else if (is_token(BEGIN)) {
    struct Statement *node = newStatement(COMPOUNDSTATEMENT);

    // TODO

    return node;
  } else if (is_token(IF)) {
    struct Statement *node = newStatement(IFSTATEMENT);

    // TODO

    return node;
  } else if (is_token(WHILE)) {
    struct Statement *node = newStatement(WHILESTATEMENT);

    // TODO

    return node;
  } else if (is_token(READ)) {
    // given
    struct Statement *node = newStatement(READSTATEMENT);

    next();
    ensure_token(IDENT);
    node->read_variable = token()->identifier;
    return node;
  } else if (is_token(WRITE)) {
    // given
    struct Statement *node = newStatement(WRITESTATEMENT);

    node->write_expression = expr();
    return node;
  } else {
    parse_error();
    return NULL;
  }
}

// exprlist     ::= expr { COMMA expr }
static struct  ExpressionList *exprlist() {
  struct ExpressionList *node = newExpressionList();

  // TODO
  
  return node;
}

// expr         ::= simpleexpr [ relop simpleexpr ]
static struct  Expression *expr() {
  // TODO: classroom exercise
  struct Expression *left = simpleexpr();

  next();
  if (is_relop()) {
    struct Expression *node = newExpression(BINARYEXPRESSION);

    // TODO
    
    return node;
  } else {
    previous();
    return left;
  }
}

// relop        ::= LT | LTE | GT | GTE | EQ | NEQ
bool static is_relop() {
  //given
  switch (token()->kind) {
  case LT:
    // fall-through
  case LTE:
    // fall-through
  case GT:
    // fall-through
  case GTE:
    // fall-through
  case EQ:
    // fall-through
  case NEQ:
    return true;
  default:
    return false;
  }
}

// simpleexpr   ::= term [ termop term ]
static struct  Expression *simpleexpr() {
  // TODO (very similar to expr()
  return NULL; // be sure to change this to return a node!
}

// termop       ::= PLUS | MINUS | OR
bool static is_termop() {
  // TODO (very similar to is_relop)
  return false;  // be sure to change this to be correct!
}

// term         ::= factor [ factorop factor ]
static struct  Expression *term() {
  // TODO (very similar to expr() and simpleexpr())
  return NULL; // be sure to change this to return a node!
}

// factorop     ::= MULT | DIV | MOD | AND
bool static is_factorop() {
  // TODO (very similar to is_relop and is_termop)
  return false;  // be sure to change this to be correct!
}

static struct  Expression *factor() {
  next();
  if (is_token(IDENT)) {

    char *name = token()->identifier;

    next();

    // TODO: similar to statement() checking for assignment vs. function call
    // be sure use previous correctly when you don't see the token you expect

    return NULL; // be sure to change this to return a node!
  } else if (is_token(NUMBER)) {
    // given
    struct Expression *node = newExpression(NUMBERFACTOR);

    node->number_value = token()->number;
    return node;
  } else if (is_token(TRUE)) {
    // given
    struct Expression *node = newExpression(BOOLEANFACTOR);

    node->boolean_value = true;
    return node;
  } else if (is_token(FALSE)) {
    // TODO (very similar to above)
    return NULL; // be sure to change this to return a node!
  } else if (is_token(LPAREN)) {
    // TODO
    return NULL; // be sure to change this to return a node!
  } else if (is_token(NOT) || is_token(MINUS)) {
    // TODO
    return NULL; // be sure to change this to return a node!
  } else {
    parse_error();
    return NULL;
  }
}
