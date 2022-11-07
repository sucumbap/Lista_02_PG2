#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include "1.h"
#define MAX_WORD_COUNT 1000
#define MAX_WORD_SIZE 8

struct filename {
   char *name;
}FILENAME[100];
struct lines {
   char line[150];
   int line_number;
};
struct text {
   struct lines text[10000];
};
typedef struct{ 
    int count; 
    char words[MAX_WORD_COUNT][MAX_WORD_SIZE]; 
} DataStore;


int main () {
   
   int number_of_files = readDirectory("texts/");
   for (int i = 2; i < number_of_files; i++){
      char *dir_name = "texts/";
      char *file_name = FILENAME[i].name;
      char *path = malloc(strlen(dir_name) + strlen(file_name) + 1);
      if(path == NULL) { return 0; }
      strcpy(path, dir_name);
      strcat(path, file_name);
      if (has_txt_extension(path)){
         ReadFileLineByLine(path);
      }
      free(path);
   }
   
 
    
   
   return(0);
}

// This function is going to be passed trought the proc argumente of the wordSplit function
// It will be used to store the words in the DataStore struct
// It will add the word to the struct whitch is passed as the argument context
// If the struct capacity is reached it will use the function stderr to print an error message
// It returns 1 if the word was added to the struct and 0 if the struct capacity was reached or the word was already in the struct
int wordStore( char *word, void *context ) {
   DataStore *data = (DataStore *)context;
   if (data->count == MAX_WORD_COUNT){
      fprintf(stderr, "Error: The struct capacity is reached");
      return 0;
   }
   for (int i = 0; i < data->count; i++){
      if (strcmp(data->words[i], word) == 0){
         return 0;
      }
   }
   strcpy(data->words[data->count], word);
   data->count++;
   return 1;
}
// This function is going to be passed trought the qsort function and bsearch function
// It will be used to compare the words in the words array on a dataStore struct
// It will use strcoll to compare the words by their alphabetical order
// It returns an integer less than, equal to, or greater than zero if the first argument is found, respectively, to be less than, to match, or be greater than the second.
// There should be no pointer incompatilability because the function is passed trought the qsort and bsearch functions
int dataComp( const void *a, const void *b ) {
   char *word1 = (char *)a;
   char *word2 = (char *)b;
   return strcoll(word1, word2);
}

// This function is going to call qsort with dataComp to sort the words array in the dataStore struct
void dataSort( DataStore *data ) {
   qsort(data->words, data->count, MAX_WORD_SIZE, dataComp);
}
// This function is going to call bsearch with dataComp to search for a word in the words array in the dataStore struct
// It returns a pointer to the matching element of the array if the word is found and NULL if the word is not found
char *dataSearch( DataStore *data, const char *sample ) {
   return bsearch(sample, data->words, data->count, MAX_WORD_SIZE, dataComp);
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
   printf("Total number of words: %d\n", wordCounter);
   return wordCounter;
}

int wordPrint( char *word, void *context ){
   printf( "%s\n", word );
   return 1;
}

int wordCheck( char *word, void *context ) {
   switch (strcoll(word, context)) {
      case 0:
         return 1;
      default:
         return 0;
   }
}

char *ReadFile(char *filename) {
   //printf("Reading file: %s\n", filename);
   FILE *fp;
   char *content = NULL;
   int count=0;
   if (filename != NULL) {
      fp = fopen(filename,"r");
      if (fp != NULL) {
         fseek(fp, 0, SEEK_END); //Get the last byte of the file
         count = ftell(fp);      //Offset from the first to the last byte,filesize
         rewind(fp);             //Set position indicator to the beginning of the file
         if (count > 0) {        //If file is not empty
            content = (char *)malloc(sizeof(char) * (count+1));//Allocate memory for the content
            count = fread(content,sizeof(char),count,fp);      //Read file in a string and store it in content
            content[count] = '\0';                             //Set the last character of the string to \0
            if(ferror(fp)) {
               printf("Error reading file %s\n", filename);
               free(content);
            }
            fclose(fp);                                        //Close the file
         }
      }
      return content;                                          //Return the string

   }
   return NULL;
}

struct text *ReadFileLineByLine(char *filename) {
   struct text *text = malloc(sizeof(struct text));
   int i = 0;
   FILE *fp;
   char line[150];
   fp = fopen(filename, "r");
   if (fp == NULL) {
      printf("Error opening file %s\n", filename);
      return NULL;
   }
   while (fgets(line, 150, fp) != NULL) {
      if(i > 10000) {
         printf("Error: File too large");
         return NULL;
      }
      strcpy(text->text[i].line, line);
      text->text[i].line_number = i;
      i++;
   }
   return text;
}
int readDirectory(char *directory) {
   DIR *dir;
   struct dirent *ent;
   int i = 0;
   if ((dir = opendir (directory)) != NULL) {
      printf("Reading directory: %s\n", directory);
      while ((ent = readdir (dir)) != NULL) {
         if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 ) {
            char *filename = ent->d_name;
            printf("Reading file: %s\n", filename);
            FILENAME[i].name = filename;
         }
         i++;
      }
      closedir (dir);
   } else {
      /* could not open directory */
      perror ("Could not open directory");
      return -1;
   }
   return i;
}

bool has_txt_extension(char const *name) {
    size_t len = strlen(name);                              //Get the length of the filename
    return len > 4 && strcmp(name + len - 4, ".txt") == 0;  //Check if the last 4 characters are ".txt"
}