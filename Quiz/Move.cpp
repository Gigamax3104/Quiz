#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define QUIZ_MAX 10
#define MAX_SIZE 100
#define BACKSPACE 8
#define SQR(x) ((x * x)) //#define[スペース]関数名(仮引数)[スペース](処理)でマクロ関数を定義できる。
#include    <stdio.h>
#include	<stdlib.h>
#include	<cstdio>
#include	<time.h>
#include	<conio.h>
#include	<Windows.h>

//問題リスト
const char* Question[] = {
	"兎は何類\?",
	"ペットボトルは何で作られている\?",
	"テレビ番組で知られている青い猫型ロボットが主人公のタイトル名は\?",
	"キノコを食べて大きくなったり、踏んで敵を倒すといった要素がある超有名なゲームのタイトル名は\?",
	"現在の総理大臣は誰\?",
	"狐(キツネ)は英語でどう書く\?",
	"AIDS(後天性免疫不全症候群)は何によって引き起こされるでしょうか\?",
	"「走れメロス」という太宰治が筆記された小説がある。その中にあるメロスが走る場面があるが、その速さはどのくらいでしょうか\?",
	"2の3乗はいくつでしょうか\?",
	"石油ショックという社会現象がある。それが起きた年は何年でしょうか\?"
};

//答えリスト
const char* Answer[] = {
	"ほにゅうるい(哺乳類,mammalian,Mammalian)",
	"ぷらすちっく(プラスチック,plastic,Plastic)",
	"どらえもん(ドラえもん)",
	"まりお(マリオ,マリオ・マリオ)",
	"たかいちさなえ(高市早苗)",
	"Fox(fox)",
	"HIV(HIV,人免疫不全ウイルス)",
	"太陽の10倍の速さ(太陽の10倍,太陽の１０倍の速さ)",
	"8(８)",
	"1973年(1973,１９７３,１９７３年)"
};

//正解数によるメッセージ
const char* massage[] = {
	"素晴らしい！全問正解だ！",
	"結構やるじゃない！次は全問正解に向けて挑戦だ！",
	"そこそこだね。次はもう少し答えられるように頑張ろう！",
	"あ～...まぁ落ち込むことはないよ。これを覚えて今後につなげられることを期待しているよ！",
	"...。頑張れ。"
};

enum Massage {
	Perfect = 0,
	Great = 1,
	Good = 2,
	Bad = 3,
	Warst = 4
};

static bool progressTimer(int timer);
static bool quiz(int timer, int* QuestionList);
static void range(int* list);
static bool judge(const char* input,const char* answer);
static Massage judgementMassage(int total);

//外部リンケージにする関数
void quizGame(int timer) {
	int questionList[QUIZ_MAX];

	for (int i = 0; i < QUIZ_MAX;i++) {
		questionList[i] = i;
	}

	while (progressTimer(timer)) {
		range(questionList);
		if (!quiz(timer, questionList)) {
			break;
		}
	}
}

//10秒経過するまで処理する関数
static bool progressTimer(int timer) {
	time_t t = time(NULL);
	struct tm* now = localtime(&t);

	return
		now->tm_sec - timer >= 10 ? false : true;
}

//主に動作する関数
static bool quiz(int timer, int* QuestionList) {
	int total = 0;
	int i = 0;

	char key = ' ';
	char input[MAX_SIZE];

	int idx = 0;
	char key2[MAX_SIZE];
	char* p = key2;

	printf("\nクイズゲームへようこそ！ここでは5問のクイズに答えてもらうよ。早速行ってみよう！\n\n");

	do {

		while (i < QUIZ_MAX / 2) {
			int idx = 0;

			printf("第%d問！%s\n回答:", i + 1, Question[QuestionList[i]]);
			while ((key = getch()) != '\r') {
				char* p;

				if (key >= ' ' && key <= '~') {
					input[idx++] = key;
					p = &input[idx - 1];
				}
				else {
					input[idx] = key;
					idx += 2;
					p = &input[idx - 2];
				}

				if (key == BACKSPACE) {
					idx -= 2;
					input[idx] = '\0';
				}

				printf("%c", *p);
			}

			input[idx] = '\0';
			printf("\n");

			if (judge(input, Answer[QuestionList[i]])) {
				printf("正解！\n\n");
				total++;
			}
			else {
				printf("残念！正解は、%sでした！\n\n", Answer[QuestionList[i]]);
			}

			idx = 0;
			i++;

			if (!progressTimer(timer)) {
				break;
			}
		}

		printf("%s\n\n", massage[judgementMassage(total)]);

		if (!progressTimer(timer)) {
			break;
		}
		else if(i == QUIZ_MAX / 2){
			printf("もう一度挑戦しますか\?やめますか\?(挑戦→z : やめる→x)");

			do {
				while ((key = getch()) != '\r') {
					key2[idx++] = key;
					printf("%c", *p);
				}

			} while (*p != 'x' && *p != 'z');

			if (!progressTimer(timer)) {
				break;
			}
			else {
				printf("\n");
			}
		}
	
		i = 0;
		idx = 0;
		total = 0;
		range(QuestionList);

	} while (*p == 'z');

	return false;
}

//問題の出題順を決める関数
static void range(int* list) {
	srand((unsigned int)time(NULL));

	int idx = 0;
	int random = 0;
	int memory[QUIZ_MAX - 1];

	for (int i = QUIZ_MAX - 1; i > 1; i--) {
		random = rand() % (i - 1);

		if (idx > 0) {
			for (int i = 0; i < idx;) {

				if (list[random] != memory[i]) {
					i++;
				}
				else {
					random = rand() % (i - 1);
					i = 0;
				}
			}
		}

		memory[idx] = list[random];
		int save = list[i];
		list[i] = list[random];
		list[random] = save;
		idx++;
	}

	for (int i = 0; i < QUIZ_MAX; i++) {
		printf("%d", list[i]);
	}
}

//回答と解答との判断をする関数
static bool judge(const char* input, const char* answer) {
	const char* save = input;

	while (*answer) {
		if (strncmp(input,answer,1) == 0) {

			answer++;
			if (*input >= ' ' && *input <= '~') {
				input++;
			}
			else {
				input += 2;
			}

			if (*input == '\0' && (strncmp(answer, ",",1) == 0|| strncmp(answer, "(",1) == 0 
								   || strncmp(answer, ")",1) == 0 || *answer == '\0')) {

				return true;
			}
		}
		else if (strncmp(input,answer,1) != 0) {
			while (strncmp(answer, ",",1) != 0 && strncmp(answer, "(",1) != 0) {
				answer++;

				if (*answer == '\0') {
					return false;
				}
			}

			input = save;
			answer++;
		}
		else if (*input == '\0') {
			return false;
		}
	}

	return false;
}

//正解数で決まる関数
static Massage judgementMassage(int total) {
	return
		total == 5 ? Perfect :
		total == 4 ? Great :
		total >= 2 && total <= 3 ? Good :
		total == 1 ? Bad : Warst;
}
