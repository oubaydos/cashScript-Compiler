#include"analy_lex.h"


void lex_get_next_char() {
    curr_char = fgetc(fp);
}

void next_sym() {
    skip_white_spaces();
    switch (curr_char) {
        case '+':
            curr_sym = OPERATEUR_PLUS_TOKEN;
            lex_get_next_char();
            break;
        case '-':
            curr_sym = OPERATEUR_MOINS_TOKEN;
            lex_get_next_char();
            break;
            //case '*': curr_sym=MULT_TOKEN;lex_get_next_char();break;
            //case '/': curr_sym=DIV_TOKEN;lex_get_next_char();break;
        case ';':
            curr_sym = POINT_VIRGULE_TOKEN;
            lex_get_next_char();
            break;
        case ',':
            curr_sym = VIRGULE_TOKEN;
            lex_get_next_char();
            break;

        case ':':
            lex_get_next_char();
            if (curr_char == '=') {
                curr_sym = AFF_TOKEN;
                lex_get_next_char();
                break;
            } else {
                curr_sym = ERROR_TOKEN;
                return;
            }
            break;
        case '<':
            curr_sym = OPERATEUR_INF_TOKEN;
            lex_get_next_char();
            if (curr_char == '=') {
                curr_sym = OPERATEUR_INFEG_TOKEN;
                lex_get_next_char();
            }
            break;
        case '>':
            curr_sym = OPERATEUR_SUP_TOKEN;
            lex_get_next_char();
            if (curr_char == '=') {
                curr_sym = OPERATEUR_SUPEG_TOKEN;
                lex_get_next_char();
            }
            break;
        case '(':
            curr_sym = PARENTHESE_O_TOKEN;
            lex_get_next_char();
            break;
        case ')':
            curr_sym = PARENTHESE_F_TOKEN;
            lex_get_next_char();
            break;
        case '[':
            curr_sym = CROCHET_O_TOKEN;
            lex_get_next_char();
            break;
        case ']':
            curr_sym = CROCHET_F_TOKEN;
            lex_get_next_char();
            break;
            //case '!': curr_sym=OPERATEUR_NON;lex_get_next_char();break;
        case '%':
            curr_sym = OPERATEUR_MODULO_TOKEN;
            lex_get_next_char();
            break;
        case '!':
            curr_sym = OPERATEUR_NON_TOKEN;
            lex_get_next_char();
            if (curr_char == '=') {
                curr_sym = OPERATEUR_DIFFERENT_TOKEN;
                lex_get_next_char();
            }
            break;


        case '*':
            curr_sym = OPERATEUR_FOIS_TOKEN;
            lex_get_next_char();
            if (curr_char == '/') {
                curr_sym = COMMENTAIRE_TOKEN_F;
                lex_get_next_char();
            }
            break;


        case '/':
            curr_sym = OPERATEUR_DIVISER_TOKEN;
            lex_get_next_char();
            if (curr_char == '/') {
                curr_sym = COMMENTAIRE_LIGNE_TOKEN;
                lex_get_next_char();
            }
            if (curr_char == '*') {
                curr_sym = COMMENTAIRE_TOKEN_O;
                lex_get_next_char();
            }
            break;

        case '|':
            curr_sym = OPERATEUR_BINAIRE_OU_TOKEN;
            lex_get_next_char();
            if (curr_char == '|') {
                curr_sym = OPERATEUR_OU_TOKEN;
                lex_get_next_char();
            }
            break;

        case '&':
            curr_sym = OPERATEUR_BINAIRE_ET_TOKEN;
            lex_get_next_char();
            if (curr_char == '&') {
                curr_sym = OPERATEUR_ET_TOKEN;
                lex_get_next_char();
            }
            break;

        case '^':
            curr_sym = OPERATEUR_BINAIRE_XOR_TOKEN;
            lex_get_next_char();
            break;
        case '~':
            curr_sym = OPERATEUR_BINAIRE_NON_TOKEN;
            lex_get_next_char();
            break;


        case EOF:
            curr_sym = EOF_TOKEN;
            break;
        case '"':
            curr_sym = GUILLEMET_TOKEN;
            //curr_sym=GUILLEMET_SIMPLE_TOKEN;
            lex_get_next_char();
            //read_string();
            break;
        case '\'':
            curr_sym = GUILLEMET_SIMPLE_TOKEN;
            //curr_sym=GUILLEMET_SIMPLE_TOKEN;
            lex_get_next_char();
            //read_string();
            break;
        case '{':
            curr_sym = ACCOLADE_O_TOKEN;
            lex_get_next_char();
            break;
        case '}':
            curr_sym = ACCOLADE_F_TOKEN;
            lex_get_next_char();
            break;
//case "'": curr_sym=ACCOLADE_F_TOKEN;lex_get_next_char();break;

        case '_':
            curr_sym = UNDER_TOKEN;
            lex_get_next_char();
            break;






            //case '{':
            //skip_comment();
            //break;
        case '=':
            curr_sym = OPERATEUR_EG_TOKEN;
            lex_get_next_char();
            if (curr_char == '=') {
                curr_sym = OPERATEUR_EGAL_TOKEN;
                lex_get_next_char();
            }
            break;



            //case '.': curr_sym=POINT_TOKEN;lex_get_next_char();break;


        case '.':
            curr_sym = POINT_TOKEN;
            lex_get_next_char();
            //if(isalpha(curr_char)){
            //read_word();break;
            //}
            break;


        default:
            if (isalpha(curr_char)) {
                read_word();
                break;
            } else if (isdigit(curr_char)) {
                read_number();
                break;
            } else {

                curr_sym = ERROR_TOKEN;
                printf("erreur : unknown character : %c", curr_char);
                exit(-1);
            }
    }
}

