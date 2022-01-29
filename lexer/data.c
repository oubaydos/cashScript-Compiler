#include"data.h"

const char* TOKEN_NAMES[]={
    
     "ID_TOKEN",
    "NUM_TOKEN",
    "ERROR_TOKEN",
    "PV_TOKEN",
    "PT_TOKEN",
    "PLUS_TOKEN",
    "MOINS_TOKEN",
    "MULT_TOKEN",
    "DIV_TOKEN",
    "VIR_TOKEN",
    "AFF_TOKEN",
    "INF_TOKEN",
    "INFEG_TOKEN",
    "EG_TOKEN",
    "SUP_TOKEN",
    "SUPEG_TOKEN",
    "DIFF_TOKEN",
    "PO_TOKEN",
    "PF_TOKEN",
    "FIN_TOKEN",
    "STRING_TOKEN",
    "PROGRAM_TOKEN",
    "CONST_TOKEN",
    "BEGIN_TOKEN",
    "END_TOKEN",
    "IF_TOKEN",
    "THEN_TOKEN",
    "WHILE_TOKEN",
    "DO_TOKEN",
    "READ_TOKEN",
    "WRITE_TOKEN",
    "VAR_TOKEN",
    "REQUIRE",
    "INVERSER",
    "TAILLE",
    "TYPE_ENTIER",
    "TYPE_BOOLEAN",
    "TYPE_STRING",
    "TYPE_CLE_PUBLIQUE",
    "TYPE_SIGNATURE",
    "TYPE_SIGNATURE_DONNEE",
    "BOOLEAN_LITTERAL",
    
    "BYTES",
    "UNITE",
    "PRAGMA",
    "ACCOLADE_F",
    "ACCOLADE_O",
"CASHSCRIPT",
"CONTRAT",
"FONCTION",
"CROCHET_O",
"CROCHET_F",
"OPERATEUR_NON",
"OPERATEUR_MODULO",
"OPERATEUR_DIFFERENT",
"OPERATEUR_BINAIRE_OU",
"OPERATEUR_OU",
"OPERATEUR_BINAIRE_ET",
"OPERATEUR_ET","NOUVEAU",
"OPERATEUR_BINAIRE_NON",
"OPERATEUR_BINAIRE_XOR",
"SPLIT",
"SINON",
"COMMENTAIRE_LIGNE",
"COMMENTAIRE",
"TX","AGE","TIME"

    
    

};
const char* TOKEN_ERRORS[]={//TODO: 
    "ID_ERROR",
    "NUM_ERROR",
    "LEX_ERROR",
    "expected ';' not found",
    "expected '.' not found",
    "PLUS_ERROR",
    "MOINS_ERROR",
    "MULT_ERROR",
    "DIV_ERROR",
    "expected ',' not found",
    "AFF_ERROR",
    "INF_ERROR",
    "INFEG_ERROR",
    "EG_ERROR",
    "SUP_ERROR",
    "SUPEG_ERROR",
    "DIFF_ERROR",
    "PO_ERROR",
    "PF_ERROR",
    "FIN_ERROR",
    "STRING_ERROR",
    "PROGRAM_ERROR",
    "CONST_ERROR",
    "BEGIN_ERROR",
    "END_ERROR",
    "IF_ERROR",
    "THEN_ERROR",
    "WHILE_ERROR",
    "DO_ERROR",
    "READ_ERROR",
    "WRITE_ERROR",
    "VAR_ERROR",

};
const LANGUAGE_KEYWORD pascal_keywords[]={
    {PROGRAM_TOKEN,"program"},
    {CONST_TOKEN,"const"},
    {BEGIN_TOKEN,"begin"},
    {END_TOKEN,"end"},
    {IF_TOKEN,"if"},
    {THEN_TOKEN,"then"},
    {WHILE_TOKEN,"while"},
    {DO_TOKEN,"do"},
    {READ_TOKEN,"read"},
    {WRITE_TOKEN,"write"},
    {VAR_TOKEN,"var"},
    {REQUIRE,"require"},
    {INVERSER,"reverse"},
    {TAILLE,"length"},
    {TYPE_ENTIER,"int"},
    {TYPE_BOOLEAN,"bool"},
    {TYPE_STRING,"string"},
    {TYPE_CLE_PUBLIQUE,"pubkey"},
    {TYPE_SIGNATURE,"sig"},
    {TYPE_SIGNATURE_DONNEE,"datasig"},
    {BOOLEAN_LITTERAL,"true"},
    {BYTES,"bytes"},
    {UNITE,"satoshis"},
    {PRAGMA,"pragma"},

    {CASHSCRIPT,"cashscript"},
    {CONTRAT,"contract"},
    {FONCTION,"function"},
    
    {BOOLEAN_LITTERAL,"false"},
    {NOUVEAU,"new"},
    {SPLIT,"split"},
    {SINON,"else"},
    {TX,"tx"},
    {AGE,"age"},
    {TIME,"time"},





    
    {UNITE,"sats"},
    {UNITE,"finney"},
    {UNITE,"bits"},
    {UNITE,"bitcoin"},
    {UNITE,"seconds"},
    {UNITE,"minutes"},
    {UNITE,"hours"},
    {UNITE,"days"},
    {UNITE,"weeks"},
    {SINON,"else"},
    
    


};
const int number_of_keywords = sizeof(pascal_keywords)/sizeof(LANGUAGE_KEYWORD);