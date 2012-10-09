#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

typedef enum{
	FALSE,
	TRUE
} BOOL;

void confirm_file();
int delDirFile(const char* folder);
void set_BoardIndex(const char* symbol);