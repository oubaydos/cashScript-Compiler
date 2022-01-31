#ifndef LEX_H
#define LEX_H
#ifndef MAX_KEYWORDS
#define MAX_KEYWORDS 255
#endif
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include"data.h"
LANGUAGE_KEYWORD identifiersTable[MAX_KEYWORDS];
int lastIdentifier = 0;

LANGUAGE_KEYWORD usedIdentifiersTable[MAX_KEYWORDS];
int lastUsedIdentifier = 0;

void lex_get_next_char();
void next_sym();
void print_token(LEX_CODE curr_sym);
void skip_white_spaces();
void skip_comment();
void read_number();
void read_word();
LEX_CODE keyword_code(char* word);
void read_string();
void analy_lex(FILE *fp);

#endif