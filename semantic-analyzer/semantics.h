#ifndef SEM_H
#define SEM_H
#include "../parser/analy_syn.h"
#define MAX_KEYWORDS 255
// this should be given by the lexer
// it should contain all the used token with their corresponding value
LANGUAGE_KEYWORD keywordsTable[MAX_KEYWORDS];
int lastKeywords = 0;

LANGUAGE_KEYWORD identifiersTable[MAX_KEYWORDS];
int lastIdentifier = 0;
//utils
// functions
void addIdentifier(LANGUAGE_KEYWORD identifier);
bool identifierExists(LANGUAGE_KEYWORD identifier);
bool stringOperationsAreValid(LANGUAGE_KEYWORD firstOperand);
void printfDoubleDeclarationError(LANGUAGE_KEYWORD identifier);
#endif