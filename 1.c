#include <string.h>
#include <stdio.h>

int wordSplit( char *str, int (*proc)( char *word, void *context ),void *context );
int wordPrint( char *word, void *context );

int main () {
   
   
   return(0);
}


int wordSplit( char *str, int (*proc)( char *word, void *context ),void *context ) {

   char str[800] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla suscipit lorem sit amet libero interdum dictum. Nulla vestibulum, mi egestas tincidunt rutrum, leo quam rutrum nibh, id pellentesque lorem libero sit amet est. Donec mattis tellus nibh, sit amet pharetra purus bibendum eget. Morbi bibendum vitae magna vitae dapibus. Nunc tempor cursus diam eu congue. Curabitur ac nulla et enim bibendum venenatis ut et risus. Nullam eu velit in est egestas aliquet. Nam vitae eleifend erat.";
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
int wordPrint( char *word, void *context );