#ifndef SEM_H
#define SEM_H
#include "../parser/analy_syn.h"
#define MAX_KEYWORDS 255
// this should be given by the lexer
// it should contain all the used token with their corresponding value



// functions
bool identifierExists(LANGUAGE_KEYWORD identifier);
bool stringOperationsAreValid(LANGUAGE_KEYWORD firstOperand , int line);
void printfDoubleDeclarationError(LANGUAGE_KEYWORD identifier);
#endif