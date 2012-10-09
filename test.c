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

char *symbol;

int list(const char *name, const struct stat *status, int type)
{
	switch ( type )
	{
		case FTW_D:
			if ( rmdir(name) == -1 )
				perror("unlink");
			printf("% - 30s*\t0%3o-%s\n", name, status->st_mode&0777, symbol);
			if(strcmp(name, symbol)!=0){
				printf("Other Directory\n");
				/*printf("해당 게시판은 하위 게시판을 가지고 있습니다. 하위 게시판을 먼저 삭제해야합니다.");
				exit(1);*/
			}
			break;
 
		case FTW_F:
		case FTW_SL:
			printf("% - 30s\t0%3o\n", name, status->st_mode&0777);
			if ( unlink(name) == -1 )
				perror("unlink");
			break;
	}

	return 0;
}

int delDirFile(const char* folder)
{
   DIR* dp;
   struct dirent *dirp;
   struct stat file_stat;
   char targetfile[512];
   int cnt = 0;
 
 
   if((dp = opendir(folder)) == NULL)
   {
      perror("Open Error : ");
      return -1;
   }
   printf("Target Directory open Succeed!\n");
 
   while(1)
   {
      if(!(dirp = readdir(dp)))
      {
         perror("readdir Error : ");
         closedir(dp);
         //remove(folder);
         return -1;
      }

	  sprintf(targetfile, "%s/%s", folder, dirp->d_name);   // Path와 파일이름을 합친다
      stat(targetfile, &file_stat);
 
      if((file_stat.st_mode & S_IFMT) == S_IFDIR)        // Directory 이면...
      {	
			if(cnt>1){
			printf("해당 게시판은 하위 게시판을 가지고 있습니다. 하위 게시판을 먼저 삭제해야합니다.");
			exit(1);
			}

			cnt++;
			continue;
      }
      if(remove(targetfile) == 0)
      {
         continue;
      }
      else
      {
         perror("remove Error : ");
         break;
      }
   }
   return 1;
}

main(int argc, char **argv)
{
	if(argc == 1)
		//ftw(".", list, 1);
		printf("usage listDel folderName");
	else{
		symbol = argv[1];
		//ftw(argv[1], list, 1);
		//ftw(argv[1], list, 1);
		delDirFile(argv[1]);
	}

	exit(0);
}