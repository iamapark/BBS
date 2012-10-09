#include "mkbbs.h"

int main(){
	char* symbol = (char *)malloc(sizeof(char) * 2);
	char* boardName=(char *)malloc(sizeof(char) * 128);
	char*  boardType = (char *)malloc(sizeof(char) * 2);
	int nread = 0;

	confirm_file();
	get_symbol(symbol);
	nread = get_boardName(boardName);
	get_boardType(boardType);
	makeDir(symbol, boardName, boardType);
	set_boardIndex(symbol, boardName, nread);
	return 0;
}

void get_symbol(char* symbol){
	
	char* p;

	printf("게시판 심볼: ");
	fgets(symbol, sizeof(symbol), stdin);
	if((p = strchr(symbol, '\n'))!=NULL) *p = '\0';

	if(access((char *)symbol, 0)==0){
		printf("게시판 심볼 %s는 이미 사용중입니다. 다른 심볼을 사용하시겠습니까?(Y/N)", symbol);
		fflush(stdin);
		switch(getchar()){
			case 'Y':
				get_symbol(symbol);
				break;
			case 'N':
				printf("취소되었습니다.");
				exit(1);
		}
	}

	fflush(stdout);
	fflush(stdin);
}

int get_boardName(char* boardName){

	int nread;

	printf("게시판 이름: ");

	nread = read(0, boardName, 128);
	
	return nread;
}

void confirm_file(){
	int bValue = access("board.index", 0);
	int aValue = access("article.index", 0);

	if(bValue==0){  // board.index 파일 존재
		if(aValue==0){ // article.index 파일 존재
			printf("하위 게시판을 생성할 수 없습니다.");
			exit(1);
		}
	}else{ // board.index 파일 없음
		printf("BBS 게시판이 아닙니다.");
		exit(1);
	}
}

void get_boardType(char* boardType){
		
	printf("게시판 유형\n1. 글 게시판\n2. 게시판 목록 : 하위에 게시판을 계속해서 생성할 수 있습니다.\n3. 취소\n게시판 유형을 선택하세요?");

	fflush(stdin);
	fflush(stdout);
	
	scanf("%s", boardType);

	if(strcmp(boardType, "3")==0){
		printf("취소되었습니다.");
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

	w1 = write(filedes, symbol, sizeof(symbol));
	write(filedes, "\n", 1);
	w2 = write(filedes, boardName, nread);
	write(filedes, "\n", 1);
	
	printf("디렉토리 이름: %s", symbol);
	printf("게시판 이름: %s\n", boardName);

	close(filedes);
		
}
