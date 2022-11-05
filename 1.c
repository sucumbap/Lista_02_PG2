#include <string.h>
#include <stdio.h>

int wordSplit( char *str, int (*proc)( char *word, void *context ),void *context );
int wordPrint( char *word, void *context );

int main () {

   return(0);
}


int wordSplit( char *str, int (*proc)( char *word, void *context ),void *context ) {


   const char s[2] = " ";
   char *token;
   
   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( "%s\n", token );

      token = strtok(str, s);
   }

}

int wordPrint( char *word, void *context ) {
    while(word!=context){
        printf("%u",*word);
        word++;
    }
    return 1;
}