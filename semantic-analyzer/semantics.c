#include "semantics.h"
void printfSemanticError(char *errorMessage)
{
    printf("Semantic error: %s\n", errorMessage);
    exit(1);
}
// if an identifier is defined twice exit with an error
// if an identifier is used without being defined exit with an error
bool identifierExists(LANGUAGE_KEYWORD identifier)
{
    for (int i = 0; i < keywordsTableSize; i++)
    {
        if (strcmp(identifier.keyword, keywordsTable[i].keyword) == 0)
        {
            return true;
        }
    }
    return false;
}
// extract version numbers, and if they are not all positive exit with an error
bool hasAllPositiveNumbers(int number1, int number2, int number3)
{
    return number1 >= 0 && number2 >= 0 && number3 >= 0;
}
// i should get a table containing all keywords and their corresponding token and value :
// for example : int a = 5 ; i should get
// a : TYPE_ENTIER_TOKEN
// and if the expression uses operations in invalid combinations, exit with an error

bool areString(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
{
    return ((firstOperand.code == TYPE_STRING_TOKEN || firstOperand.code == STRING_LITTERAL_TOKEN) && (secondOperand.code == TYPE_STRING_TOKEN || secondOperand.code == STRING_LITTERAL_TOKEN));
}
bool areNumbers(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
{
    return (
        (firstOperand.code == TYPE_ENTIER_TOKEN || firstOperand.code == NOMBRE_LITTERAL_TOKEN) && (secondOperand.code == TYPE_ENTIER_TOKEN || secondOperand.code == NOMBRE_LITTERAL_TOKEN));
}
bool plusOperationIsValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
{
    return areNumbers(firstOperand, secondOperand) || areString(firstOperand, secondOperand);
}
bool otherArithmeticAndLogicalOperationAreValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
{
    return areNumbers(firstOperand, secondOperand);
}
bool splitOperationIsValid(LANGUAGE_KEYWORD firstOperand)
{
    return firstOperand.code == TYPE_STRING_TOKEN || firstOperand.code == STRING_LITTERAL_TOKEN;
}
bool reverseOperationIsValid(LANGUAGE_KEYWORD firstOperand)
{
    return firstOperand.code == TYPE_STRING_TOKEN || firstOperand.code == STRING_LITTERAL_TOKEN;
}
bool lengthOperationIsValid(LANGUAGE_KEYWORD firstOperand)
{
    return firstOperand.code == TYPE_STRING_TOKEN || firstOperand.code == STRING_LITTERAL_TOKEN;
}
