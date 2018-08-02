#pragma once
#define DELI '$'
#define DELIS "$"
/*구조체 선언 FUNC*/
typedef struct _FUNC {
	char name[20];			/* 함수 명*/
	char header[20];		/* 해더 명*/
	char source[1000];		/* 소스 내용*/
	char comment[200];		/* 코멘트*/
	struct _FUNC* next;		
} FUNC;

FUNC* MakeData(char* data);
FUNC* MakeNode(char *name, char *header, char *source, char *comment);
FUNC* FindNode(FUNC* root, char* name);
FUNC* AppendNode(FUNC* root, FUNC* newNode);
void Print(FUNC* root);
