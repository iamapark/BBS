#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <errno.h>
//#include <dirent.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <windows.h>

void confirm_file();
void get_symbol(char* symbol);
void get_boardName(char* boardName);
void get_boardType(char* boardType);
void makeDir(char* symbol, char* boardName, char* boardType);
void set_boardIndex(char* symbol, char* boardName);
