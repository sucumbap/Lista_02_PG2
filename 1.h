int wordSplit( char *str, int (*proc)( char *word, void *context ),void *context );
int wordPrint( char *word, void *context );
int wordCheck( char *word, void *context );
int readDirectory(char *directory);
char *ReadFile(char *filename);
bool has_txt_extension(char const *name);
struct text *ReadFileLineByLine(char *filename);
int wordStore( char *word, void *context );