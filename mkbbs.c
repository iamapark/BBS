#include "mkbbs.h"

int main(){
	char* symbol = (char *)malloc(sizeof(char) * 64);
	char* boardName=(char *)malloc(sizeof(char) * 128);
	char*  boardType = (char *)malloc(sizeof(char) * 2);
	int nread = 0;

	confirm_file();
	get_symbol(symbol);
	nread = get_boardName(boardName);
	get_boardType(boardType);
	makeDir(symbol, boardName, boardType);
	set_boardIndex(symbol, boardName, nread);
	make_boardIndex(boardName, symbol);
	return 0;
}

void confirm_symbol(char* symbol){
	//board.index 파일에서 사용자가 입력한 심볼과 일치하는
	// 디렉토리가 있는지 검색한다.

	FILE* file = fopen("board.index", "rt");
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
					printf("게시판 심볼 %s는 이미 사용중입니다. 다른 심볼을 사용하시겠습니까?(Y/N)", symbol);
					fgets(s, sizeof(s), stdin);
					s[strlen(s)-1] = '\0';
					fputs(s, stdout);

					if(strcmp(s, "Y")==0)
						get_symbol(symbol);
					else if(strcmp(s, "N")==0){
						printf("취소되었습니다.");
						exit(1);
					}else{
						printf("취소되었습니다.");
						exit(1);
					}
				}
			}	
			
			if(flag==0){
				if(buf[0]=='#') flag++;
				else if(strcmp(buf, symbol)==0){
					flag = 2;
					printf("게시판 심볼 %s는 이미 사용중입니다. 다른 심볼을 사용하시겠습니까?(Y/N)", symbol);
					fflush(stdin);
					fgets(s, sizeof(s), stdin);
					s[strlen(s)-1] = '\0';
					fputs(s, stdout);

					if(strcmp(s, "Y")==0)
						get_symbol(symbol);
					else if(strcmp(s, "N")==0){
						printf("취소되었습니다.");
						exit(1);
					}else{
						printf("취소되었습니다.");
						exit(1);
					}
				}else
					flag = 2;
			}
			flag--;
		}
		cnt++;
	}		
}

void get_symbol(char* symbol){
	
	char* p;
	printf("게시판 심볼: ");
	fflush(stdout);
	//fgets(symbol, sizeof(symbol), stdin);
	read(0, symbol, 64);
	if((p = strchr(symbol, '\n'))!=NULL) *p = '\0';

	confirm_symbol(symbol);
}

int get_boardName(char* boardName){

	int nread = 0;

	printf("게시판 이름: ");
	fflush(stdout);

	nread = read(0, boardName, 128);
	
	return nread;
}

void confirm_file(){
	int bValue = access("board.index", 0);
	int aValue = access("article.index", 0);
	int dValue = access(".", W_OK);
	char buf[255];

	if(dValue==-1){
		printf("시스템 오류: 권한이 없습니다.\n");
		exit(1);
	}

	if(bValue==0){  // board.index 파일 존재
		if(aValue==0){ // article.index 파일 존재
			printf("하위 게시판을 생성할 수 없습니다.\n");
			exit(1);
		}
	}else{ // board.index 파일 없음
		printf("BBS 게시판이 아닙니다.\n");
		exit(1);
	}

	

	memset(buf, 0x00, 255);
    if(readlink(".", buf, 255)==0){
		printf("게시판 경로가 잘못되었습니다. 올바른 위치에서 실행해야합니다.\n");
		exit(1);
	}
}

void get_boardType(char* boardType){
		
	printf("게시판 유형\n1. 글 게시판\n2. 게시판 목록 : 하위에 게시판을 계속해서 생성할 수 있습니다.\n3. 취소\n게시판 유형을 선택하세요?");

	fflush(stdin);
	fflush(stdout);
	
	scanf("%s", boardType);

	if(strcmp(boardType, "3")==0){
		printf("\n취소되었습니다.");
		exit(1);
	}
}

void makeDir(char* symbol, char* boardName, char* boardType){

	DIR *dp;
	char dirname[200];

	if(mkdir(symbol, 0777)==-1){
		printf("error: %d", errno);	
	}
	
	getcwd(dirname, 200);
	dp = opendir(dirname);

	

}

void set_boardIndex(char* symbol, char* boardName, int nread){
	int filedes;
	ssize_t w1, w2;

	if((filedes = open("board.index", O_WRONLY | O_APPEND))==-1){
		printf("error: %d\n", errno);
	}

	w1 = write(filedes, symbol, strlen(symbol));
	write(filedes, "\n", 1);
	w2 = write(filedes, boardName, nread);

	close(filedes);
}

void make_boardIndex(char* boardName, char* symbol){
	int filedes;
	char bbs[100]= "BBS-";
	char dir[100] = "./";
	char* comment = "# 첫 줄부터 '#'으로 시작하는 경우 주석으로 해석한다. 파일 중간에 나타나\n#는 '#'는 확장 필드로 해석하며, 해석할 수 없는 경우 주석으로  처리한다.\n#글머리 주석과 명세가 시작하는 줄 사이에 한 줄을 비워야 한다.\n\n";

	strcat(bbs, boardName);
	strcat(dir, symbol);
	strcat(dir, "/board.index");

	if((filedes = open(dir, O_WRONLY | O_CREAT, 0644))==-1){
		printf("error: %d\n", errno);
	}

	write(filedes, comment, strlen(comment));
	write(filedes, bbs, strlen(bbs));
	write(filedes, "\n", 1);
	
	puts("생성되었습니다.");

	close(filedes);
}
