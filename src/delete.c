#include "delete.h"


int main(int argc, char* argv[]){

	char index[100];
	char* fileSubject = (char *)malloc(sizeof(char) * 128*100);
	char* deleteIndex;
	int pos = 0;

	if(argc==1){//명령행 파라미터가 없을 때
		printf("USAGE: DELETE [filename]\n");
		return 2;
	}
	else{

		if(!confirmDeletion())
			return 2;

		deleteIndex = argv[1];
	
		if(confirmIndexFile(deleteIndex)){
			if(confirmFileWriter(deleteIndex, fileSubject)){
				if(deleteFile(deleteIndex)){
					get_fileIndexNum(index, &pos);
					set_ArticleIndex(index, fileSubject, &pos);
				}else{
					printf("해당 파일을 삭제할 수 없습니다.");
					return 2;
				}
				
			}else{
				printf("다른 사용자가 작성한 글은 삭제할 수 없습니다.\n");
			}
		}else{
			printf("해당 글이 존재하지 않습니다.\n");
			return 2;
		}
	}
	free(fileSubject);
	return 0;
}

BOOL confirmDeletion(){

	char yOrN[10];
	BOOL flag;

	printf("삭제한 글은 복구할 수 없습니다. 계속하시겠습니까(Y/N)?");
	scanf("%s", yOrN);

	if(strcmp(yOrN, "Y")==0)
		flag = TRUE;
	else
		flag = FALSE;

	return flag;
}

BOOL confirmIndexFile(char* deleteIndex){

	BOOL flag = TRUE;

	FILE* file = fopen(deleteIndex, "rt");

	if(file==NULL){
		flag = FALSE;
	}else{
		fclose(file);
	}

	return flag;
}

BOOL confirmFileWriter(char* deleteIndex, char* fileSubject){
	BOOL flag;
	char* CurrentWriter = get_writer();
	char fileWriter[80];
	char* p;

	FILE* file = fopen(deleteIndex, "rt");
	fgets(fileSubject, 160, file);
	fgets(fileWriter, 160, file);
	if((p = strchr(fileWriter, '\n'))!= NULL) *p = '\0';
	if((p = strchr(fileSubject, '\n'))!= NULL) *p = '\0';

	if(strcmp(fileWriter, CurrentWriter)==0)
		flag = TRUE;
	else
		flag = FALSE;

	fclose(file);

	return flag;
}

char* get_writer() {
    return  "홍길동";
}

BOOL deleteFile(char* deleteIndex){

	BOOL flag;

	if(remove(deleteIndex)==0){
		flag = TRUE;
		printf("%s번 글이 삭제되었습니다.", deleteIndex);
	}else{
		flag = FALSE;
	}

	return flag;
}

char* get_fileIndexNum(char* index, int* pos){

	FILE* file = fopen("article.index", "rt");
	char* p;
	char buf[160];
	int cnt = 0;

	while(fgets(buf, 160, file)!=NULL){
		if(cnt==4){
			*pos = (int)ftell(file);
		}
		if(cnt==5){
			strcpy(index, buf);
			sprintf(index, "%s", buf);
		}

		cnt++;
	}
	fflush(file);
	if((p = strchr(index, '\n'))!= NULL) *p = '\0';
	fclose(file);
	return index;
}

void set_ArticleIndex(char* index, char* subject, int* position){
	int nIndex = atoi(index);
	char buf[160];
	char* p;
	int pos=0;
	int cnt=0;
	FILE* file = fopen("article.index", "r+");

	sprintf(index, "%d", nIndex-1);

	fseek(file, *position, SEEK_SET);
	fputs(index, file);
	fflush(file);


	fseek(file, 0, SEEK_SET);

	while(fgets(buf, sizeof(buf), file)!=NULL){
		if((p = strchr(buf, '\n'))!= NULL) *p = '\0';

		if(strcmp(buf, subject)==0){
			pos = ftell(file);
			break;
		}
	}

	fseek(file, pos-strlen(subject)-strlen(index)-2, SEEK_SET);
	fputc(68,file);

	fclose(file);
}
