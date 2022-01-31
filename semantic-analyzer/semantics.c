#include "semantics.h"
#include "../parser/analy_syn.c"
void printfSemanticError(char *errorMessage)
{
    printf("Semantic error: %s\n", errorMessage);
    exit(1);
}
void printfDoubleDeclarationError(LANGUAGE_KEYWORD identifier)
{
    printf("double declaration de %s", identifier.keyword);
    exit(1);
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

void assertIdentifierDoesnotExist(LANGUAGE_KEYWORD identifier)
{
    if (identifierExists(identifier))
        printfDoubleDeclarationError(identifier);

}
void assertIdentifierExistsBeforeUse(LANGUAGE_KEYWORD identifier)
{
    if (!identifierExists(identifier))
    {
        printf("identifiant utilise mais n'est pas declare %s ", identifier.keyword);
        exit(1);
    }
}
bool stringOperationsAreValid(LANGUAGE_KEYWORD firstOperand, int line)
{
    return firstOperand.code == IDENTIFIANT_TOKEN || firstOperand.code == GUILLEMET_TOKEN || firstOperand.code == GUILLEMET_SIMPLE_TOKEN;
}
void assertStringOperationsAreValid(LANGUAGE_KEYWORD firstOperand, int line)
{
    if (!stringOperationsAreValid(firstOperand, line))
    {
        printf("operation invalide pour %s dans la ligne : %d", TOKEN_NAMES[firstOperand.code],line);
        exit(1);
    }
}
void analy_sem(){
    for (int counter = 0 ; counter < lastUsedIdentifier ; counter++){
        assertIdentifierExistsBeforeUse(usedIdentifiersTable[counter]);
    }
    LANGUAGE_KEYWORD tempLanguageKeyword;
    for (int counter = 0 ; counter < cursor ; counter++){
        if (symbols[counter].token == SPLIT_TOKEN || symbols[counter].token == INVERSER_TOKEN || symbols[counter].token == TAILLE_TOKEN){
            tempLanguageKeyword.code = symbols[counter-1].token;
            strcpy(tempLanguageKeyword.keyword,"");
            assertStringOperationsAreValid(tempLanguageKeyword, symbols[cursor - 1].line);
        }
    }
}
int main() {
    fp = fopen("../tests/test.cash", "r"); // for debuging
    if (fp == NULL) {
        perror("Error in opening file");
        return -1;
    }
    analy_lex(fp);
    printf("analyseur lexical termine : success \n");
    analy_syn();
    printf("analyseur lexical : success\n");
    analy_sem();
    printf("analyseur semantique : success\n");
    return 0;
}