void print_token(LEX_CODE curr_sym) {
    printf("%s line %d\n", TOKEN_NAMES[curr_sym], current_line);
}

void read_number() {
    int i = 0;


    while (isdigit(curr_char) || isalpha(curr_char)) {
        if (isalpha(curr_char) != 0) { i++; }

        lex_get_next_char();
    }

    if (i == 0) { curr_sym = NOMBRE_LITTERAL_TOKEN; }


    else {
        curr_sym = HEX_LITTERAL_TOKEN;
    }
}

void read_word() {
    char word[100];
    int i = 0;
    while (isalnum(curr_char) || curr_char == '_') {
        word[i] = curr_char;
        i++;
        lex_get_next_char();
    }
    word[i] = '\0';

    strcpy(id, word);
    LEX_CODE code = keyword_code(word);

    if (code == -1) {
        curr_sym = IDENTIFIANT_TOKEN;
        //add_to_id_array(word);
    } else curr_sym = code;
}

void read_string() {
    char quote = curr_char;
    lex_get_next_char();
    while (curr_char != quote && curr_char != EOF) {
        lex_get_next_char();
    }
    if (curr_char == quote) {
        curr_sym = STRING_TOKEN;
    }
    lex_get_next_char();
}

void skip_white_spaces() {
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n' || curr_char == '\r') {
        if (curr_char == '\n') current_line++;
        lex_get_next_char();
    }
}

void skip_comment() {
    lex_get_next_char();
    while (curr_char != '}' && curr_char != EOF) {
        lex_get_next_char();
    }
    if (curr_char == '}') {
        lex_get_next_char();
    }
    next_sym();
}

LEX_CODE keyword_code(char *word) {
    int i;
    for (i = 0; i < number_of_keywords; i++) {
        if (strcmp(word, pascal_keywords[i].keyword) == 0) {
            return pascal_keywords[i].code;
        }
    }
    return -1;
}

