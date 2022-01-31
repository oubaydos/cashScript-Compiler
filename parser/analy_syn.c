#include "../lexer/data.c"
#include "../lexer/analy_lex.c"
#include <unistd.h>
#include "../semantic-analyzer/semantics.c"

int cursor = 0;

void printError(LEX_CODE code) {
    if (code == CONTRAT_TOKEN) printf("Error in line 1: PRAGMA_ERROR\n");
    else printf("Error in line %d: %s\n", symbols[cursor - 1].line, TOKEN_ERRORS[code]);
}

void test_sym(LEX_CODE code) {
    if (symbols[cursor].token == code) {
        cursor++;
    } else {
        printError(code);
        exit(1);
    }
}

void PROGRAMME() {
    while (symbols[cursor].token == PRAGMA_TOKEN) {
        DIRECTIVE_PRAGMA();
    }
    DEFINITION_CONTRAT();
    test_sym(EOF_TOKEN);
}

void DIRECTIVE_PRAGMA() {
    test_sym(PRAGMA_TOKEN);
    test_sym(CASHSCRIPT_TOKEN);
    VALEUR_PRAGMA();
    test_sym(POINT_VIRGULE_TOKEN);
}

void VALEUR_PRAGMA() {
    CONTRAINTE_VERSION();
    if (symbols[cursor].token == NOMBRE_LITTERAL_TOKEN || symbols[cursor].token == OPERATEUR_BINAIRE_XOR_TOKEN
        || symbols[cursor].token == OPERATEUR_BINAIRE_NON_TOKEN || symbols[cursor].token == OPERATEUR_SUPEG_TOKEN
        || symbols[cursor].token == OPERATEUR_SUP_TOKEN || symbols[cursor].token == OPERATEUR_INF_TOKEN
        || symbols[cursor].token == OPERATEUR_INFEG_TOKEN || symbols[cursor].token == OPERATEUR_EG_TOKEN) {
        CONTRAINTE_VERSION();
    } else if (symbols[cursor].token != POINT_VIRGULE_TOKEN) {
        printError(POINT_VIRGULE_TOKEN);
        exit(EXIT_FAILURE);
    }
}

void CONTRAINTE_VERSION() {
    if (symbols[cursor].token == OPERATEUR_BINAIRE_XOR_TOKEN
        || symbols[cursor].token == OPERATEUR_BINAIRE_NON_TOKEN || symbols[cursor].token == OPERATEUR_SUPEG_TOKEN
        || symbols[cursor].token == OPERATEUR_SUP_TOKEN || symbols[cursor].token == OPERATEUR_INF_TOKEN
        || symbols[cursor].token == OPERATEUR_INFEG_TOKEN || symbols[cursor].token == OPERATEUR_EG_TOKEN) {
        OPERATEUR_VERSION();
    }
    VERSION_LITTERALE_TOKEN();
}

