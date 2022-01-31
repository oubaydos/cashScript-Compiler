#include "semantics.h"
void printfSemanticError(char *errorMessage)
{
    printf("Semantic error: %s\n", errorMessage);
    exit(1);
}
void printfDoubleDeclarationError(LANGUAGE_KEYWORD identifier,int line)
{
    printf("double déclaration de %s, \t ligne : %d", identifier.keyword,line);
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

void assertIdentifierDoesnotExist(LANGUAGE_KEYWORD identifier,int line)
{
    if (!identifierExists(identifier))
        addIdentifier(identifier);
    else
        printfDoubleDeclarationError(identifier,line);
}
void assertIdentifierExistsBeforeUse(LANGUAGE_KEYWORD identifier, int line)
{
    if (!identifierExists(identifier))
    {
        printf("identifiant utilisé mais n'est pas déclaré %s \t ligne : %d ", identifier.keyword,line);
        exit(1);
    }
}
bool stringOperationsAreValid(LANGUAGE_KEYWORD firstOperand)
{
    return firstOperand.code == IDENTIFIANT_TOKEN || firstOperand.code == STRING_VALEUR_TOKEN;
}
void assertStringOperationsAreValid(LANGUAGE_KEYWORD firstOperand, int line)
{
    if (!stringOperationsAreValid(firstOperand))
    {
        printf("operation invalide pour %s \t ligne : ", firstOperand.keyword,line);
        exit(1);
    }
}
void assertNumberIsPositive(LANGUAGE_KEYWORD number, int line)
{
    for (int i = 0; i < number.keyword[i] != '\0' && i < 254; i++)
    {
        if (number.keyword[i] == '-')
        {
            printf("operation invalide pour %s : le nombre dans la version doit etre positif \t ligne : ", number.keyword,line);
            exit(1);
        }
    }
}
