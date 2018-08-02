#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
(1) function : FUNC 노드 생성 함수.
(2) input value
	- char *name, char *header, char *source, char *comment
(3) return value
  	- FUNC *
  	 생성 된 노드 
*/
FUNC* MakeNode(char *name, char *header, char *source, char *comment) { 
	FUNC* newNode = (FUNC*)malloc(sizeof(FUNC));
	strcpy(newNode->name, name);
	strcpy(newNode->header, header);
	strcpy(newNode->source, source);
	strcpy(newNode->comment, comment);
	newNode->next = NULL;

	return newNode;
}

/*
(1) function : $name 에 해당하는 값 검색 함수.
(2) input value
	- FUNC* root, char* name
(3) return value
 	- FUNC *
 	/* 검색 성공 : 검색한 노드 , 검색 실패 : NULL
(4) 데이터 입력 포맷
	ex) 내용/'\n' 
*/
FUNC* FindNode(FUNC* root, char* name) { 

	FUNC* curr = root; 	
	char tmp[100] = { 0 };
	while (curr != NULL) {		
		/*  시행착오(1)
		파일에서 읽어오는 데이터는 마지막에 '\n' (엔터값)이 남아있어서 엔터값 제거를 해야지 검색내용과 일치한다.
		ex) printf'\n' != printf --> printf == printf
		*/
		strcpy(tmp, curr->name);
		tmp[strlen(curr->name) - 1] = '\0';
		if (!strcmp(tmp, name)) {  // 비교(!)
			return curr; /* 데이터가 있다면 해당 노드 반환*/
		}
		curr = curr->next;
	}	
	return NULL; /* 데이터가 없다면 NULL 반환*/
}
/*
(1) function : 생성된 FUNC 노드 연결.
(2) input value
 	- FUNC* root, FUNC* newNode
(3) return value
	- FUNC *
  	 main stack 영역에 root 주소값을 전달해주기 위해 return 한다.
*/
FUNC* AppendNode(FUNC* root, FUNC* newNode)
{
	/* 노드를 처음 연결하는 경우.*/
	if (root == NULL) {
		root = newNode;
		return root; 
	}
	/* 노드가 1개 이상인 경우.*/
	FUNC* curr = root;
	/* 다음노드 next 가 없는 경우까지 노드 이동.*/
	while (curr->next != NULL) {
		curr = curr->next;
	}
	/* next 가 없는 경우 FUNC* newNode 전달 받은 노드를 연결*/
	curr->next = newNode;
	return NULL;
}
/*
(1) function : 선택된 노드 출력
(2) input value
 	- FUNC* curr
(3) return value
 	- NONE
*/
void Print(FUNC* curr) {
	printf("name : %s\n", curr->name);
	printf("header : %s\n", curr->header);
	printf("source : %s\n", curr->source);
	printf("comment : %s\n", curr->comment);
	printf("\n");
}
/*
(1) function : 파일에서 읽어온 $data 구조체 내용으로 분리.
(2) input value
- char* data
(3) return value
- FUNC*
*/
FUNC* MakeData(char* data) {
	char name[20] = { 0 };
	char header[20] = { 0 };
	char source[1000] = { 0 };
	char comment[200] = { 0 };

	char* ptr[4] = { name, header, source, comment };
	int idx = 0;

	/*
	strtok : 특정 문자로 문자열 분리. 
	ex) printf/ int main -> char * div = printf ;  
	    파일 처음부터 검색을 진행하고 '/' 값이 나오면 그 전까지 문자열 저장.
	*/
	char* div = strtok(data, DELIS);
	while (div != NULL)
	{
		/*
	 	strncpy 
		ptr : name, header ... 등 4개의 문자열 주소를 저장하고 있는 char 포인터 배열
		검색된 문자열 div 를 div 만큼 복사.
		*/
		strncpy(ptr[idx++], div, strlen(div));
		/* strtok 내부에 자르고 남은 문자열이 저장되 있어서 첫번째 인자에 NULL을 넣으면 그다음 '/' 나올때 까지 탐색한다.*/
		div = strtok(NULL, DELIS);
	}

	return MakeNode(name, header, source, comment);
}

void WriteData(FUNC* root) {
	char name[100] = { 0 };
	char header[100] = { 0 };
	char source[1000] = { 0 };
	char comment[200] = { 0 };

	char* ptr[4] = { name, header, source, comment };
	char* head[4] = { "이름" , "헤더", "예제소스", "주석" };
	int i = 0, tmp = 0, len;
	char c;
	for (i = 0; i < 4; i++) {
		if (i == 2) {
			printf("%s 입력($를 마지막에 넣어주세요) : ", head[i]);
			scanf("%[^$]", ptr[i]);
			len = strlen(ptr[i]);
			ptr[i][len] = ' '; ptr[i][len + 1] = '\0';
			getchar();
		}
		else {
			printf("%s 입력 : ", head[i]);
			scanf("%[^\n]", ptr[i]);
			len = strlen(ptr[i]);
			ptr[i][len] = ' '; ptr[i][len + 1] = '\0';
		}
		getchar();
	}
	
	FILE* fp = fopen("test.txt", "a");
	
	for (i = 0; i < 4; i++) {
		fwrite(ptr[i], strlen(ptr[i]), 1, fp);
		fwrite("\n$", 2, 1, fp);
	}
	
	fclose(fp);
	FUNC* data = MakeNode(name, header, source, comment);
	AppendNode(root, data);
}
