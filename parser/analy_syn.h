#ifndef SYN_H
#define SYN_H

#include "../lexer/analy_lex.h"

void PROGRAMME();
void DIRECTIVE_PRAGMA();
void VALEUR_PRAGMA();
void CONTRAINTE_VERSION();
void OPERATEUR_VERSION();
void DEFINITION_CONTRAT();
void DEFINITION_FONCTION();
void LISTE_PARAMETRE();
void PARAMETRE();
void BLOC();
void DECLARATION();
void DEFINITION_VARIABLE();
void AFFECTATION();
void TEMPS_DECLARATION();
void requireStatement();
void SI();
void FONCTION();
void LISTE_EXPRESSIONS();
void EXPRESSION();
void DEUXIEME_EXPRESSION_BINAIRE();
void LITTERAL();
void NOMBRE_LITTERAL();
void NOM_TYPE();
void BYTES();
void DATE_LITTERAL();
void WHILE();
void ECRIRE();
void LIRE();
void COMMENT();
void LINE_COMMENT();

void VERSION_LITTERALE_TOKEN();
void TX_VAR_TOKEN();
void BOOLEAN_LITTERAL_TOKEN();
void STRING_LITTERAL_TOKEN();
void UNITE_TOKEN();
void CHAMP_AVANT_IMAGE_TOKEN();

void parser();
#endif