void OPERATEUR_VERSION() {
    switch (symbols[cursor].token) {
        case OPERATEUR_BINAIRE_XOR_TOKEN:
            test_sym(OPERATEUR_BINAIRE_XOR_TOKEN);
            break;
        case OPERATEUR_BINAIRE_NON_TOKEN:
            test_sym(OPERATEUR_BINAIRE_NON_TOKEN);
            break;
        case OPERATEUR_SUPEG_TOKEN:
            test_sym(OPERATEUR_SUPEG_TOKEN);
            break;
        case OPERATEUR_INF_TOKEN :
            test_sym(OPERATEUR_INF_TOKEN);
            break;
        case OPERATEUR_INFEG_TOKEN:
            test_sym(OPERATEUR_INFEG_TOKEN);
            break;
        case OPERATEUR_EG_TOKEN:
            test_sym(OPERATEUR_EG_TOKEN);
            break;
        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void DEFINITION_CONTRAT() {
    test_sym(CONTRAT_TOKEN);
    // --- check if identifier exists
//    asserIdentifierDoesnotExist(keywordsTable[cursor]);
    // -------------
    test_sym(IDENTIFIANT_TOKEN);
    LISTE_PARAMETRE();
    test_sym(ACCOLADE_O_TOKEN);
    while (symbols[cursor].token == FONCTION_TOKEN) {
        DEFINITION_FONCTION();
    }
    test_sym(ACCOLADE_F_TOKEN);
}

void DEFINITION_FONCTION() {
    test_sym(FONCTION_TOKEN);
    // --- check if identifier exists
//    asserIdentifierDoesnotExist(keywordsTable[cursor]);
    // -------------
    test_sym(IDENTIFIANT_TOKEN);
    LISTE_PARAMETRE();
    test_sym(ACCOLADE_O_TOKEN);
    while (symbols[cursor].token == TYPE_ENTIER_TOKEN
           || symbols[cursor].token == TYPE_BOOLEAN_TOKEN || symbols[cursor].token == TYPE_STRING_TOKEN
           || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_TOKEN
           || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN || symbols[cursor].token == BYTES_TOKEN
           || symbols[cursor].token == IDENTIFIANT_TOKEN || symbols[cursor].token == REQUIRE_TIME_TOKEN
           || symbols[cursor].token == REQUIRE_TOKEN || symbols[cursor].token == IF_TOKEN
           || symbols[cursor].token == WHILE_TOKEN || symbols[cursor].token == LIRE_TOKEN ||
           symbols[cursor].token == ECRIRE_TOKEN
            ) {
        DECLARATION();
    }
    test_sym(ACCOLADE_F_TOKEN);
}

void LISTE_PARAMETRE() {
    test_sym(PARENTHESE_O_TOKEN);
    if (symbols[cursor].token == TYPE_ENTIER_TOKEN
        || symbols[cursor].token == TYPE_BOOLEAN_TOKEN || symbols[cursor].token == TYPE_STRING_TOKEN
        || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_TOKEN
        || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN || symbols[cursor].token == BYTES_TOKEN) {
        PARAMETRE();
        while (symbols[cursor].token == VIRGULE_TOKEN && (symbols[cursor + 1].token == TYPE_ENTIER_TOKEN
                                                          || symbols[cursor + 1].token == TYPE_BOOLEAN_TOKEN ||
                                                          symbols[cursor + 1].token == TYPE_STRING_TOKEN
                                                          || symbols[cursor + 1].token == TYPE_CLE_PUBLIQUE_TOKEN ||
                                                          symbols[cursor + 1].token == TYPE_SIGNATURE_TOKEN
                                                          || symbols[cursor + 1].token == TYPE_SIGNATURE_DONNEE_TOKEN ||
                                                          symbols[cursor + 1].token == BYTES_TOKEN)) {
            test_sym(VIRGULE_TOKEN);
            PARAMETRE();
        }
        if (symbols[cursor].token == VIRGULE_TOKEN) test_sym(VIRGULE_TOKEN);

    }
    test_sym(PARENTHESE_F_TOKEN);
}

void PARAMETRE() {
    NOM_TYPE();
    // --- check if identifier exists
//    asserIdentifierDoesnotExist(keywordsTable[cursor]);
    // -------------
    test_sym(IDENTIFIANT_TOKEN);
}

void BLOC() {
    if (symbols[cursor].token == ACCOLADE_O_TOKEN) {
        test_sym(ACCOLADE_O_TOKEN);
        while (symbols[cursor].token == TYPE_ENTIER_TOKEN
               || symbols[cursor].token == TYPE_BOOLEAN_TOKEN || symbols[cursor].token == TYPE_STRING_TOKEN
               || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_TOKEN
               || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN || symbols[cursor].token == BYTES_TOKEN
               || symbols[cursor].token == IDENTIFIANT_TOKEN || symbols[cursor].token == REQUIRE_TIME_TOKEN
               || symbols[cursor].token == REQUIRE_TOKEN || symbols[cursor].token == IF_TOKEN ||
               symbols[cursor].token == WHILE_TOKEN
               || symbols[cursor].token == ECRIRE_TOKEN || symbols[cursor].token == LIRE_TOKEN
                ) {
            DECLARATION();
        }
        test_sym(ACCOLADE_F_TOKEN);
    } else if (symbols[cursor].token == TYPE_ENTIER_TOKEN
               || symbols[cursor].token == TYPE_BOOLEAN_TOKEN || symbols[cursor].token == TYPE_STRING_TOKEN
               || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_TOKEN
               || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN || symbols[cursor].token == BYTES_TOKEN
               || symbols[cursor].token == IDENTIFIANT_TOKEN || symbols[cursor].token == REQUIRE_TIME_TOKEN
               || symbols[cursor].token == REQUIRE_TOKEN || symbols[cursor].token == IF_TOKEN ||
               symbols[cursor].token == WHILE_TOKEN
               || symbols[cursor].token == ECRIRE_TOKEN || symbols[cursor].token == LIRE_TOKEN) {
        DECLARATION();
    } else {
        printError(ERROR_TOKEN);
        exit(EXIT_FAILURE);
    }

}


void DECLARATION() {
    if (symbols[cursor].token == TYPE_ENTIER_TOKEN
        || symbols[cursor].token == TYPE_BOOLEAN_TOKEN || symbols[cursor].token == TYPE_STRING_TOKEN
        || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_TOKEN
        || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN || symbols[cursor].token == BYTES_TOKEN) {
        DEFINITION_VARIABLE();
    } else if (symbols[cursor].token == IDENTIFIANT_TOKEN) {
        AFFECTATION();
    } else if (symbols[cursor].token == REQUIRE_TIME_TOKEN) {
        TEMPS_DECLARATION();
    } else if (symbols[cursor].token == REQUIRE_TOKEN) {
        requireStatement();
    } else if (symbols[cursor].token == IF_TOKEN) {
        SI();
    } else if (symbols[cursor].token == WHILE_TOKEN) {
        WHILE();
    } else if (symbols[cursor].token == ECRIRE_TOKEN) {
        ECRIRE();
    } else if (symbols[cursor].token == LIRE_TOKEN) {
        LIRE();
    } else {
        printError(ERROR_TOKEN);
        exit(EXIT_FAILURE);
    }
}

void DEFINITION_VARIABLE() {
    NOM_TYPE();
    // --- check if identifier exists
//    asserIdentifierDoesnotExist(keywordsTable[cursor]);
    // -------------
    test_sym(IDENTIFIANT_TOKEN);
    test_sym(OPERATEUR_EG_TOKEN);
    EXPRESSION();
    test_sym(POINT_VIRGULE_TOKEN);
}

void AFFECTATION() {
    // --- check if identifier exists
//    asserIdentifierExistsBeforeUse(keywordsTable[cursor]);
    // -------------
    test_sym(IDENTIFIANT_TOKEN);
    test_sym(OPERATEUR_EG_TOKEN);
    EXPRESSION();
    test_sym(POINT_VIRGULE_TOKEN);
}

void TEMPS_DECLARATION() {
    test_sym(REQUIRE_TIME_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    TX_VAR_TOKEN();
    test_sym(OPERATEUR_SUPEG_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(POINT_VIRGULE_TOKEN);
}
int temp = 0;
void requireStatement() {
    temp++;
    test_sym(REQUIRE_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(POINT_VIRGULE_TOKEN);
}

void SI() {
    test_sym(IF_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    BLOC();
    if (symbols[cursor].token == SINON) {
        test_sym(SINON);
        BLOC();
    } else if (symbols[cursor].token != ACCOLADE_F_TOKEN) {
        printError(ACCOLADE_F_TOKEN);
        exit(EXIT_FAILURE);
    }
}

void FONCTION() {
    // --- check if identifier exists
//    asserIdentifierDoesnotExist(keywordsTable[cursor]);
    // -------------
    test_sym(IDENTIFIANT_TOKEN);
}

void LISTE_EXPRESSIONS() {
    test_sym(PARENTHESE_O_TOKEN);
    if (symbols[cursor].token == PARENTHESE_O_TOKEN
        || symbols[cursor].token == TYPE_ENTIER_TOKEN || symbols[cursor].token == TYPE_BOOLEAN_TOKEN
        || symbols[cursor].token == TYPE_STRING_TOKEN || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN
        || symbols[cursor].token == TYPE_SIGNATURE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN
        || symbols[cursor].token == BYTES_TOKEN || symbols[cursor].token == NOUVEAU_TOKEN
        || symbols[cursor].token == IDENTIFIANT_TOKEN || symbols[cursor].token == TRUE_TOKEN
        || symbols[cursor].token == FALSE_TOKEN || symbols[cursor].token == NOMBRE_LITTERAL_TOKEN
        || symbols[cursor].token == GUILLEMET_SIMPLE_TOKEN || symbols[cursor].token == GUILLEMET_TOKEN
        || symbols[cursor].token == DATE_TOKEN || symbols[cursor].token == HEX_LITTERAL_TOKEN ||
        symbols[cursor].token == OPERATEUR_NON_TOKEN
        || symbols[cursor].token == OPERATEUR_MOINS_TOKEN || symbols[cursor].token == CROCHET_O_TOKEN
        || symbols[cursor].token == TX_VERSION_TOKEN || symbols[cursor].token == TX_HASHPREVOUTS_TOKEN ||
        symbols[cursor].token == TX_HASHSEQUENCE_TOKEN
        || symbols[cursor].token == TX_OUTPOINT_TOKEN || symbols[cursor].token == TX_BYTECODE_TOKEN ||
        symbols[cursor].token == TX_VALUE_TOKEN
        || symbols[cursor].token == TX_SEQUENCE_TOKEN || symbols[cursor].token == TX_HASHOUTPUTS_TOKEN ||
        symbols[cursor].token == TX_LOCKTIME_TOKEN
        || symbols[cursor].token == TX_HASHTYPE_TOKEN || symbols[cursor].token == TX_PREIMAGE_TOKEN
            ) {
        EXPRESSION();
        while (symbols[cursor].token == VIRGULE_TOKEN && (symbols[cursor + 1].token == PARENTHESE_O_TOKEN
                                                          || symbols[cursor + 1].token == TYPE_ENTIER_TOKEN ||
                                                          symbols[cursor + 1].token == TYPE_BOOLEAN_TOKEN
                                                          || symbols[cursor + 1].token == TYPE_STRING_TOKEN ||
                                                          symbols[cursor + 1].token == TYPE_CLE_PUBLIQUE_TOKEN
                                                          || symbols[cursor + 1].token == TYPE_SIGNATURE_TOKEN ||
                                                          symbols[cursor + 1].token == TYPE_SIGNATURE_DONNEE_TOKEN
                                                          || symbols[cursor + 1].token == BYTES_TOKEN ||
                                                          symbols[cursor + 1].token == NOUVEAU_TOKEN
                                                          || symbols[cursor + 1].token == IDENTIFIANT_TOKEN ||
                                                          symbols[cursor + 1].token == TRUE_TOKEN
                                                          || symbols[cursor + 1].token == FALSE_TOKEN ||
                                                          symbols[cursor + 1].token == NOMBRE_LITTERAL_TOKEN
                                                          || symbols[cursor + 1].token == GUILLEMET_SIMPLE_TOKEN ||
                                                          symbols[cursor + 1].token == GUILLEMET_TOKEN
                                                          || symbols[cursor + 1].token == DATE_TOKEN ||
                                                          symbols[cursor + 1].token == HEX_LITTERAL_TOKEN ||
                                                          symbols[cursor + 1].token == OPERATEUR_NON_TOKEN
                                                          || symbols[cursor + 1].token == OPERATEUR_MOINS_TOKEN ||
                                                          symbols[cursor + 1].token == CROCHET_O_TOKEN
                                                          || symbols[cursor + 1].token == TX_VERSION_TOKEN ||
                                                          symbols[cursor + 1].token == TX_HASHPREVOUTS_TOKEN ||
                                                          symbols[cursor + 1].token == TX_HASHSEQUENCE_TOKEN
                                                          || symbols[cursor + 1].token == TX_OUTPOINT_TOKEN ||
                                                          symbols[cursor + 1].token == TX_BYTECODE_TOKEN ||
                                                          symbols[cursor + 1].token == TX_VALUE_TOKEN
                                                          || symbols[cursor + 1].token == TX_SEQUENCE_TOKEN ||
                                                          symbols[cursor + 1].token == TX_HASHOUTPUTS_TOKEN ||
                                                          symbols[cursor + 1].token == TX_LOCKTIME_TOKEN
                                                          || symbols[cursor + 1].token == TX_HASHTYPE_TOKEN ||
                                                          symbols[cursor + 1].token == TX_PREIMAGE_TOKEN)) {
            test_sym(VIRGULE_TOKEN);
            EXPRESSION();
        }
        if (symbols[cursor].token == VIRGULE_TOKEN) { test_sym(VIRGULE_TOKEN); }
    }
    test_sym(PARENTHESE_F_TOKEN);
}

void EXPRESSION() {
    if (symbols[cursor].token == PARENTHESE_O_TOKEN) {
        test_sym(PARENTHESE_O_TOKEN);
        EXPRESSION();
        test_sym(PARENTHESE_F_TOKEN);
    } else if (symbols[cursor].token == TYPE_ENTIER_TOKEN
               || symbols[cursor].token == TYPE_BOOLEAN_TOKEN || symbols[cursor].token == TYPE_STRING_TOKEN
               || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_TOKEN
               || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN || symbols[cursor].token == BYTES_TOKEN) {
        NOM_TYPE();
        test_sym(PARENTHESE_O_TOKEN);
        EXPRESSION();
        if (symbols[cursor].token == VIRGULE_TOKEN &&
            (symbols[cursor + 1].token == PARENTHESE_O_TOKEN
             || symbols[cursor + 1].token == TYPE_ENTIER_TOKEN || symbols[cursor + 1].token == TYPE_BOOLEAN_TOKEN
             || symbols[cursor + 1].token == TYPE_STRING_TOKEN || symbols[cursor + 1].token == TYPE_CLE_PUBLIQUE_TOKEN
             || symbols[cursor + 1].token == TYPE_SIGNATURE_TOKEN ||
             symbols[cursor + 1].token == TYPE_SIGNATURE_DONNEE_TOKEN
             || symbols[cursor + 1].token == BYTES_TOKEN || symbols[cursor + 1].token == NOUVEAU_TOKEN
             || symbols[cursor + 1].token == IDENTIFIANT_TOKEN || symbols[cursor + 1].token == TRUE_TOKEN
             || symbols[cursor + 1].token == FALSE_TOKEN || symbols[cursor + 1].token == NOMBRE_LITTERAL_TOKEN
             || symbols[cursor + 1].token == GUILLEMET_SIMPLE_TOKEN || symbols[cursor + 1].token == GUILLEMET_TOKEN
             || symbols[cursor + 1].token == DATE_TOKEN || symbols[cursor + 1].token == HEX_LITTERAL_TOKEN ||
             symbols[cursor + 1].token == OPERATEUR_NON_TOKEN
             || symbols[cursor + 1].token == OPERATEUR_MOINS_TOKEN || symbols[cursor + 1].token == CROCHET_O_TOKEN
             || symbols[cursor + 1].token == TX_VERSION_TOKEN || symbols[cursor + 1].token == TX_HASHPREVOUTS_TOKEN ||
             symbols[cursor + 1].token == TX_HASHSEQUENCE_TOKEN
             || symbols[cursor + 1].token == TX_OUTPOINT_TOKEN || symbols[cursor + 1].token == TX_BYTECODE_TOKEN ||
             symbols[cursor + 1].token == TX_VALUE_TOKEN
             || symbols[cursor + 1].token == TX_SEQUENCE_TOKEN || symbols[cursor + 1].token == TX_HASHOUTPUTS_TOKEN ||
             symbols[cursor + 1].token == TX_LOCKTIME_TOKEN
             || symbols[cursor + 1].token == TX_HASHTYPE_TOKEN || symbols[cursor + 1].token == TX_PREIMAGE_TOKEN
            )) {
            test_sym(VIRGULE_TOKEN);
            EXPRESSION();
        } else if (symbols[cursor].token == VIRGULE_TOKEN) test_sym(symbols[cursor].token == VIRGULE_TOKEN);
        test_sym(PARENTHESE_F_TOKEN);
    } else if (symbols[cursor].token == NOUVEAU_TOKEN) {
        test_sym(NOUVEAU_TOKEN);
        // --- check if identifier exists
//        asserIdentifierExistsBeforeUse(keywordsTable[cursor]);
        // -------------
        test_sym(IDENTIFIANT_TOKEN);
        LISTE_EXPRESSIONS();
    } else if (symbols[cursor].token == IDENTIFIANT_TOKEN) {
        // added by oubaydos - may produce errors
        test_sym(IDENTIFIANT_TOKEN);
        // -
        switch (symbols[cursor].token) {
            case PARENTHESE_O_TOKEN:
                LISTE_EXPRESSIONS();
                break;
            case INVERSER_TOKEN:
                test_sym(INVERSER_TOKEN);
                break;
            case TAILLE_TOKEN:
                test_sym(TAILLE_TOKEN);
                break;
            case CROCHET_O_TOKEN: {
                test_sym(CROCHET_O_TOKEN);
                test_sym(NOMBRE_LITTERAL_TOKEN);
                test_sym(CROCHET_F_TOKEN);
            };
                break;
            case SPLIT_TOKEN: {
//                            assertStringOperationsAreValid(keywordsTable[cursor-1]);
                test_sym(SPLIT_TOKEN);
                test_sym(PARENTHESE_O_TOKEN);
                EXPRESSION();
                test_sym(PARENTHESE_F_TOKEN);
            };
                break;
            case OPERATEUR_FOIS_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case DIV_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_MODULO_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_PLUS_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_MOINS_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_INF_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_INFEG_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_SUP_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_SUPEG_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_EG_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_DIFFERENT_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_BINAIRE_ET_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_BINAIRE_XOR_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_BINAIRE_OU_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_ET_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_OU_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_EGAL_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;

        }
    } else if (symbols[cursor].token == TRUE_TOKEN || symbols[cursor].token == FALSE_TOKEN ||
               symbols[cursor].token == NOMBRE_LITTERAL_TOKEN
               || symbols[cursor].token == GUILLEMET_SIMPLE_TOKEN || symbols[cursor].token == GUILLEMET_TOKEN ||
               symbols[cursor].token == DATE_TOKEN
               || symbols[cursor].token == HEX_LITTERAL_TOKEN
            ) {
        LITTERAL();
        switch (symbols[cursor].token) {
            case INVERSER_TOKEN:
                test_sym(INVERSER_TOKEN);
                break;
            case TAILLE_TOKEN:
                test_sym(TAILLE_TOKEN);
                break;
            case CROCHET_O_TOKEN: {
                test_sym(CROCHET_O_TOKEN);
                test_sym(NOMBRE_LITTERAL_TOKEN);
                test_sym(CROCHET_F_TOKEN);
            }
                break;
            case SPLIT_TOKEN: {
//                            assertStringOperationsAreValid(keywordsTable[cursor-1]);
                test_sym(SPLIT_TOKEN);
                test_sym(PARENTHESE_O_TOKEN);
                EXPRESSION();
                test_sym(PARENTHESE_F_TOKEN);
                break;
            }
            case OPERATEUR_FOIS_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case DIV_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_MODULO_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_PLUS_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_MOINS_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_INF_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_INFEG_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_SUP_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_SUPEG_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_EG_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_DIFFERENT_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_BINAIRE_ET_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_BINAIRE_XOR_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_BINAIRE_OU_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_ET_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case OPERATEUR_OU_TOKEN:
                DEUXIEME_EXPRESSION_BINAIRE();
                break;
            case POINT_VIRGULE_TOKEN:
                if (symbols[cursor-1].token == GUILLEMET_SIMPLE_TOKEN || symbols[cursor - 1].token == GUILLEMET_TOKEN)
                    break;
//                else {
//                    printError(POINT_VIRGULE_TOKEN);
//                    exit(EXIT_FAILURE);
//                    break;
//                }

        }
    } else if (symbols[cursor].token == OPERATEUR_NON_TOKEN) {
        test_sym(OPERATEUR_NON_TOKEN);
        EXPRESSION();
    } else if (symbols[cursor].token == OPERATEUR_MOINS_TOKEN) {
        test_sym(OPERATEUR_MOINS_TOKEN);
        EXPRESSION();
    } else if (symbols[cursor].token == CROCHET_O_TOKEN) {
        test_sym(CROCHET_O_TOKEN);
        if (symbols[cursor].token == PARENTHESE_O_TOKEN
            || symbols[cursor].token == TYPE_ENTIER_TOKEN || symbols[cursor].token == TYPE_BOOLEAN_TOKEN
            || symbols[cursor].token == TYPE_STRING_TOKEN || symbols[cursor].token == TYPE_CLE_PUBLIQUE_TOKEN
            || symbols[cursor].token == TYPE_SIGNATURE_TOKEN || symbols[cursor].token == TYPE_SIGNATURE_DONNEE_TOKEN
            || symbols[cursor].token == BYTES_TOKEN || symbols[cursor].token == NOUVEAU_TOKEN
            || symbols[cursor].token == IDENTIFIANT_TOKEN || symbols[cursor].token == TRUE_TOKEN
            || symbols[cursor].token == FALSE_TOKEN || symbols[cursor].token == NOMBRE_LITTERAL_TOKEN
            || symbols[cursor].token == GUILLEMET_SIMPLE_TOKEN || symbols[cursor].token == GUILLEMET_TOKEN
            || symbols[cursor].token == DATE_TOKEN || symbols[cursor].token == HEX_LITTERAL_TOKEN ||
            symbols[cursor].token == OPERATEUR_NON_TOKEN
            || symbols[cursor].token == OPERATEUR_MOINS_TOKEN || symbols[cursor].token == CROCHET_O_TOKEN
            || symbols[cursor].token == TX_VERSION_TOKEN || symbols[cursor].token == TX_HASHPREVOUTS_TOKEN ||
            symbols[cursor].token == TX_HASHSEQUENCE_TOKEN
            || symbols[cursor].token == TX_OUTPOINT_TOKEN || symbols[cursor].token == TX_BYTECODE_TOKEN ||
            symbols[cursor].token == TX_VALUE_TOKEN
            || symbols[cursor].token == TX_SEQUENCE_TOKEN || symbols[cursor].token == TX_HASHOUTPUTS_TOKEN ||
            symbols[cursor].token == TX_LOCKTIME_TOKEN
            || symbols[cursor].token == TX_HASHTYPE_TOKEN || symbols[cursor].token == TX_PREIMAGE_TOKEN
                ) {
            EXPRESSION();
            while (symbols[cursor].token == VIRGULE_TOKEN && (symbols[cursor + 1].token == PARENTHESE_O_TOKEN
                                                              || symbols[cursor + 1].token == TYPE_ENTIER_TOKEN ||
                                                              symbols[cursor + 1].token == TYPE_BOOLEAN_TOKEN
                                                              || symbols[cursor + 1].token == TYPE_STRING_TOKEN ||
                                                              symbols[cursor + 1].token == TYPE_CLE_PUBLIQUE_TOKEN
                                                              || symbols[cursor + 1].token == TYPE_SIGNATURE_TOKEN ||
                                                              symbols[cursor + 1].token == TYPE_SIGNATURE_DONNEE_TOKEN
                                                              || symbols[cursor + 1].token == BYTES_TOKEN ||
                                                              symbols[cursor + 1].token == NOUVEAU_TOKEN
                                                              || symbols[cursor + 1].token == IDENTIFIANT_TOKEN ||
                                                              symbols[cursor + 1].token == TRUE_TOKEN
                                                              || symbols[cursor + 1].token == FALSE_TOKEN ||
                                                              symbols[cursor + 1].token == NOMBRE_LITTERAL_TOKEN
                                                              || symbols[cursor + 1].token == GUILLEMET_SIMPLE_TOKEN ||
                                                              symbols[cursor + 1].token == GUILLEMET_TOKEN
                                                              || symbols[cursor + 1].token == DATE_TOKEN ||
                                                              symbols[cursor + 1].token == HEX_LITTERAL_TOKEN ||
                                                              symbols[cursor + 1].token == OPERATEUR_NON_TOKEN
                                                              || symbols[cursor + 1].token == OPERATEUR_MOINS_TOKEN ||
                                                              symbols[cursor + 1].token == CROCHET_O_TOKEN
                                                              || symbols[cursor + 1].token == TX_VERSION_TOKEN ||
                                                              symbols[cursor + 1].token == TX_HASHPREVOUTS_TOKEN ||
                                                              symbols[cursor + 1].token == TX_HASHSEQUENCE_TOKEN
                                                              || symbols[cursor + 1].token == TX_OUTPOINT_TOKEN ||
                                                              symbols[cursor + 1].token == TX_BYTECODE_TOKEN ||
                                                              symbols[cursor + 1].token == TX_VALUE_TOKEN
                                                              || symbols[cursor + 1].token == TX_SEQUENCE_TOKEN ||
                                                              symbols[cursor + 1].token == TX_HASHOUTPUTS_TOKEN ||
                                                              symbols[cursor + 1].token == TX_LOCKTIME_TOKEN
                                                              || symbols[cursor + 1].token == TX_HASHTYPE_TOKEN ||
                                                              symbols[cursor + 1].token == TX_PREIMAGE_TOKEN)) {
                test_sym(VIRGULE_TOKEN);
                EXPRESSION();
            }
            if (symbols[cursor].token == VIRGULE_TOKEN) { test_sym(VIRGULE_TOKEN); }
        }
        test_sym(CROCHET_F_TOKEN);
    } else if (symbols[cursor].token == TX_VERSION_TOKEN || symbols[cursor].token == TX_HASHPREVOUTS_TOKEN
               || symbols[cursor].token == TX_HASHSEQUENCE_TOKEN || symbols[cursor].token == TX_OUTPOINT_TOKEN
               || symbols[cursor].token == TX_BYTECODE_TOKEN || symbols[cursor].token == TX_VALUE_TOKEN
               || symbols[cursor].token == TX_SEQUENCE_TOKEN || symbols[cursor].token == TX_HASHOUTPUTS_TOKEN
               || symbols[cursor].token == TX_LOCKTIME_TOKEN || symbols[cursor].token == TX_HASHTYPE_TOKEN
               || symbols[cursor].token == TX_PREIMAGE_TOKEN
            ) {
        CHAMP_AVANT_IMAGE_TOKEN();
    } else {
        printError(ERROR_TOKEN);
        exit(EXIT_FAILURE);
    }
}

void DEUXIEME_EXPRESSION_BINAIRE() {
    switch (symbols[cursor].token) {
        case OPERATEUR_FOIS_TOKEN:
            test_sym(OPERATEUR_FOIS_TOKEN);
            break;
        case DIV_TOKEN:
            test_sym(DIV_TOKEN);
            break;
        case OPERATEUR_MODULO_TOKEN:
            test_sym(OPERATEUR_MODULO_TOKEN);
            break;
        case OPERATEUR_PLUS_TOKEN:
            // assertPlusOperationIsValid(keywordsTable[cursor-1],keywordsTable[cursor+1]);
            test_sym(OPERATEUR_PLUS_TOKEN);
            break;
        case OPERATEUR_MOINS_TOKEN:
            test_sym(OPERATEUR_MOINS_TOKEN);
            break;
        case OPERATEUR_INF_TOKEN:
            test_sym(OPERATEUR_INF_TOKEN);
            break;
        case OPERATEUR_INFEG_TOKEN:
            test_sym(OPERATEUR_INFEG_TOKEN);
            break;
        case OPERATEUR_SUP_TOKEN:
            test_sym(OPERATEUR_SUP_TOKEN);
            break;
        case OPERATEUR_SUPEG_TOKEN:
            test_sym(OPERATEUR_SUPEG_TOKEN);
            break;
        case OPERATEUR_EGAL_TOKEN:
            test_sym(OPERATEUR_EGAL_TOKEN);
            break;
        case OPERATEUR_DIFFERENT_TOKEN:
            test_sym(OPERATEUR_DIFFERENT_TOKEN);
            break;
        case OPERATEUR_BINAIRE_ET_TOKEN:
            test_sym(OPERATEUR_BINAIRE_ET_TOKEN);
            break;
        case OPERATEUR_BINAIRE_XOR_TOKEN:
            test_sym(OPERATEUR_BINAIRE_XOR_TOKEN);
            break;
        case OPERATEUR_BINAIRE_OU_TOKEN:
            test_sym(OPERATEUR_BINAIRE_OU_TOKEN);
            break;
        case OPERATEUR_ET_TOKEN:
            test_sym(OPERATEUR_ET_TOKEN);
            break;
        case OPERATEUR_OU_TOKEN:
            test_sym(OPERATEUR_OU_TOKEN);
            break;

        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (symbols[cursor].token == IDENTIFIANT_TOKEN) {
        // --- check if identifier exists
//        asserIdentifierExistsBeforeUse(keywordsTable[cursor]);
        // -------------
        test_sym(IDENTIFIANT_TOKEN);
    } else if (symbols[cursor].token == TRUE_TOKEN || symbols[cursor].token == FALSE_TOKEN ||
               symbols[cursor].token == NOMBRE_LITTERAL_TOKEN
               || symbols[cursor].token == GUILLEMET_SIMPLE_TOKEN || symbols[cursor].token == GUILLEMET_TOKEN ||
               symbols[cursor].token == DATE_TOKEN
               || symbols[cursor].token == HEX_LITTERAL_TOKEN
            ) {
        LITTERAL();
    } else {
        printError(ERROR_TOKEN);
        exit(EXIT_FAILURE);
    }
}

void LITTERAL() {
    switch (symbols[cursor].token) {
        case TRUE_TOKEN :
            BOOLEAN_LITTERAL_TOKEN();
            break;
        case FALSE_TOKEN :
            BOOLEAN_LITTERAL_TOKEN();
            break;
        case NOMBRE_LITTERAL_TOKEN :
            NOMBRE_LITTERAL();
            break;
        case GUILLEMET_SIMPLE_TOKEN :
            STRING_LITTERAL_TOKEN();
            break;
        case GUILLEMET_TOKEN :
            STRING_LITTERAL_TOKEN();
            break;
        case DATE_TOKEN :
            DATE_LITTERAL();
            break;
        case HEX_LITTERAL_TOKEN :
            test_sym(HEX_LITTERAL_TOKEN);
            break;
        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void NOMBRE_LITTERAL() {
    test_sym(NOMBRE_LITTERAL_TOKEN);
    if (symbols[cursor].token == SATOSHIS_TOKEN || symbols[cursor].token == SATS_TOKEN
        || symbols[cursor].token == FINNEY_TOKEN || symbols[cursor].token == BITS_TOKEN
        || symbols[cursor].token == BITCOIN_TOKEN || symbols[cursor].token == SECONDS_TOKEN
        || symbols[cursor].token == MINUTES_TOKEN || symbols[cursor].token == HOURS_TOKEN
        || symbols[cursor].token == DAYS_TOKEN || symbols[cursor].token == WEEKS_TOKEN
            ) {
        UNITE_TOKEN();
    }
}

void NOM_TYPE() {
    switch (symbols[cursor].token) {
        case TYPE_ENTIER_TOKEN:
            test_sym(TYPE_ENTIER_TOKEN);
            break;
        case TYPE_BOOLEAN_TOKEN:
            test_sym(TYPE_BOOLEAN_TOKEN);
            break;
        case TYPE_STRING_TOKEN:
            test_sym(TYPE_STRING_TOKEN);
            break;
        case TYPE_CLE_PUBLIQUE_TOKEN:
            test_sym(TYPE_CLE_PUBLIQUE_TOKEN);
            break;
        case TYPE_SIGNATURE_TOKEN:
            test_sym(TYPE_SIGNATURE_TOKEN);
            break;
        case TYPE_SIGNATURE_DONNEE_TOKEN:
            test_sym(TYPE_SIGNATURE_DONNEE_TOKEN);
            break;
        case BYTES_TOKEN:
            BYTES();
            break;

        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void DATE_LITTERAL() {
    test_sym(DATE_TOKEN);
    STRING_LITTERAL_TOKEN();
    test_sym(PARENTHESE_F_TOKEN);

}

void WHILE() {
    test_sym(WHILE_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    BLOC();
}

void ECRIRE() {
    test_sym(ECRIRE_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(POINT_VIRGULE_TOKEN);

}

void LIRE() {
    test_sym(LIRE_TOKEN);
    // --- check if identifier exists
//    asserIdentifierExistsBeforeUse(keywordsTable[cursor]);
    // -------------
    test_sym(PARENTHESE_O_TOKEN);
    test_sym(IDENTIFIANT_TOKEN);
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(POINT_VIRGULE_TOKEN);
}

void VERSION_LITTERALE_TOKEN() {
//    assertNumberIsPositive(keywordsTable[cursor]);
    test_sym(NOMBRE_LITTERAL_TOKEN);
    test_sym(POINT_TOKEN);
//    assertNumberIsPositive(keywordsTable[cursor]);
    test_sym(NOMBRE_LITTERAL_TOKEN);
    test_sym(POINT_TOKEN);
//    assertNumberIsPositive(keywordsTable[cursor]);
    test_sym(NOMBRE_LITTERAL_TOKEN);
}

void BOOLEAN_LITTERAL_TOKEN() {
    switch (symbols[cursor].token) {
        case TRUE_TOKEN:
            test_sym(TRUE_TOKEN);
            break;
        case FALSE_TOKEN:
            test_sym(FALSE_TOKEN);
            break;
        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void UNITE_TOKEN() {
    switch (symbols[cursor].token) {
        case SATOSHIS_TOKEN:
            test_sym(SATOSHIS_TOKEN);
            break;
        case SATS_TOKEN:
            test_sym(SATS_TOKEN);
            break;
        case FINNEY_TOKEN:
            test_sym(FINNEY_TOKEN);
            break;
        case BITS_TOKEN:
            test_sym(BITS_TOKEN);
            break;
        case BITCOIN_TOKEN:
            test_sym(BITCOIN_TOKEN);
            break;
        case SECONDS_TOKEN:
            test_sym(SECONDS_TOKEN);
            break;
        case MINUTES_TOKEN:
            test_sym(MINUTES_TOKEN);
            break;
        case HOURS_TOKEN:
            test_sym(HOURS_TOKEN);
            break;
        case DAYS_TOKEN:
            test_sym(DAYS_TOKEN);
            break;
        case WEEKS_TOKEN:
            test_sym(WEEKS_TOKEN);
            break;

        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void STRING_LITTERAL_TOKEN() {
    switch (symbols[cursor].token) {
        case GUILLEMET_SIMPLE_TOKEN: {
            test_sym(GUILLEMET_SIMPLE_TOKEN);
            test_sym(STRING_VALEUR_TOKEN);
            test_sym(GUILLEMET_SIMPLE_TOKEN);
            break;
        }
        case GUILLEMET_TOKEN : {
            test_sym(GUILLEMET_TOKEN);
            test_sym(STRING_VALEUR_TOKEN);
            test_sym(GUILLEMET_TOKEN);
            break;
        }

        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void TX_VAR_TOKEN() {
    switch (symbols[cursor].token) {
        case TX_AGE_TOKEN:
            test_sym(TX_AGE_TOKEN);
            break;
        case TX_TIME_TOKEN:
            test_sym(TX_TIME_TOKEN);
            break;
        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void CHAMP_AVANT_IMAGE_TOKEN() {
    switch (symbols[cursor].token) {
        case TX_VERSION_TOKEN:
            test_sym(TX_VERSION_TOKEN);
            break;
        case TX_HASHPREVOUTS_TOKEN:
            test_sym(TX_HASHPREVOUTS_TOKEN);
            break;
        case TX_HASHSEQUENCE_TOKEN:
            test_sym(TX_HASHSEQUENCE_TOKEN);
            break;
        case TX_OUTPOINT_TOKEN:
            test_sym(TX_OUTPOINT_TOKEN);
            break;
        case TX_BYTECODE_TOKEN:
            test_sym(TX_BYTECODE_TOKEN);
            break;
        case TX_VALUE_TOKEN:
            test_sym(TX_VALUE_TOKEN);
            break;
        case TX_SEQUENCE_TOKEN:
            test_sym(TX_SEQUENCE_TOKEN);
            break;
        case TX_HASHOUTPUTS_TOKEN:
            test_sym(TX_HASHOUTPUTS_TOKEN);
            break;
        case TX_LOCKTIME_TOKEN:
            test_sym(TX_LOCKTIME_TOKEN);
            break;
        case TX_HASHTYPE_TOKEN:
            test_sym(TX_HASHTYPE_TOKEN);
            break;
        case TX_PREIMAGE_TOKEN:
            test_sym(TX_PREIMAGE_TOKEN);
            break;

        default: {
            printError(ERROR_TOKEN);
            exit(EXIT_FAILURE);
            break;
        }
    }
}

void BYTES() {
    test_sym(BYTES_TOKEN);
    if (symbols[cursor].token == NOMBRE_LITTERAL_TOKEN) {
        test_sym(NOMBRE_LITTERAL_TOKEN);
    }
}

int main() {
    fp = fopen("../tests/test1.cash", "r"); // for debuging
    if (fp == NULL) {
        perror("Error in opening file");
        return -1;
    }
    analy_lex(fp);
//    sleep(4);
//    char* tempCharArray[MAX_KEYWORDS];
//    fileToArray(tempCharArray,MAX_KEYWORDS);
//    printf("\n\n%s",tempCharArray[0]);
    printf("analyseur lexical termine : success \n");
    PROGRAMME();
    printf("analyseur lexical et semantique : success\n");

    return 0;
}