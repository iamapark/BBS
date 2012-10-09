#include "delbbs.h"

int main(int argc, char **argv){
	
	char* symbol = argv[1];

	//confirm_file();
	deleteDir(symbol);

	return 1;
}

void confirm_file(){
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
}

void deleteDir(char* symbol){
	DIR* dp;
	struct dirent *dirp;
	struct stat file_stat;
	char targetfile[512];

	sprintf(targetfile, "%s/%s", symbol, dirp->d_name);   // Path와 파일이름을 합친다
    stat(targetfile, &file_stat);

	if( rmdir(symbol)  == -1){
		printf("해당 게시판은 하위 게시판을 가지고 있습니다. 하위 게시판을 먼저 삭제해야합니다.\n");
		exit(1);
	}
	


	printf("게시판 %s이 삭제되었습니다.", symbol);

}