void analy_lex(FILE *fp) {


    current_line = 1;
    //ids_arr_cursor = 0;
    last_keyword = -1;
    lex_get_next_char();
    int i = 0;
    int count = 0;

    FILE *f;
    f = fopen("./lexer/ids.txt", "w");
    if (f == NULL) {
        printf("err\n");
        exit(-1);
    }
    while (curr_sym != EOF_TOKEN && curr_sym != ERROR_TOKEN) {
        next_sym();
        LEX_CODE code1;
        LEX_CODE code2;
        LEX_CODE code3;
        LEX_CODE code4;
        code1 = curr_sym;
        if (curr_sym == GUILLEMET_TOKEN) {
            symbols[i] = (SYMBOL) {GUILLEMET_TOKEN, current_line};
            i++;

            next_sym();

            while (curr_sym != GUILLEMET_TOKEN && curr_sym != EOF_TOKEN) {
                next_sym();
            }
            if (curr_sym == GUILLEMET_TOKEN) {
                symbols[i] = (SYMBOL) {STRING_VALEUR_TOKEN, current_line};
                i++;
                symbols[i] = (SYMBOL) {GUILLEMET_TOKEN, current_line};
                i++;
            } else {
                symbols[i] = (SYMBOL) {ERROR_TOKEN, current_line};
                i++;
            }

            next_sym();
        }
        if (curr_sym == GUILLEMET_SIMPLE_TOKEN) {
            symbols[i] = (SYMBOL) {GUILLEMET_SIMPLE_TOKEN, current_line};
            i++;

            next_sym();

            while (curr_sym != GUILLEMET_SIMPLE_TOKEN && curr_sym != EOF_TOKEN) {
                next_sym();
            }
            if (curr_sym == GUILLEMET_SIMPLE_TOKEN) {
                symbols[i] = (SYMBOL) {STRING_VALEUR_TOKEN, current_line};
                i++;
                symbols[i] = (SYMBOL) {GUILLEMET_SIMPLE_TOKEN, current_line};
                i++;
            } else {
                symbols[i] = (SYMBOL) {ERROR_TOKEN, current_line};
                i++;
            }

            next_sym();
        }


        if (curr_sym == TAILLE_TOKEN || curr_sym == SPLIT_TOKEN || curr_sym == INVERSER_TOKEN ||
            curr_sym == IDENTIFIANT_TOKEN) {
            //temp created by oubaydos - may produce errors
            LEX_CODE tempToken = symbols[i - 1].token;
            if (i - 1 >= 0 &&
                (
                        tempToken == CONTRAT_TOKEN || tempToken == TYPE_BOOLEAN_TOKEN
                        || tempToken == TYPE_CLE_PUBLIQUE_TOKEN || tempToken == TYPE_ENTIER_TOKEN
                        || tempToken == TYPE_SIGNATURE_DONNEE_TOKEN || tempToken == TYPE_SIGNATURE_TOKEN
                        || tempToken == TYPE_STRING_TOKEN || tempToken == BYTES_TOKEN || tempToken == FONCTION_TOKEN
                )
                    ){
                LANGUAGE_KEYWORD tempKeyWord;
                tempKeyWord.code = IDENTIFIANT_TOKEN;
                strcpy(tempKeyWord.keyword,id);
                identifiersTable[lastIdentifier++] = tempKeyWord;
            }else{
                LANGUAGE_KEYWORD tempKeyWord;
                tempKeyWord.code = IDENTIFIANT_TOKEN;
                strcpy(tempKeyWord.keyword,id);
                usedIdentifiersTable[lastUsedIdentifier++] = tempKeyWord;
            }
//                printf("--\n%s--\n", TOKEN_NAMES[symbols[i - 1].token]);
            //-

            if (strcmp(id, "") != 0) {
                fprintf(f, id);
                fprintf(f, "\n ");
            }

            next_sym();
            symbols[i] = (SYMBOL) {IDENTIFIANT_TOKEN, current_line};
            i++;
        }

        //COMMENTAIRE_LIGNE_TOKEN
        //if(curr_sym==GUILLEMET_SIMPLE_TOKEN  ){
        //  next_sym();
        //}

        if (curr_sym == COMMENTAIRE_TOKEN_O) {
            next_sym();
            while (curr_sym != COMMENTAIRE_TOKEN_F && curr_sym != EOF_TOKEN) {
                next_sym();
            }
            next_sym();

        }

        if (curr_sym == DATE_TOKEN) {
            next_sym();
            if (curr_sym == PARENTHESE_O_TOKEN) {
                symbols[i] = (SYMBOL) {DATE_TOKEN, current_line};
                i++;
                next_sym();
            } else {
                fprintf(f, id);
                fprintf(f, "\n ");
                symbols[i] = (SYMBOL) {IDENTIFIANT_TOKEN, current_line};
                i++;
                symbols[i] = (SYMBOL) {curr_sym, current_line};
                i++;
                next_sym();

            }


        }

        if (curr_sym == COMMENTAIRE_LIGNE_TOKEN) {
            int i = 0;
            i = current_line;
            while (i == current_line) {
                next_sym();
            }
            if (curr_sym == COMMENTAIRE_LIGNE_TOKEN) {
                i = 0;
                i = current_line;
                while (i == current_line) {
                    next_sym();
                }


            }


        }


        if (curr_sym == POINT_TOKEN) {
            next_sym();
            code2 = curr_sym;
            if (curr_sym == SPLIT_TOKEN) {


                symbols[i] = (SYMBOL) {SPLIT_TOKEN, current_line};
                i++;


            } else if (curr_sym == TAILLE_TOKEN) {


                symbols[i] = (SYMBOL) {TAILLE_TOKEN, current_line};
                i++;


            } else if (curr_sym == INVERSER_TOKEN) {
                next_sym();
                code3 = curr_sym;
                if (curr_sym == PARENTHESE_O_TOKEN) {
                    next_sym();
                    code4 = curr_sym;
                    if (curr_sym == PARENTHESE_F_TOKEN) {
                        symbols[i] = (SYMBOL) {INVERSER_TOKEN, current_line};
                        i++;
                    } else {
                        symbols[i] = (SYMBOL) {POINT_TOKEN, current_line};
                        i++;
                        symbols[i] = (SYMBOL) {IDENTIFIANT_TOKEN, current_line};
                        fprintf(f, id);
                        fprintf(f, "\n ");
                        i++;
                        symbols[i] = (SYMBOL) {code3, current_line};
                        i++;
                        symbols[i] = (SYMBOL) {code4, current_line};
                        i++;
                    }
                } else {

                    //for debuging
                    symbols[i] = (SYMBOL) {POINT_TOKEN, current_line};
                    i++;
                    symbols[i] = (SYMBOL) {IDENTIFIANT_TOKEN, current_line};
                    fprintf(f, id);
                    fprintf(f, "\n ");
                    i++;
                    symbols[i] = (SYMBOL) {code3, current_line};
                    i++;
                    //symbols[i]=(SYMBOL){code4,current_line};
                    //i++;
                }
            } else {
                symbols[i] = (SYMBOL) {POINT_TOKEN, current_line};
                i++;
                symbols[i] = (SYMBOL) {code2, current_line};
                i++;
                //next_sym();
            }
        } else {
            //for debuging
            symbols[i] = (SYMBOL) {curr_sym, current_line};
            i++;
        }
    }

    int j = 0;

    FILE *fptr;
    fptr = fopen("test.txt", "w");
    for (j; j < i; j++) {

        //fwrite(TOKEN_NAMES[symbols[j].token], sizeof(char), 11, fptr);
        //fwrite("\n", sizeof(char), 1, fptr);
        fprintf(fptr, TOKEN_NAMES[symbols[j].token]);
        fprintf(fptr, "\n ");

        //printf("\n%s\n ",TOKEN_NAMES[symbols[j].token]);

    }
    fclose(fptr);

}
