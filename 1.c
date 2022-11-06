#include <string.h>
#include <stdio.h>

int wordSplit( char *str, int (*proc)( char *word, void *context ),void *context );
int wordPrint( char *word, void *context );

int main () {
   char str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla suscipit lorem sit amet libero interdum dictum. Nulla vestibulum, mi egestas tincidunt rutrum, leo quam rutrum nibh, id pellentesque lorem libero sit amet est. Donec mattis tellus nibh, sit amet pharetra purus bibendum eget. Morbi bibendum vitae magna vitae dapibus. Nunc tempor cursus diam eu congue. Curabitur ac nulla et enim bibendum venenatis ut et risus. Nullam eu velit in est egestas aliquet. Nam vitae eleifend erat.";
   wordSplit( str, wordPrint, NULL );
   return(0);
}


int wordSplit( char *str, int (*proc)( char *word, void *context ),void *context ) {

   const char s[2] = " ";
   char *token;
   int wordCounter = 0;
   
   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
      wordCounter += proc(token, context);
      token = strtok(NULL, s);
   }
   printf("Total number of words: %d:", wordCounter);
   return wordCounter;
}
int wordPrint( char *word, void *context ){
   printf( "%s\n", word );
   return 1;
}