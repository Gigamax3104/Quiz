#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const int INPUT_MAX = 99;

const char* Question[] = {
	"兎は何類\?",
	"ペットボトルは何で作られている\?",
	"テレビ番組で知られている青い猫型ロボットが主人公のタイトル名は\?",
	"キノコを食べて大きくなったり、踏んで敵を倒すといった要素がある超有名なゲームのタイトル名は\?",
	"現在の総理大臣は誰\?"
};

const char* Answer[] = {
	"哺乳類",
	"プラスチック",
	"ドラえもん",
	"マリオ",
	"高市早苗"
};

void Move();
bool Judge(const char* input,const char* answer);

int main() {
	Move();
}

void Move() {
	int total = 0;
	char input[INPUT_MAX] = "";

	int size = sizeof Question / sizeof Question[0];

	printf("クイズゲームへようこそ！ここでは5問のクイズに答えてもらうよ。早速行ってみよう！\n\n");

	for (int i = 0; i < size; i++) {
		printf("第%d問！%s\n回答:",i + 1,Question[i]);
		scanf("%s",input);

		if (Judge(input,Answer[i])) {
			printf("正解！\n\n");
			total++;
		}
		else {
			printf("残念！正解は%sでした！\n\n", Answer[i]);
		}
	}

	printf("やったね！%d問正解したよ！",total);
}

bool Judge(const char* input,const char* answer) {
	while (*answer) {
		if (*input == *answer) {
			answer++;
			input++;
		}
		else if(*input != *answer || *input == '\0'|| *answer == '\0') {
			return false;
		}
	}

	return true;
}
