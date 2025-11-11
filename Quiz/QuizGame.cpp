#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "List.h"

int main() {
	int choice = 0;

	printf("選択してください。(1 : クイズゲーム、 2 : 数当てゲーム) それ以外を入力しますと強制終了します。>");
	scanf("%d", &choice);

	switch (choice) {
		case 1:
			Move(); break;
		case 2:
			Move2(); break;
	}
}

