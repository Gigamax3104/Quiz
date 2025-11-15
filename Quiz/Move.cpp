#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define QUIZ_MAX 10
#define SQR(x) ((x * x)) //#define[スペース]関数名(仮引数)[スペース](処理)でマクロ関数を定義できる。
#include    <stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<conio.h>
#include	<Windows.h>

const int INPUT_MAX = 99;

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

const char* Answer[] = {
	"ほにゅうるい(哺乳類,mammalian,Mammalian)",
	"ぷらすちっく(プラスチック,plastic,Plastic)",
	"どらえもん(ドラえもん)",
	"まりお(マリオ,マリオ・マリオ)",
	"たかいちさなえ(高市早苗)",
	"Fox(fox)",
	"HIV(人免疫不全ウイルス)",
	"太陽の10倍の速さ(太陽の10倍)",
	"8",
	"1973年(1973)"
};

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

static bool ProgressTimer(int timer);
static void Quiz(int total,int timer, int* QuestionList);
static void Range(int* list);
static bool Judge(const char* input, const char* answer);
static Massage JM(int total);

void Move(int timer) {
	int total = 0;
	int* QuestionList = new int[QUIZ_MAX];


	//while (true) {
		//if (ProgressTimer(timer)) {
			Range(QuestionList);
			Quiz(total,timer, QuestionList);
		//}
		//else {
		//	break;
		//}
	//}
	delete[] QuestionList;
}

static bool ProgressTimer(int timer) {
	time_t t = time(NULL);
	struct tm* now = localtime(&t);

	return
		now->tm_sec - timer >= 10 ? false : true;
}

static void Quiz(int total,int timer, int* QuestionList) {
	int i = 0;
	char key = ' ';
	char key2 = ' ';

	printf("\nクイズゲームへようこそ！ここでは5問のクイズに答えてもらうよ。早速行ってみよう！\n\n");

	do {
		char input1[] = "";

		while (i < QUIZ_MAX / 2) {
			//int idx = 0;
			//char input2[] = "";

			printf("第%d問！%s\n回答:", i + 1, Question[QuestionList[i]]);
			scanf("%s", &input1);
			//while ((key = getch()) != '\r') {
			//	input2[idx++] = key;
			//	char* p = &input2[idx - 1];
			//	printf("%c", *p);
			//}

			//input2[idx] = '\0';
			printf("\n");

			if (Judge(input1, Answer[QuestionList[i]])) {
				printf("正解！\n\n");
				total++;
			}
			else {
				printf("残念！正解は、%sでした！\n\n", Answer[QuestionList[i]]);
			}

			//idx = 0;
			i++;

			//if (!ProgressTimer(timer)) {
			//	break;
			//}
		}

		printf("%s\n\n", massage[JM(total)]);

		//if (!ProgressTimer(timer)) {
		//	break;
		//}
		//else if(i == QUIZ_MAX / 2){
			printf("もう一度挑戦しますか\?やめますか\?(挑戦→z : やめる→x)");

			//int idx = 0;
			//char save[] = "";

			do {
				scanf("%c", &key);
				//while ((key2 = getch()) != '\r') {
				//	save[idx++] = key2;
				//	char* p = &key2;
				//	printf("%c", *p);
				//}

				//save[idx] = '\0';

				//if (!ProgressTimer(timer)) {
				//	break;
				//}

			} while (key != 'x' && key != 'z');

			//if (!ProgressTimer(timer)) {
			//	break;
			//}
			//else {
				printf("\n");
			//}
		//}
	
				i = 0;
	} while (key == 'z');
}

static void Range(int* list) {
	srand((unsigned int)time(NULL));

	list[0] = rand() % QUIZ_MAX;

	for (int i = 1; i < QUIZ_MAX; i++) {
		list[i] = rand() % QUIZ_MAX;

		for (int j = 0; j < i;) {
			if (list[j] == list[i]) {
				j = 0;
				list[i] = rand() % QUIZ_MAX;
			}
			else {
				j++;
			}
		}
	}
}

static bool Judge(const char* input, const char* answer) {
	const char* save = input;

	while (*answer) {
		if (*input == *answer) {
			answer++;
			input++;

			if (*input == '\0' && (*answer == ',' || * answer == '(' || *answer == ')' || *answer == '\0')) {
				return true;
			}
		}
		else if (*input != *answer) {
			while (*answer != ',' && *answer != '(') {
				answer++;

				if (*answer == '\0') {
					return false;
				}
			}

			input = save;
			answer++;
		}
		else if (*input == '\0' || *answer == '\0') {
			return false;
		}
	}
}

static Massage JM(int total) {
	return
		total == 5 ? Perfect :
		total == 4 ? Great :
		total >= 2 && total <= 3 ? Good :
		total == 1 ? Bad : Warst;
}
