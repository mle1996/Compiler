#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

#include "token.h"
#include "lexer.h"
#include "lexer_reserved.c"

// here is a comment

struct Token** lexer(FILE *lexerin) {
  int token_list_i = 0;
  struct Token** token_list = alloc_token_list();
  char c;
  
  c = fgetc(lexerin);
  while (true) {
    char buffer[MAX_LEXEME_LEN];
    int buffer_i = 0;

    if (token_list_i > MAX_TOKENS) {
      error(0, 0, "exceeded maximum tokens");
      exit(1);
    }

    if (isalpha(c) || '_' == c) {
      // TODO: fill in the identifier/reserved word lexer

      // TODO: buffer an identifier (don't forget the \0 sentinel!)

      // hash function to match reserved words is given
      struct reserved_type *reserved = lexer_reserved(buffer, strlen(buffer));
      if (NULL != reserved) {
        // reserved word
        token_list[token_list_i++] = new_token(reserved->type);
      } else {
        // TODO: create token for identifier with its lexeme
      }
    } else if (isdigit(c)) {
        while(isdigit(c) && buffer_i < MAX_LEXEME_LEN - 1){
            buffer[buffer_i++] = c;
            c = fgetc(lexerin);
        }
        buffer[bugger_i++] = '\0';
        token_list[token_list_i++] = new_number(NUMBER,ATOI(buffer));
    } else if (ispunct(c)) {
      // TODO: fill in the rest of the punctuation-based lexemes
      if ('#' == c) { // given
        while ('\n' !=  (c = fgetc(lexerin)));
      } else if ('=' == c) { // given
        token_list[token_list_i++] = new_token(EQ);
        c = fgetc(lexerin);
      } else if (',' == c) { // given
        token_list[token_list_i++] = new_token(COMMA);
        c = fgetc(lexerin);
      // TODO: lots more else ifs here
      } else {
        error(0, 0, "invalid token");
        exit(1);
      }
    } else if (isspace(c)) {
      c = fgetc(lexerin);
    } else if (c == EOF) {
      token_list[token_list_i++] = new_token(EOT);
      break;
    }
  }
  return token_list;
}
