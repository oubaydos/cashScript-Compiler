// #include "analy_syn.h"
#include "analy_lex.h"
#include "analy_lex.c"
// #include "analy_syn.c"
// #include "anly_sem.c"
#include "data.h"
#include "data.c"
// #include "analy_sem.h"

int main(int argc, char *argv[])
{
  // if (argc<2){
  //   printf("no file specified");
  //   return -1;
  // }else{
  //   fp = fopen(argv[1],"r");
  fp = fopen("../tests/test1.cash", "r"); // for debuging
  if (fp == NULL)
  {
    perror("Error in opening file");
    return -1;
  }
  // printf("BRAVO: le programme est correcte!!!");
  analy_lex(fp);
  printf("BRAVO: le programme est correcte!!!");
  // you should assert that the expected tokens in the file ../tests/expected1.txt are the same as the result tokens of analysing test1.txt
  fclose(fp);
  // printf("--\n%d\n", pascal_keywords[0].token);
  return 0;
  //}
}

// cd "C:\Users\hp\Desktop\Pascal-master1\Pascal-master\src" && C:\TDM-GCC-64\bin\gcc main.c -o main && "C:\Users\hp\Desktop\Pascal-master1\Pascal-master\src"\main
