#include <stdbool.h>
#include "../parser/analy_syn.h"

LANGUAGE_KEYWORD *keywordsTable;
int keywordsTableSize;

bool identifierExists(LANGUAGE_KEYWORD identifier);
bool hasAllPositiveNumbers(int number1, int number2, int number3);
bool plusOperationIsValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand);
bool otherArithmeticAndLogicalOperationAreValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand);
bool splitOperationIsValid(LANGUAGE_KEYWORD firstOperand);
bool reverseOperationIsValid(LANGUAGE_KEYWORD firstOperand);
bool lengthOperationIsValid(LANGUAGE_KEYWORD firstOperand);

void printfSemanticError(char *errorMessage);