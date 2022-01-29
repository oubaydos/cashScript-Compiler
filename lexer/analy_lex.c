#include"analy_lex.h"


void lex_get_next_char(){
    curr_char = fgetc(fp);
}

void next_sym(){
    skip_white_spaces();
    switch(curr_char){
        case '+': curr_sym=PLUS_TOKEN;lex_get_next_char();break;
        case '-': curr_sym=MOINS_TOKEN;lex_get_next_char();break;
        //case '*': curr_sym=MULT_TOKEN;lex_get_next_char();break;
        //case '/': curr_sym=DIV_TOKEN;lex_get_next_char();break;
        case ';': curr_sym=PV_TOKEN;lex_get_next_char();break;
        case ',': curr_sym=VIR_TOKEN;lex_get_next_char();break;
       
        case ':': 
            lex_get_next_char();
            if(curr_char=='='){
                curr_sym=AFF_TOKEN;lex_get_next_char();break;
            }else{
                curr_sym=ERROR_TOKEN;return;
            }
            break;
        case '<': 
            curr_sym=INF_TOKEN;
            lex_get_next_char();
            if(curr_char=='='){
                curr_sym=INFEG_TOKEN;
                lex_get_next_char();
            }
            break;
        case '>': 
            curr_sym=SUP_TOKEN;
            lex_get_next_char();
            if(curr_char=='='){
                curr_sym=SUPEG_TOKEN;
                lex_get_next_char();
            }
            break;
        case '(': curr_sym=PO_TOKEN;lex_get_next_char();break;
        case ')': curr_sym=PF_TOKEN;lex_get_next_char();break;
        case '[': curr_sym=CROCHET_O;lex_get_next_char();break;
        case ']': curr_sym=CROCHET_F;lex_get_next_char();break;
        //case '!': curr_sym=OPERATEUR_NON;lex_get_next_char();break;
        case '%': curr_sym=OPERATEUR_MODULO;lex_get_next_char();break;
       case '!': 
            curr_sym=OPERATEUR_NON;
            lex_get_next_char();
            if(curr_char=='='){
                curr_sym=OPERATEUR_DIFFERENT;
                lex_get_next_char();
            }
            break;


        case '*': 
            curr_sym=MULT_TOKEN;
            lex_get_next_char();
            if(curr_char=='/'){
                curr_sym=COMMENTAIRE;
                lex_get_next_char();
            }
            break;    
        

        case '/': 
            curr_sym=DIV_TOKEN;
            lex_get_next_char();
            if(curr_char=='/'){
                curr_sym=COMMENTAIRE_LIGNE;
                lex_get_next_char();
            }
            if(curr_char=='*'){
                curr_sym=COMMENTAIRE;
                lex_get_next_char();
            }
            break;

        case '|': 
            curr_sym=OPERATEUR_BINAIRE_OU;
            lex_get_next_char();
            if(curr_char=='|'){
                curr_sym=OPERATEUR_OU;
                lex_get_next_char();
            }
            break;
        
        case '&': 
            curr_sym=OPERATEUR_BINAIRE_ET;
            lex_get_next_char();
            if(curr_char=='&'){
                curr_sym=OPERATEUR_ET;
                lex_get_next_char();
            }
            break;

        case '^': curr_sym=OPERATEUR_BINAIRE_XOR;lex_get_next_char();break;
        case '~': curr_sym=OPERATEUR_BINAIRE_NON;lex_get_next_char();break;    
       
       
       
       
       
        case EOF: curr_sym=FIN_TOKEN;break;
        case '"':
        case '\'':
            read_string();
            break;
case '{': curr_sym=ACCOLADE_O;lex_get_next_char();break;
case '}': curr_sym=ACCOLADE_F;lex_get_next_char();break;




        //case '{':
            //skip_comment();
            //break;
        case '=': 
            curr_sym=EG_TOKEN;
            lex_get_next_char();
            if(curr_char=='='){
                curr_sym=EG_TOKEN;
                lex_get_next_char();
            }
            break;



       //case '.': curr_sym=PT_TOKEN;lex_get_next_char();break;


       case '.': 
            curr_sym=PT_TOKEN;
            lex_get_next_char();
            //if(isalpha(curr_char)){
                //read_word();break;
            //}
            break;


       default:
            if (isalpha(curr_char)){
                read_word();break;
            }else if (isdigit(curr_char)){
                read_number();break;
            }else{
                
                    printf("%d\n",curr_char);
                
                curr_sym=ERROR_TOKEN;return;
            }
    }
}
void print_token(LEX_CODE curr_sym){
    printf("%s line %d\n",TOKEN_NAMES[curr_sym],current_line);
}

