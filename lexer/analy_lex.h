#ifndef LEX_H
#define LEX_H

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include"data.h"

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