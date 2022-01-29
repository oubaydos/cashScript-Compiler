#include "analy_syn.h"

int cursor = 0;

void printError(LEX_CODE code){
    printf("Error in line %d: %s\n",symbols[cursor-1].line,TOKEN_ERRORS[code]);
}

void test_sym(LEX_CODE code){
    if(symbols[cursor].token==code){
        cursor++;
    }else {
        printError(code);
        exit(EXIT_FAILURE);
    }
}

void PROGRAMME(){
    while (symbols[cursor].token==PRAGMA)
    {
        DIRECTIVE_PRAGMA();
    }
    DEFINITION_CONTRAT();
    test_sym(EOF_TOKEN);
}

void DIRECTIVE_PRAGMA(){
    test_sym(PRAGMA);
    test_sym(CASHSCRIPT);
    VALEUR_PRAGMA();
    test_sym(PV_TOKEN);
}

void VALEUR_PRAGMA(){
    CONTRAINTE_VERSION();
    if(symbols[cursor].token==VERSION_LITTERALE_TOKEN || symbols[cursor].token==OPERATEUR_BINAIRE_XOR 
    || symbols[cursor].token==OPERATEUR_BINAIRE_NON || symbols[cursor].token==SUPEG_TOKEN 
    || symbols[cursor].token==SUP_TOKEN || symbols[cursor].token==INF_TOKEN 
    || symbols[cursor].token==INFEG_TOKEN || symbols[cursor].token==EG_TOKEN){
        CONTRAINTE_VERSION();
    }
    else if(symbols[cursor].token!= PV_TOKEN){
        printError(PV_TOKEN);
        printf(EXIT_FAILURE);
    }
}

void CONTRAINTE_VERSION(){
    if(symbols[cursor].token==OPERATEUR_BINAIRE_XOR 
    || symbols[cursor].token==OPERATEUR_BINAIRE_NON || symbols[cursor].token==SUPEG_TOKEN 
    || symbols[cursor].token==SUP_TOKEN || symbols[cursor].token==INF_TOKEN 
    || symbols[cursor].token==INFEG_TOKEN || symbols[cursor].token==EG_TOKEN){
        OPERATEUR_VERSION();
    }
    else if(symbols[cursor].token!=VERSION_LITTERALE_TOKEN){
        printError(VERSION_LITTERALE_TOKEN);
        printf(EXIT_FAILURE);
    }
}

void OPERATEUR_VERSION(){
    switch(symbols[cursor].token){
        case OPERATEUR_BINAIRE_XOR: test_sym(OPERATEUR_BINAIRE_XOR);break;
        case OPERATEUR_BINAIRE_NON: test_sym(OPERATEUR_BINAIRE_NON);break;
        case SUPEG_TOKEN: test_sym(SUPEG_TOKEN);break;
        case INF_TOKEN : test_sym(INF_TOKEN);break;
        case INFEG_TOKEN: test_sym(INFEG_TOKEN);break;
        case EG_TOKEN: test_sym(EG_TOKEN);break;
        default: break;
    }
}

void DEFINITION_CONTRAT(){
    test_sym(CONTRAT);
    test_sym(ID_TOKEN);
    LISTE_PARAMETRE();
    test_sym(ACCOLADE_O);
    while (symbols[cursor].token== FONCTION)
    {
       DEFINITION_FONCTION();
    }
    test_sym(ACCOLADE_F);
}

void DEFINITION_FONCTION(){
    test_sym(FONCTION);
    test_sym(ID_TOKEN);
    LISTE_PARAMETRE();
    test_sym(ACCOLADE_O);
    while (symbols[cursor].token==TYPE_ENTIER 
    || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
    || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
    || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN)
    {
       DECLARATION();
    }
    test_sym(ACCOLADE_F);
}

