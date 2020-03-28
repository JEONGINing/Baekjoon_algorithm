/*

나 쓸라고 만들어 본

원피스 랜덤 디펜스

첫 희귀 선택 도우미

*/


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int top5(int s[]) {
	int min = 100;
	int idx;
	for (int i = 0; i < 39; i++) {
		if (s[i] < min) { // 필요한 재료가 가장 적은 캐릭터부터 
			min = s[i];
			idx = i;
		}
	}
	return idx;
}

typedef struct _info
{
	char name[20]; // 캐릭터 이름
	int ch[9]; // 만드는데 필요한 재료 개수
} info;

int main(void)
{
	info id[39];
	ifstream fread;
	char str[50];

	fread.open("rare.txt"); // 데이터 호출
	int size = 0;
	while (!fread.eof()) { // 캐릭터 정보 입력
		fread.getline(str, 50);
		char* tok = strtok(str, " ");
		strcpy(id[size].name, tok); // 이름
		tok = strtok(NULL, " ");
		for (int i = 0; i < 9; i++) {
			id[size].ch[i] = atoi(tok); // 만드는데 필요한 재료 개수 입력
			tok = strtok(NULL, " ");
		}
		size++;
	}

	int input[9];

	printf("<<< 현시점 최적의 희귀 찾기 >>> \n\n");
	printf("루피 조로 나미 우솝 상디 초파 버기 총병 칼병 순으로 입력 -> ");

	for (int i = 0; i < 9; i++)
		scanf("%d", &input[i]); // 현재 보유한 재료 수 입력하면

	int sum[39] = { 0, };
	int store[39][9]; // 더 필요한 개수 저장

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 9; j++) {
			if (id[i].ch[j] - input[j] >= 0) {
				store[i][j] = id[i].ch[j] - input[j]; // 몇개가 모자란지 입력
			}
			else {
				store[i][j] = 0; // 딱 맞게 있거나 더 많으면 더이상 필요가 없음
			}
			sum[i] += store[i][j]; // 더 필요한 개수의 합이 얼마나 되는지 저장
		}
	}

	printf("\n\n");
	for (int i = 0; i < 5; i++) {
		int idx = top5(sum);
		int isAllZero = 1;
		printf("%d순위 %s: ", i + 1, id[idx].name); // 인덱스 가져와서 정보 입력
		for (int j = 0; j < 9; j++) {
			if (store[idx][j] == 0) { // 1개 이상인 캐릭터만 표시
				continue;
			}
			else {
				if (j == 0)
					printf("루피 %d개, ", store[idx][j]);
				else if (j == 1)
					printf("조로 %d개, ", store[idx][j]);
				else if (j == 2)
					printf("나미 %d개, ", store[idx][j]);
				else if (j == 3)
					printf("우솝 %d개, ", store[idx][j]);
				else if (j == 4)
					printf("상디 %d개, ", store[idx][j]);
				else if (j == 5)
					printf("초파 %d개, ", store[idx][j]);
				else if (j == 6)
					printf("버기 %d개, ", store[idx][j]);
				else if (j == 7)
					printf("총병 %d개, ", store[idx][j]);
				else if (j == 8)
					printf("칼병 %d개, ", store[idx][j]);
				isAllZero = 0; // 필요한 재료가 하나라도 있으면 isAllZero가 0
			}
		}

		if (isAllZero) // isAllZero가 1일 때
			printf("바로 만들 수 있음!\n\n");
		else
			printf("\n\n");

		sum[idx] = 999; // 재료 총합에 999 넣고 반복 (그 다음 적은 캐릭터 선택)
	}

	fread.close();
}
