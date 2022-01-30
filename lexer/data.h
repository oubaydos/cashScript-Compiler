#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdio.h>
#include <string.h>

char curr_char;
FILE *fp;

typedef enum
{
    IDENTIFIANT_TOKEN,
    NOMBRE_LITTERAL_TOKEN,
    ERROR_TOKEN,
    POINT_VIRGULE_TOKEN,
    POINT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIRGULE_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    EG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PARENTHESE_O_TOKEN,
    PARENTHESE_F_TOKEN,
    EOF_TOKEN,
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
    REQUIRE_TOKEN,
    INVERSER_TOKEN,
    TAILLE_TOKEN,
    TYPE_ENTIER_TOKEN,
    TYPE_BOOLEAN_TOKEN,
    TYPE_STRING_TOKEN,
    TYPE_CLE_PUBLIQUE_TOKEN,
    TYPE_SIGNATURE_TOKEN,
    TYPE_SIGNATURE_DONNEE_TOKEN,
    BOOLEAN_LITTERAL_TOKEN,

    BYTES_TOKEN,
    UNITE_TOKEN,
    PRAGMA_TOKEN,
    ACCOLADE_F_TOKEN,
    ACCOLADE_O_TOKEN,
    CONTINIUE_TOKEN,
    CASHSCRIPT_TOKEN,
    CONTRAT_TOKEN,
    FONCTION_TOKEN,
    CROCHET_O_TOKEN,
    CROCHET_F_TOKEN,
    OPERATEUR_NON_TOKEN,
    OPERATEUR_MODULO_TOKEN,
    OPERATEUR_DIFFERENT_TOKEN,
    OPERATEUR_BINAIRE_OU_TOKEN,
    OPERATEUR_OU_TOKEN,
    OPERATEUR_BINAIRE_ET_TOKEN,
    OPERATEUR_ET_TOKEN,
    NOUVEAU_TOKEN,
    OPERATEUR_BINAIRE_NON_TOKEN,
    OPERATEUR_BINAIRE_XOR_TOKEN,
    SPLIT_TOKEN,
    SINON,
    COMMENTAIRE_LIGNE_TOKEN,
    COMMENTAIRE_TOKEN,
    TX,
    AGE,
    TIME

} LEX_CODE;

extern const char *TOKEN_NAMES[];
extern const char *TOKEN_ERRORS[];
typedef struct
{
    LEX_CODE code;
    char keyword[20];
} LANGUAGE_KEYWORD;

extern const LANGUAGE_KEYWORD pascal_keywords[];
extern const int number_of_keywords;
LEX_CODE curr_sym;

typedef struct
{
    LEX_CODE token;
    int line;
} SYMBOL;
SYMBOL symbols[255];

LEX_CODE last_keyword;

typedef enum
{ //Type de symbole
    VAR_TYPE,
    CONST_TYPE,
    PROGRAM_TYPE
} SYM_TYPE;

typedef struct
{ //Type de tableau d'identifiants
    char *value;
    SYM_TYPE type;
} IDS_ARR_TYPE;

IDS_ARR_TYPE IDS_ARR[100];

int ids_arr_cursor;

int current_line;

#endif
