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
// i should get a table containing all keywords and their corresponding token and value :
// for example : int a = 5 ; i should get
// a : TYPE_ENTIER_TOKEN
// and if the expression uses operations in invalid combinations, exit with an error

// bool areString(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
// {
//     return ((firstOperand.code == TYPE_STRING_TOKEN || firstOperand.code == STRING_LITTERAL_TOKEN) && (secondOperand.code == TYPE_STRING_TOKEN || secondOperand.code == STRING_LITTERAL_TOKEN));
// }
// bool areNumbers(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
// {
//     return (
//         (firstOperand.code == TYPE_ENTIER_TOKEN || firstOperand.code == NOMBRE_LITTERAL_TOKEN) && (secondOperand.code == TYPE_ENTIER_TOKEN || secondOperand.code == NOMBRE_LITTERAL_TOKEN));
// }
// bool plusOperationIsValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
// {
//     return areNumbers(firstOperand, secondOperand) || areString(firstOperand, secondOperand);
// }
// void assertPlusOperationIsValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
// {
//     if (!plusOperationIsValid(firstOperand, secondOperand))
//     {
//         printf("operation + invalide pour les valeurs %s et %s ", firstOperand.keyword, secondOperand.keyword);
//         exit(1);
//     }
// }
// bool otherArithmeticAndLogicalOperationAreValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
// {
//     return areNumbers(firstOperand, secondOperand);
// }
// void assertOtherArithmeticAndLogicalOperationAreValid(LANGUAGE_KEYWORD firstOperand, LANGUAGE_KEYWORD secondOperand)
// {
//     if (!otherArithmeticAndLogicalOperationAreValid(firstOperand, secondOperand))
//     {
//         printf("operation invalide pour les valeurs %s et %s ", firstOperand.keyword, secondOperand.keyword);
//         exit(1);
//     }
// }
// reverse length split
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
//utils
//char *remove_white_spaces(char *str)
//{
//    int i = 0, j = 0;
//    while (str[i])
//    {
//        if (str[i] != ' ')
//        str[j++] = str[i];
//        i++;
//    }
//    str[j] = '\0';
//    return str;
//}
//void fileToArray(char* strings[], size_t size){
//    FILE *f = fopen("../lexer/ids.txt","r");
//    if (f == NULL){
//        printf("error opening the file ids.txt");
//        exit(EXIT_FAILURE);
//    }
//    int i = 0;
//    char line[255], *temp;
//    while (fgets(line, sizeof(line), f) || i>= size) {
//        /* note that fgets don't strip the terminating \n, checking its
//           presence would allow to handle lines longer that sizeof(line) */
//        strings[i++] = remove_white_spaces(line);
//        strings[i-1] = malloc(255*sizeof(char));
//        printf("%s", strings[i-1]);
//    }
//
//}