void LISTE_PARAMETRE(){
    test_sym(PARENTHESE_O_TOKEN);
    if(symbols[cursor].token==TYPE_ENTIER 
    || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
    || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
    || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN){
        PARAMETRE();
        while (symbols[cursor].token==VIR_TOKEN &&(symbols[cursor+1].token==TYPE_ENTIER 
            || symbols[cursor+1].token==TYPE_BOOLEAN || symbols[cursor+1].token==TYPE_STRING 
            || symbols[cursor+1].token==TYPE_CLE_PUBLIQUE || symbols[cursor+1].token==TYPE_SIGNATURE 
            || symbols[cursor+1].token==TYPE_SIGNATURE_DONNEE || symbols[cursor+1].token==BYTES_TOKEN))
        {
            test_sym(VIR_TOKEN);
            PARAMETRE();
        }
        if(symbols[cursor].token==VIR_TOKEN) test_sym(VIR_TOKEN);

    }
    test_sym(PARENTHESE_F_TOKEN);
}

void PARAMETRE(){
    NOM_TYPE();
    test_sym(ID_TOKEN);
}

void BLOC(){
    if(symbols[cursor].token==ACCOLADE_O){
        test_sym(ACCOLADE_O);
        while (symbols[cursor].token==TYPE_ENTIER 
    || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
    || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
    || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN
    || symbols[cursor].token==ID_TOKEN || symbols[cursor].token==REQUIRE_TIME_TOKEN 
    || symbols[cursor].token==REQUIRE || symbols[cursor].token==IF_TOKEN || symbols[cursor].token==WHILE_TOKEN
    || symbols[cursor].token==WRITE_TOKEN || symbols[cursor].token==READ_TOKEN
    ){
            DECLARATION();
    }
    test_sym(ACCOLADE_F);
    }
    else if(symbols[cursor].token==TYPE_ENTIER 
    || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
    || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
    || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN
    || symbols[cursor].token==ID_TOKEN || symbols[cursor].token==REQUIRE_TIME_TOKEN 
    || symbols[cursor].token==REQUIRE || symbols[cursor].token==IF_TOKEN || symbols[cursor].token==WHILE_TOKEN
    || symbols[cursor].token==WRITE_TOKEN || symbols[cursor].token==READ_TOKEN){
        DECLARATION();
    }
    else {
        printError(ERROR_TOKEN);
        printf(EXIT_FAILURE);
    }
        
}


void DECLARATION(){
    if(symbols[cursor].token==TYPE_ENTIER 
    || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
    || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
    || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN){
        DEFINITION_VARIABLE();
    }
    else if(symbols[cursor].token==ID_TOKEN){
        AFFECTATION();
    }
    else if(symbols[cursor].token==REQUIRE_TIME_TOKEN){
        TEMPS_DECLARATION();
    }
    else if(symbols[cursor].token==REQUIRE){
        requireStatement();
    }
    else if(symbols[cursor].token==IF_TOKEN){
        SI();
    }
    else if(symbols[cursor].token==WHILE_TOKEN){
        WHILE();
    }
    else if(symbols[cursor].token==READ_TOKEN){
        ECRIRE();
    }
    else if(symbols[cursor].token==WRITE_TOKEN){
        LIRE();
    }
    else {
        printError(ERROR_TOKEN);
        printf(EXIT_FAILURE);
    }
}

void DEFINITION_VARIABLE(){
    NOM_TYPE();
    test_sym(ID_TOKEN);
    test_sym(EG_TOKEN);
    EXPRESSION();
    test_sym(PV_TOKEN);
}

void AFFECTATION(){
    test_sym(ID_TOKEN);
    test_sym(EG_TOKEN);
    EXPRESSION();
    test_sym(PV_TOKEN);
}

