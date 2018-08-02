#include "list.h"
#include <stdio.h>

int main() {

	FILE* fp = fopen("test.txt", "r");
	FUNC* root = NULL, *tmp;
	char buf[1400] = { 0 };
	char temp[1400] = { 0 };
	char name[100] = { 0 };
	int cnt = 0;
	int deli_cnt = 0;	
	int n;
	int size;

	while ((buf[cnt] = fgetc(fp)) != EOF) {
		if (buf[cnt++] == DELI) {
			deli_cnt++;  // 컬럼 수 체크
			buf[cnt - 2] = ' ';
		}
		if (deli_cnt == 4) {
			buf[cnt - 2] = ' ';
			buf[cnt] = '\0';
			// MakeData 데이터를 구조체에 저장한다.
			FUNC* ptr = MakeData(buf);
			tmp = AppendNode(root, ptr);
			// root 일 경우만 주소값 리턴.
			if (tmp != NULL) root = tmp;
			deli_cnt = 0;
			cnt = 0;
			continue;
		}
	}
	fclose(fp);
																				WriteData(root);
																				while (1) {
		printf("검색할 명령어를 입력하세요 : ");
		scanf("%s", name);
		printf("--------------------------------\n");
		tmp = FindNode(root, name);
		printf("결과\n");
		if (tmp != NULL) {
			Print(tmp);
		}
		else {
			printf("%s 명령어가 없습니다\n", name);
		}
	}
																				return 0;
}
