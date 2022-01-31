#include "semantics.h"
void printfSemanticError(char *errorMessage)
{
    printf("Semantic error: %s\n", errorMessage);
    exit(1);
}
void printfDoubleDeclarationError(LANGUAGE_KEYWORD identifier)
{
    printf("double déclaration de %s ", identifier.keyword);
    exit(1);
}
// add to list of identifiers
void addIdentifier(LANGUAGE_KEYWORD identifier)
{
    identifiersTable[lastKeywords++] = identifier;
}

// if an identifier is defined twice exit with an error
// if an identifier is used without being defined exit with an error
bool identifierExists(LANGUAGE_KEYWORD identifier)
{
    for (int i = 0; i < lastIdentifier + 1; i++)
    {
        if (strcmp(identifier.keyword, identifiersTable[i].keyword) == 0)
        {
            return true;
        }
    }
    return false;
}

void asserIdentifierDoesnotExist(LANGUAGE_KEYWORD identifier)
{
    if (!identifierExists(identifier))
        addIdentifier(identifier);
    else
        printfDoubleDeclarationError(identifier);
}
void asserIdentifierExistsBeforeUse(LANGUAGE_KEYWORD identifier)
{
    if (!identifierExists(identifier))
    {
        printf("identifiant utilisé mais n'est pas déclaré %s ", identifier.keyword);
        exit(1);
    }
}
// extract version numbers, and if they are not all positive exit with an error
bool hasAllPositiveNumbers(int number1, int number2, int number3)
{
    return number1 >= 0 && number2 >= 0 && number3 >= 0;
}

bool stringOperationsAreValid(LANGUAGE_KEYWORD firstOperand)
{
    return firstOperand.code == IDENTIFIANT_TOKEN || firstOperand.code == STRING_VALEUR_TOKEN;
}
void assertStringOperationsAreValid(LANGUAGE_KEYWORD firstOperand)
{
    if (!stringOperationsAreValid(firstOperand))
    {
        printf("operation invalide pour %s ", firstOperand.keyword);
        exit(1);
    }
}
void assertNumberIsPositive(LANGUAGE_KEYWORD number)
{
    for (int i = 0; i < number.keyword[i] != '\0', i < 255; i++)
    {
        if (number.keyword[i] == '-')
        {
            printf("operation invalide pour %s ", number.keyword);
            exit(1);
        }
    }
}