void TEMPS_DECLARATION(){
    test_sym(REQUIRE_TIME_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    test_sym(TX_VAR_TOKEN);
    test_sym(SUPEG_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(PV_TOKEN);
}

void requireStatement(){
    test_sym(REQUIRE);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(PV_TOKEN);
}

void SI(){
    test_sym(IF_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    BLOC();
    while (symbols[cursor].token==SINON){
        test_sym(SINON);
        BLOC();
    }
}

void FONCTION(){
    test_sym(ID_TOKEN);
}

void LISTE_EXPRESSIONS(){
    test_sym(PARENTHESE_O_TOKEN);
    if(symbols[cursor].token==TYPE_ENTIER
    || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
    || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
    || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN
    || symbols[cursor].token==PARENTHESE_O_TOKEN || symbols[cursor].token==ID_TOKEN
    || symbols[cursor].token==NOUVEAU || symbols[cursor].token==OPERATEUR_NON
    || symbols[cursor].token==MOINS_TOKEN || symbols[cursor].token==CROCHET_O
    || symbols[cursor].token==MOINS_TOKEN || symbols[cursor].token==CHAMP_AVANT_IMAGE_TOKEN
    || symbols[cursor].token==BOOLEAN_LITTERAL_TOKEN || symbols[cursor].token==NOMBRE_LITTERAL_TOKEN  
    || symbols[cursor].token==STRING_LITTERAL_TOKEN || symbols[cursor].token==DATE_TOKEN
    || symbols[cursor].token==HEX_LITTERAL_TOKEN
    ){
        EXPRESSION();
        while (symbols[cursor].token==VIR_TOKEN &&(symbols[cursor+1].token==TYPE_ENTIER 
    || symbols[cursor+1].token==TYPE_BOOLEAN || symbols[cursor+1].token==TYPE_STRING 
    || symbols[cursor+1].token==TYPE_CLE_PUBLIQUE || symbols[cursor+1].token==TYPE_SIGNATURE 
    || symbols[cursor+1].token==TYPE_SIGNATURE_DONNEE || symbols[cursor+1].token==BYTES_TOKEN
    || symbols[cursor+1].token==PARENTHESE_O_TOKEN || symbols[cursor+1].token==ID_TOKEN
    || symbols[cursor+1].token==NOUVEAU_TOKEN || symbols[cursor+1].token==OPERATEUR_NON
    || symbols[cursor+1].token==MOINS_TOKEN || symbols[cursor+1].token==CROCHET_O_TOKEN
    || symbols[cursor+1].token==OPERATEUR_MOINS_TOKEN || symbols[cursor+1].token==CHAMP_AVANT_IMAGE_TOKEN
    || symbols[cursor+1].token==BOOLEAN_LITTERAL_TOKEN || symbols[cursor+1].token==NOMBRE_LITTERAL_TOKEN  
    || symbols[cursor+1].token==STRING_LITTERAL_TOKEN || symbols[cursor+1].token==DATE_TOKEN
    || symbols[cursor+1].token==HEX_LITTERAL_TOKEN))
        {
            test_sym(VIR_TOKEN);
            EXPRESSION();
        }
        if(symbols[cursor].token==VIR_TOKEN) {test_sym(VIR_TOKEN);}
        test_sym(PARENTHESE_F_TOKEN);
    }
}

void EXPRESSION(){
    if(symbols[cursor].token==PARENTHESE_O_TOKEN){
        test_sym(PARENTHESE_O_TOKEN);
        EXPRESSION();
        test_sym(PARENTHESE_F_TOKEN);
    }
    else if(symbols[cursor].token==TYPE_ENTIER 
    || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
    || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
    || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN){
        NOM_TYPE();
        test_sym(PARENTHESE_O_TOKEN);
        EXPRESSION();
        if(symbols[cursor].token==VIR_TOKEN &&(symbols[cursor+1].token==PARENTHESE_O_TOKEN
        ||symbols[cursor+1].token==TYPE_ENTIER 
        || symbols[cursor+1].token==TYPE_BOOLEAN || symbols[cursor+1].token==TYPE_STRING 
        || symbols[cursor+1].token==TYPE_CLE_PUBLIQUE || symbols[cursor+1].token==TYPE_SIGNATURE 
        || symbols[cursor+1].token==TYPE_SIGNATURE_DONNEE || symbols[cursor+1].token==BYTES_TOKEN
        || symbols[cursor+1].token==NOUVEAU_TOKEN || symbols[cursor+1].token==ID_TOKEN
        || symbols[cursor+1].token==BOOLEAN_LITTERAL_TOKEN || symbols[cursor+1].token==NOMBRE_LITTERAL_TOKEN
        || symbols[cursor+1].token==STRING_LITTERAL_TOKEN || symbols[cursor+1].token==DATE_TOKEN
        || symbols[cursor+1].token==HEX_LITTERAL_TOKEN || symbols[cursor+1].token==OPERATEUR_NON
        || symbols[cursor+1].token==HEX_LITTERAL_TOKEN || symbols[cursor+1].token==MOINS_TOKEN
        || symbols[cursor+1].token==CROCHET_O_TOKEN || symbols[cursor+1].token==CHAMP_AVANT_IMAGE_TOKEN
        )){
            test_sym(VIRGULE_TOKEN);
            EXPRESSION();
        }
        else if(symbols[cursor].token==VIR_TOKEN) test_sym(symbols[cursor].token==VIR_TOKEN);
        test_sym(PARENTHESE_F_TOKEN);
    }
    else if(symbols[cursor].token==NOUVEAU_TOKEN){
        test_sym(NOUVEAU_TOKEN);
        test_sym(ID_TOKEN);
        LISTE_EXPRESSIONS();
    }
    else if(symbols[cursor].token==ID_TOKEN){
        switch (symbols[cursor].token)
        {
        case PARENTHESE_O_TOKEN: LISTE_EXPRESSIONS(); break;
        case INVERSER: test_sym(INVERSER); break;
        case TAILLE: test_sym(TAILLE); break;
        case CROCHET_O_TOKEN: {
                                test_sym(CROCHET_O_TOKEN);
                                test_sym(NOMBRE_LITTERAL_TOKEN);
                                test_sym(CROCHET_F_TOKEN);
                                }; break;
        case SPLIT_TOKEN: {
                            test_sym(SPLIT_TOKEN);
                            test_sym(PARENTHESE_O_TOKEN);
                            EXPRESSION();
                            test_sym(PARENTHESE_F_TOKEN);
                        }; break;
        case OPERATEUR_FOIS_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_DIVISER_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_MODULO: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case PLUS_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case MOINS_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case INF_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case INFEG_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case SUP_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case SUPEG_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case EG_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_DIFFERENT: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_BINAIRE_ET: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_BINAIRE_XOR: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_BINAIRE_OU: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_ET: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_OU: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case PARENTHESE_O_TOKEN:  break;
        default:{printError(ERROR_TOKEN);
                printf(EXIT_FAILURE);
        } break;
        }
    }
    else if(symbols[cursor].token==BOOLEAN_LITTERAL || symbols[cursor].token==NOMBRE_LITTERAL_TOKEN
    || symbols[cursor].token==STRING_LITTERAL_TOKEN || symbols[cursor].token=="'date('"
    || symbols[cursor].token==HEX_LITTERAL_TOKEN
    ){
        LITTERAL();
        switch (symbols[cursor].token)
        {
        case INVERSER: test_sym(INVERSER_TOKEN); break;
        case TAILLE: test_sym(TAILLE_TOKEN); break;
        case CROCHET_O_TOKEN: {test_sym(CROCHET_O_TOKEN); test_sym(NOMBRE_LITTERAL_TOKEN); test_sym(CROCHET_F_TOKEN); } break;
        case SPLIT: {test_sym(SPLIT);
                            test_sym(PARENTHESE_O_TOKEN);
                            EXPRESSION();
                            test_sym(PARENTHESE_F_TOKEN);
        } break;
        case INVERSER: test_sym(INVERSER_TOKEN); break;
        case OPERATEUR_FOIS_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_DIVISER_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_MODULO: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case PLUS_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case MOINS_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case INF_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case INFEG_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case SUP_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case SUPEG_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case EG_TOKEN: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_DIFFERENT: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_BINAIRE_ET: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_BINAIRE_XOR: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_BINAIRE_OU: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_ET: DEUXIEME_EXPRESSION_BINAIRE(); break;
        case OPERATEUR_OU: DEUXIEME_EXPRESSION_BINAIRE(); break;
        }
    }
    else if(symbols[cursor].token== OPERATEUR_NON){
        test_sym(OPERATEUR_NON);
        EXPRESSION();
    }
    else if(symbols[cursor].token== MOINS_TOKEN){
        test_sym(MOINS_TOKEN);
        EXPRESSION();
    }
    else if(symbols[cursor].token==CROCHET_O_TOKEN){
        test_sym(CROCHET_O_TOKEN);
            if(symbols[cursor].token==TYPE_ENTIER 
            || symbols[cursor].token==TYPE_BOOLEAN || symbols[cursor].token==TYPE_STRING 
            || symbols[cursor].token==TYPE_CLE_PUBLIQUE || symbols[cursor].token==TYPE_SIGNATURE 
            || symbols[cursor].token==TYPE_SIGNATURE_DONNEE || symbols[cursor].token==BYTES_TOKEN
            || symbols[cursor].token==PARENTHESE_O_TOKEN || symbols[cursor].token==ID_TOKEN
            || symbols[cursor].token==NOUVEAU_TOKEN || symbols[cursor].token==OPERATEUR_NON
            || symbols[cursor].token==MOINS_TOKEN || symbols[cursor].token==CROCHET_O_TOKEN
            || symbols[cursor].token==MOINS_TOKEN || symbols[cursor].token==CHAMP_AVANT_IMAGE_TOKEN
            || symbols[cursor].token==BOOLEAN_LITTERAL || symbols[cursor].token==NOMBRE_LITTERAL_TOKEN  
            || symbols[cursor].token==STRING_LITTERAL_TOKEN || symbols[cursor].token==DATE_TOKEN
            || symbols[cursor].token==HEX_LITTERAL_TOKEN
            ){
                EXPRESSION();
                while (symbols[cursor].token==VIR_TOKEN &&(symbols[cursor+1].token==TYPE_ENTIER 
            || symbols[cursor+1].token==TYPE_BOOLEAN || symbols[cursor+1].token==TYPE_STRING 
            || symbols[cursor+1].token==TYPE_CLE_PUBLIQUE || symbols[cursor+1].token==TYPE_SIGNATURE 
            || symbols[cursor+1].token==TYPE_SIGNATURE_DONNEE || symbols[cursor+1].token==BYTES_TOKEN
            || symbols[cursor+1].token==PARENTHESE_O_TOKEN || symbols[cursor+1].token==ID_TOKEN
            || symbols[cursor+1].token==NOUVEAU_TOKEN || symbols[cursor+1].token==OPERATEUR_NON
            || symbols[cursor+1].token==MOINS_TOKEN || symbols[cursor+1].token==CROCHET_O_TOKEN
            || symbols[cursor+1].token==MOINS_TOKEN || symbols[cursor+1].token==CHAMP_AVANT_IMAGE_TOKEN
            || symbols[cursor+1].token==BOOLEAN_LITTERAL || symbols[cursor+1].token==NOMBRE_LITTERAL_TOKEN  
            || symbols[cursor+1].token==STRING_LITTERAL_TOKEN || symbols[cursor+1].token==DATE_TOKEN
            || symbols[cursor+1].token==HEX_LITTERAL_TOKEN))
                {
                    test_sym(VIR_TOKEN);
                    EXPRESSION();
                }
                if(symbols[cursor].token==VIR_TOKEN) {test_sym(VIR_TOKEN);}
                test_sym(CROCHET_F_TOKEN);
            }
            }
            else if(symbols[cursor].token==CHAMP_AVANT_IMAGE_TOKEN){
                test_sym(CHAMP_AVANT_IMAGE_TOKEN);
            }
            else {
                printError(ERROR_TOKEN);
                printf(EXIT_FAILURE);
            }
}

void DEUXIEME_EXPRESSION_BINAIRE(){
    switch (symbols[cursor].token)
    {
    case OPERATEUR_FOIS_TOKEN: test_sym(OPERATEUR_FOIS_TOKEN); break;
    case OPERATEUR_DIVISER_TOKEN: test_sym(OPERATEUR_DIVISER_TOKEN); break;
    case OPERATEUR_MODULO: test_sym(OPERATEUR_MODULO_TOKEN); break;
    case PLUS_TOKEN: test_sym(OPERATEUR_PLUS_TOKEN); break;
    case MOINS_TOKEN: test_sym(OPERATEUR_MOINS_TOKEN); break;
    case INF_TOKEN: test_sym(OPERATEUR_INF_TOKEN); break;
    case INFEG_TOKEN: test_sym(OPERATEUR_MODULO_TOKEN); break;
    case SUP_TOKEN: test_sym(OPERATEUR_SUP_TOKEN); break;
    case SUPEG_TOKEN: test_sym(OPERATEUR_SUPEG_TOKEN); break;
    case EG_TOKEN: test_sym(OPERATEUR_EGAL_TOKEN); break;
    case DIFF_TOKEN: test_sym(OPERATEUR_DIFFERENT_TOKEN); break;
    case OPERATEUR_BINAIRE_ET: test_sym(OPERATEUR_BINAIRE_ET_TOKEN); break;
    case OPERATEUR_BINAIRE_XOR: test_sym(OPERATEUR_BINAIRE_XOR_TOKEN); break;
    case OPERATEUR_BINAIRE_OU: test_sym(OPERATEUR_BINAIRE_OU_TOKEN); break;
    case OPERATEUR_ET: test_sym(OPERATEUR_ET_TOKEN); break;
    case OPERATEUR_OU: test_sym(OPERATEUR_OU_TOKEN); break;
    
    default:{
        printError(ERROR_TOKEN);
        printf(EXIT_FAILURE);
        break;
    }
    }
    if(symbols[cursor].token==ID_TOKEN){
        test_sym(ID_TOKEN);
    }
    else if(symbols[cursor].token==BOOLEAN_LITTERAL || symbols[cursor].token==NOMBRE_LITTERAL_TOKEN
    || symbols[cursor].token==STRING_LITTERAL_TOKEN || symbols[cursor].token==DATE_TOKEN
    || symbols[cursor].token==HEX_LITTERAL_TOKEN
    ){
        LITTERAL();
    }
    else {
        printError(ERROR_TOKEN);
        printf(EXIT_FAILURE);
    }
}

void LITTERAL(){
    switch (symbols[cursor].token)
    {
    case BOOLEAN_LITTERAL : test_sym(BOOLEAN_LITTERAL_TOKEN); break;
    case NOMBRE_LITTERAL_TOKEN : NOMBRE_LITTERAL(); break;
    case STRING_LITTERAL_TOKEN : test_sym(STRING_LITTERAL_TOKEN); break;
    case DATE_TOKEN : DATE_LITTERAL(); break;
    case HEX_LITTERAL_TOKEN : test_sym(HEX_LITTERAL_TOKEN); break;
    default:{ printError(ERROR_TOKEN);
                printf(EXIT_FAILURE);
     } break;
    }
}

void NOMBRE_LITTERAL(){
    test_sym(NOMBRE_LITTERAL_TOKEN);
    if(symbols[cursor].token == UNITE){
        test_sym(UNITE);
    }
}

void NOM_TYPE(){
    switch (symbols[cursor].token)
    {
    case TYPE_ENTIER: test_sym(TYPE_ENTIER); break;
    case TYPE_BOOLEAN: test_sym(TYPE_BOOLEAN); break;
    case TYPE_STRING: test_sym(TYPE_STRING); break;
    case TYPE_CLE_PUBLIQUE: test_sym(TYPE_CLE_PUBLIQUE); break;
    case TYPE_SIGNATURE: test_sym(TYPE_SIGNATURE); break;
    case TYPE_SIGNATURE_DONNEE: test_sym(TYPE_SIGNATURE_DONNEE); break;
    case BYTES_TOKEN: BYTES(); break;

    default:{ printError(ERROR_TOKEN);
            printf(EXIT_FAILURE);
            break;
    }
    }
}

void DATE_LITTERAL(){
    test_sym(DATE_TOKEN);
    test_sym(STRING_LITTERAL_TOKEN);
    test_sym(PARENTHESE_F_TOKEN);

}

void WHILE(){
    test_sym(WHILE_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    BLOC();
}

void ECRIRE(){
    test_sym(WRITE_TOKEN);
    test_sym(PARENTHESE_O_TOKEN);
    EXPRESSION();
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(PV_TOKEN);

}

void LIRE(){
    test_sym(READ_TOKEN);
    test_sym(ID_TOKEN);
    test_sym(PARENTHESE_F_TOKEN);
    test_sym(PV_TOKEN);
}