void read_number(){
    while(isdigit(curr_char)){
        lex_get_next_char();
    }
    curr_sym=NUM_TOKEN;
}
void read_word(){
    char word[100];
    int i=0;
    while(isalnum(curr_char)||curr_char=='_'){
        word[i]=curr_char;
        i++;
        lex_get_next_char();
    }
    word[i]='\0';
    LEX_CODE code = keyword_code(word);
    if(code==-1) {
        curr_sym=ID_TOKEN;
        //add_to_id_array(word);
    }
    else curr_sym=code;
}
void read_string(){
    char quote=curr_char;
    lex_get_next_char();
    while(curr_char!=quote && curr_char!=EOF){
        lex_get_next_char();
    }
    if(curr_char==quote){
        curr_sym=STRING_TOKEN;
    }
    lex_get_next_char();
}
void skip_white_spaces(){
    while(curr_char==' '||curr_char=='\t'||curr_char=='\n'||curr_char=='\r'){
        if(curr_char=='\n') current_line++;
        lex_get_next_char();
    }
}
void skip_comment(){
    lex_get_next_char();
    while(curr_char!='}' && curr_char!=EOF){
        lex_get_next_char();
    }
    if(curr_char=='}'){
        lex_get_next_char();
    }
    next_sym();
}
LEX_CODE keyword_code(char* word){
    int i;
    for(i=0;i<number_of_keywords;i++){
        if(strcmp(word,pascal_keywords[i].keyword)==0){
            return pascal_keywords[i].code;
        }
    }
    return -1;
}
void analy_lex(FILE *fp){
    current_line = 1;
    //ids_arr_cursor = 0;
    last_keyword = -1;
    lex_get_next_char();
    int i=0;
    int count=0;
    while(curr_sym!=FIN_TOKEN && curr_sym!=ERROR_TOKEN){
        next_sym();
        LEX_CODE code1;
        LEX_CODE code2;
        LEX_CODE code3;
        LEX_CODE code4;
        code1=curr_sym;
        if(curr_sym==PT_TOKEN){
            next_sym();
            code2=curr_sym;
            if(curr_sym==SPLIT){
            
            //print_token(code1);
            print_token(SPLIT);
            symbols[i]=(SYMBOL){SPLIT,current_line};
        i++;
       
            
        }else if (curr_sym==INVERSER)
        {
            next_sym();
            code3=curr_sym;
                if(curr_sym==PO_TOKEN){
                    next_sym();
            code4=curr_sym;
            if(curr_sym==PF_TOKEN){
                  print_token(INVERSER);
            symbols[i]=(SYMBOL){INVERSER,current_line};
        i++;
            }
            
            else{print_token(code1);print_token(ID_TOKEN);print_token(code3);print_token(curr_sym);
             symbols[i]=(SYMBOL){code1,current_line};
        i++;symbols[i]=(SYMBOL){ID_TOKEN,current_line};
        i++;symbols[i]=(SYMBOL){code3,current_line};
        i++;}}
            else{print_token(code1);print_token(ID_TOKEN);print_token(code3);print_token(curr_sym);
            
            //for debuging 
        symbols[i]=(SYMBOL){code1,current_line};
        i++;symbols[i]=(SYMBOL){ID_TOKEN,current_line};
        i++;symbols[i]=(SYMBOL){code3,current_line};
        i++;}}
        
        
        else{print_token(code1) ;
        symbols[i]=(SYMBOL){code1,current_line};
        i++;print_token(code2);print_token(code3);print_token(code4);symbols[i]=(SYMBOL){code2,current_line};
        i++;}
        }
        else{
        print_token(curr_sym); //for debuging 
        symbols[i]=(SYMBOL){curr_sym,current_line};
        i++;}
    }
   
int j=0;
for(j;j<i;j++){

    printf("\n\n%s\n\n ",TOKEN_NAMES[symbols[j].token]);

}
   
     
}