#include "data.h"

const char *TOKEN_NAMES[] = {

    "IDENTIFIANT_TOKEN",
    "NOMBRE_LITTERAL_TOKEN",
    "ERROR_TOKEN",
    "POINT_VIRGULE_TOKEN",
    "POINT_TOKEN",
    "PLUS_TOKEN",
    "MOINS_TOKEN",
    "MULT_TOKEN",
    "DIV_TOKEN",
    "VIRGULE_TOKEN",
    "AFF_TOKEN",
    "INF_TOKEN",
    "INFEG_TOKEN",
    "EG_TOKEN",
    "SUP_TOKEN",
    "SUPEG_TOKEN",
    "DIFF_TOKEN",
    "PARENTHESE_O_TOKEN",
    "PARENTHESE_F_TOKEN",
    "EOF_TOKEN",
    "STRING_TOKEN",
    "PROGRAM_TOKEN",
    "CONST_TOKEN",
    "BEGIN_TOKEN",
    "END_TOKEN",
    "IF_TOKEN",
    "THEN_TOKEN",
    "WHILE_TOKEN",
    "DO_TOKEN",
    "READ_TOKEN",
    "WRITE_TOKEN",
    "VAR_TOKEN",
    "REQUIRE_TOKEN",
    "INVERSER_TOKEN",
    "TAILLE_TOKEN",
    "TYPE_ENTIER_TOKEN",
    "TYPE_BOOLEAN_TOKEN",
    "TYPE_STRING_TOKEN",
    "TYPE_CLE_PUBLIQUE_TOKEN",
    "TYPE_SIGNATURE_TOKEN",
    "TYPE_SIGNATURE_DONNEE_TOKEN",
    "BOOLEAN_LITTERAL_TOKEN",

    "BYTES_TOKEN",
    "UNITE_TOKEN",
    "PRAGMA_TOKEN",
    "ACCOLADE_F_TOKEN",
    "ACCOLADE_O_TOKEN",
    "CONTINIUE_TOKEN",
    "CASHSCRIPT_TOKEN",
    "CONTRAT_TOKEN",
    "FONCTION_TOKEN",
    "CROCHET_O_TOKEN",
    "CROCHET_F_TOKEN",
    "OPERATEUR_NON_TOKEN",
    "OPERATEUR_MODULO_TOKEN",
    "OPERATEUR_DIFFERENT_TOKEN",
    "OPERATEUR_BINAIRE_OU_TOKEN",
    "OPERATEUR_OU_TOKEN",
    "OPERATEUR_BINAIRE_ET_TOKEN",
    "OPERATEUR_ET_TOKEN", "NOUVEAU_TOKEN",
    "OPERATEUR_BINAIRE_NON_TOKEN",
    "OPERATEUR_BINAIRE_XOR_TOKEN",
    "SPLIT_TOKEN",
    "SINON",
    "COMMENTAIRE_LIGNE_TOKEN",
    "COMMENTAIRE_TOKEN",
    "TX", "AGE", "TIME"

};
const char *TOKEN_ERRORS[] = {
    //TODO:
    "ID_ERROR",
    "NUM_ERROR",
    "LEX_ERROR",
    "expected ';' not found",
    "expected '.' not found",
    "PLUS_ERROR",
    "MOINS_ERROR",
    "MULT_ERROR",
    "DIV_ERROR",
    "expected ',' not found",
    "AFF_ERROR",
    "INF_ERROR",
    "INFEG_ERROR",
    "EG_ERROR",
    "SUP_ERROR",
    "SUPEG_ERROR",
    "DIFF_ERROR",
    "PO_ERROR",
    "PF_ERROR",
    "FIN_ERROR",
    "STRING_ERROR",
    "PROGRAM_ERROR",
    "CONST_ERROR",
    "BEGIN_ERROR",
    "END_ERROR",
    "IF_ERROR",
    "THEN_ERROR",
    "WHILE_ERROR",
    "DO_ERROR",
    "READ_ERROR",
    "WRITE_ERROR",
    "VAR_ERROR",

};
const LANGUAGE_KEYWORD pascal_keywords[] = {
    {PROGRAM_TOKEN, "program"},
    {CONST_TOKEN, "const"},
    {BEGIN_TOKEN, "begin"},
    {END_TOKEN, "end"},
    {IF_TOKEN, "if"},
    {THEN_TOKEN, "then"},
    {WHILE_TOKEN, "while"},
    {DO_TOKEN, "do"},
    {READ_TOKEN, "read"},
    {WRITE_TOKEN, "write"},
    {VAR_TOKEN, "var"},
    {REQUIRE_TOKEN, "require"},
    {INVERSER_TOKEN, "reverse"},
    {TAILLE_TOKEN, "length"},
    {TYPE_ENTIER_TOKEN, "int"},
    {TYPE_BOOLEAN_TOKEN, "bool"},
    {TYPE_STRING_TOKEN, "string"},
    {TYPE_CLE_PUBLIQUE_TOKEN, "pubkey"},
    {TYPE_SIGNATURE_TOKEN, "sig"},
    {TYPE_SIGNATURE_DONNEE_TOKEN, "datasig"},
    {BOOLEAN_LITTERAL_TOKEN, "true"},
    {BYTES_TOKEN, "bytes"},
    {UNITE_TOKEN, "satoshis"},
    {PRAGMA_TOKEN, "pragma"},

    {CASHSCRIPT_TOKEN, "cashscript"},
    {CONTRAT_TOKEN, "contract"},
    {FONCTION_TOKEN, "function"},

    {BOOLEAN_LITTERAL_TOKEN, "false"},
    {NOUVEAU_TOKEN, "new"},
    {SPLIT_TOKEN, "split"},
    {SINON, "else"},
    {TX, "tx"},
    {AGE, "age"},
    {TIME, "time"},

    {UNITE_TOKEN, "sats"},
    {UNITE_TOKEN, "finney"},
    {UNITE_TOKEN, "bits"},
    {UNITE_TOKEN, "bitcoin"},
    {UNITE_TOKEN, "seconds"},
    {UNITE_TOKEN, "minutes"},
    {UNITE_TOKEN, "hours"},
    {UNITE_TOKEN, "days"},
    {UNITE_TOKEN, "weeks"},
    {SINON, "else"},

};
const int number_of_keywords = sizeof(pascal_keywords) / sizeof(LANGUAGE_KEYWORD);