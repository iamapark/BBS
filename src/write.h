#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_Subject(char* subject, FILE* file);
void set_Content(char* content, FILE* file);
char* get_writer();
void get_fileIndexNum(char* currentIndex, char* numOfArticle, int *nCurrentIndex, int *nNumOfArticle);
void set_ArticleIndex(char* currentIndex, char* numOfArticle, char* subject, int *nCurrentIndex, int *nNumOfArticle);
FILE* open_File(char* index, char* mode);