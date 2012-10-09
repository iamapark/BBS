//#include "write.h"
//#include <assert.h>
//
//
//int main(int argc, char* argv[])
//{
//	char numOfArticle[100]; 
//	char currentIndex[100];
//	char* subject = (char *)malloc(sizeof(char) * 128*100);
//	char* content = (char *)malloc(sizeof(char) * 100*100*100);
//	int nCurrentIndex = 0;
//	int nNumOfArticle = 0;
//	FILE* file = NULL;
//
//	get_fileIndexNum(currentIndex, numOfArticle, &nCurrentIndex, &nNumOfArticle);
//	file = open_File(currentIndex, "w+");
//	
//	set_Subject(subject, file);
//	set_Content(content, file);
//	set_ArticleIndex(currentIndex, numOfArticle, subject, &nCurrentIndex, &nNumOfArticle);
//
//	free(subject);
//	free(content);
//	fclose(file);
//	return 0;
//}
//
//FILE* open_File(char* index, char* mode){
//	FILE* file = fopen(index, mode);
//	
//	if(file==NULL){
//		printf("파일 생성 실패");	
//	}else{
//		printf("파일 생성 성공");
//	}
//
//	return file;
//}
//
//void set_Subject(char* subject, FILE* file){
//	printf("%s", "제목: ");
//	gets(subject);
//	fflush(stdin);
//
//	fputs(subject, file);
//	fputs("\n", file);
//	fputs(get_writer(), file);
//	fputs("\n\n", file);
//	fflush(file);
//}
//
//void set_Content(char* content, FILE* file){
//
//	char ch;
//	
//	printf("내용을 입력하세요. 입력을 종료하려면 마지막 줄에 마침표(.)를 입력하고 엔터(Enter)키를 누르세요.\n");
//
//	while(1){
//		ch = getchar();
//		if(ch=='.')
//			break;
//
//		fputc(ch, file);
//	}
//	fputc('\n', file);
//	fflush(file);
//}
//
//char* get_writer() {
//    return  "홍길동";
//}
//
//void get_fileIndexNum(char* currentIndex, char* numOfArticle, int *nCurrentIndex, int *nNumOfArticle){
//
//	FILE* file = fopen("article.index", "rt");
//	char* p;
//	char buf[160];
//	int cnt = 0;
//
//	while(fgets(buf, 160, file)!=NULL){
//		if(cnt==3){
//			*nCurrentIndex = (int)ftell(file);
//		}
//		else if(cnt==4){
//			*nNumOfArticle = (int)ftell(file);
//			strcpy(currentIndex, buf);
//		}else if(cnt==5){
//			strcpy(numOfArticle, buf);
//		}
//		cnt++;
//	}
//
//	fflush(file);
//	if((p = strchr(currentIndex, '\n'))!= NULL) *p = '\0';
//	if((p = strchr(numOfArticle, '\n'))!= NULL) *p = '\0';
//
//	fclose(file);
//}
//
//void set_ArticleIndex(char* currentIndex, char* numOfArticle, char* subject, int *pCurrentIndex, int *pNumOfArticle){
//	
//	FILE* file = fopen("article.index", "r+");
//	int nCurrentIndex = atoi(currentIndex);
//	int nNumOfArticle = atoi(numOfArticle);
//	char currentIndexNum[10];
//	char a[100]="";
//	char b[100]="";
//	strcpy(currentIndexNum, currentIndex);
//	nCurrentIndex++;
//	nNumOfArticle++;
//	sprintf(a, "%d", nCurrentIndex);
//	sprintf(b, "%d", nNumOfArticle);
//	
//	fseek(file, *pCurrentIndex, SEEK_SET); 
//	fputs(a, file);
//
//	fseek(file, *pNumOfArticle, SEEK_SET); 
//	fputs(b, file);
//	
//	fclose(file);
//
//	file = fopen("article.index", "a+t");
//	fseek(file, 0, SEEK_END);
//	//글 번호
//	fputs(currentIndexNum, file);
//	//글 제목
//	fputs("\n", file);
//	fputs(subject, file);
//	//글쓴이
//	fputs("\n", file);
//	fputs(get_writer(), file);
//	//첨부 파일 갯수
//	fputs("\n", file);
//	fputs("0", file);
//	fputs("\n", file);
//	fflush(file);
//
//	fclose(file);
//}