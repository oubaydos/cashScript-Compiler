#ifndef DATA_H
#define DATA_H

#include<stdio.h>
#include<stdio.h>
#include<string.h>

char curr_char;
FILE *fp;

typedef enum {
    ID_TOKEN,
    NUM_TOKEN,
    ERROR_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    EG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    STRING_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    VAR_TOKEN,
    REQUIRE,
    INVERSER,
    TAILLE,
    TYPE_ENTIER,
    TYPE_BOOLEAN,
    TYPE_STRING,
    TYPE_CLE_PUBLIQUE,
    TYPE_SIGNATURE,
    TYPE_SIGNATURE_DONNEE,
    BOOLEAN_LITTERAL,
    
    BYTES,
    UNITE,
    PRAGMA,
    ACCOLADE_F,
    ACCOLADE_O,
CASHSCRIPT,
CONTRAT,
FONCTION,
CROCHET_O,
CROCHET_F,
OPERATEUR_NON,
OPERATEUR_MODULO,
OPERATEUR_DIFFERENT,
OPERATEUR_BINAIRE_OU,
OPERATEUR_OU,
OPERATEUR_BINAIRE_ET,
OPERATEUR_ET,NOUVEAU,
OPERATEUR_BINAIRE_NON,
OPERATEUR_BINAIRE_XOR,
SPLIT,
SINON,
COMMENTAIRE_LIGNE,
COMMENTAIRE,
TX,AGE,TIME



} LEX_CODE;

extern const char* TOKEN_NAMES[];
extern const char* TOKEN_ERRORS[];
typedef struct {
    LEX_CODE code;
    char keyword[20];
}LANGUAGE_KEYWORD;

extern const LANGUAGE_KEYWORD pascal_keywords[];
extern const int number_of_keywords;
LEX_CODE curr_sym;

typedef struct {
    LEX_CODE token;
    int line;
} SYMBOL;
SYMBOL symbols[255];

LEX_CODE last_keyword;

typedef enum { //Type de symbole
    VAR_TYPE,
    CONST_TYPE,
    PROGRAM_TYPE
} SYM_TYPE;

typedef struct { //Type de tableau d'identifiants
    char* value;
    SYM_TYPE type;
} IDS_ARR_TYPE;

IDS_ARR_TYPE IDS_ARR[100];

int ids_arr_cursor;

int current_line;

#endif
