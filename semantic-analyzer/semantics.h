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
void fileToArray(char* strings[], size_t size);
// functions
void addIdentifier(LANGUAGE_KEYWORD identifier);
bool identifierExists(LANGUAGE_KEYWORD identifier);
void asserIdentifierDoesnotExist(LANGUAGE_KEYWORD identifier);
void asserIdentifierExistsBeforeUse(LANGUAGE_KEYWORD identifier);

void assertNumberIsPositive(LANGUAGE_KEYWORD number);
// bool hasAllPositiveNumbers(int number1, int number2, int number3);
// bool plusOperationIsValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand);
// void assertPlusOperationIsValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand);

// bool otherArithmeticAndLogicalOperationAreValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand);
// void assertOtherArithmeticAndLogicalOperationAreValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand);

bool stringOperationsAreValid(LANGUAGE_KEYWORD firstOperand);
void assertStringOperationsAreValid(LANGUAGE_KEYWORD firstOperand);

// bool reverseOperationIsValid(LANGUAGE_KEYWORD firstOperand);
// bool lengthOperationIsValid(LANGUAGE_KEYWORD firstOperand);

void printfSemanticError(char *errorMessage);
void printfDoubleDeclarationError(LANGUAGE_KEYWORD identifier);
#endif