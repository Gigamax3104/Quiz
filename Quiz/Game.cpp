#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include "List.h"

enum State {
	Quiz = 1,
	NumberHit = 2
};
int main() {
	int choice = 0;
	time_t t = time(NULL);
	struct tm* now = localtime(&t);

	printf("選択してください。(1 : クイズゲーム、 2 : 数当てゲーム) それ以外を入力しますと強制終了します。>");
	scanf("%d", &choice);

	switch (choice) {
		case Quiz:
			quizGame(now->tm_sec); break;
		case NumberHit:
			numberHitGame(); break;
	}
}

