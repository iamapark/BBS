#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
	FALSE,
	TRUE
} BOOL;

BOOL confirmDeletion();
BOOL confirmIndexFile(char* deleteIndex);
BOOL confirmFileWriter(char* deleteIndex, char* fileSubject);
char* get_writer();
BOOL deleteFile(char* deleteIndex);
void set_ArticleIndex(char* index, char* subject, int* position);
char* get_fileIndexNum(char* index, int* pos);