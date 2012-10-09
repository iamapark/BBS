#include "delbbs.h"

char* symbol;

int main(int argc, char **argv){
	
	symbol = argv[1];

	confirm_file(argv[1]);
	delDirFile(argv[1]);
	set_BoardIndex(argv[1]);

	return 1;
}

void confirm_file(const char *symbol){
	int bValue = access("board.index", 0);
	int aValue = access("article.index", 0);
	int dValue = access(".", W_OK);
	char buf[255];

	if(bValue==-1){
		printf("BBS 게시판이 아닙니다.\n");
		exit(1);
	}else{
		if(aValue==0){ // article.index 파일 존재
			printf("하위 게시판을 생성할 수 없습니다.\n");
			exit(1);
		}
	}

	if(dValue==-1){
		printf("시스템 오류: 권한이 없습니다.\n");
		exit(1);
	}

	ftw(symbol, searchDIR, 1);
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
      printf("해당 게시판이 존재하지 않습니다.\n");
		exit(1);
   }
 
   while(1)
   {
      if(!(dirp = readdir(dp)))
      {
         closedir(dp);
         remove(folder);
         return -1;
      }

	  sprintf(targetfile, "%s/%s", folder, dirp->d_name);   // Path와 파일이름을 합친다
      stat(targetfile, &file_stat);
 
      if((file_stat.st_mode & S_IFMT) == S_IFDIR)        // Directory 이면...
      {	
			continue;
      }
      if(remove(targetfile) == 0)
      {
		 printf("게시판 %s가 삭제되었습니다.\n", folder);
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

void set_BoardIndex(const char* symbol){

	FILE* file = fopen("board.index", "r+");
	char buf[160];
	char* p;
	char s[4];
	int cnt = 0;
	int flag = 2;

	while(fgets(buf, 160, file)!=NULL){
		if((p=strchr(buf, '\n'))!=NULL) *p = '\0';
		if(cnt >= 6){
			if(cnt==6){
				if(strcmp(buf, symbol)==0){
					flag = 1;
					fseek(file, -1-strlen(symbol), SEEK_CUR);
					fputs(" ", file);
				}
			}	
			
			if(flag==0){
				if(buf[0]=='#') flag++;
				else if(strcmp(buf, symbol)==0){
					flag = 1;
					fseek(file, -1-strlen(symbol), SEEK_CUR);
					fputs(" ", file);
				}else
					flag = 2;
			}
			flag--;
		}
		cnt++;
	}		
}

int searchDIR(const char *name, const struct stat *status, int type)
{
	switch ( type )
	{
		case FTW_D:
			/*if ( rmdir(name) == -1 )
				perror("unlink");
			printf("% - 30s*\t0%3o-%s\n", name, status->st_mode&0777, symbol);*/
			if(strcmp(name, symbol)!=0){
				printf("해당 게시판은 하위 게시판을 가지고 있습니다. 하위 게시판을 먼저 삭제해야합니다.");
				exit(1);
			}
			break;
 
		/*case FTW_F:
		case FTW_SL:
			printf("% - 30s\t0%3o\n", name, status->st_mode&0777);
			if ( unlink(name) == -1 )
				perror("unlink");
			break;*/
	}

	return 0;
}