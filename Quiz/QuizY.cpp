#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define Q_MAX 10
#define Q_CMAX 5
#define Q_TIME 10
#define BACKSPACE 8
#define ENTER 13
#include <stdio.h>
#include<stdlib.h>
#include <cstring>
#include<conio.h>
#include<time.h>;
#include<windows.h>

static int score = 0;
void game();
bool cmpRand(int i, int r, const int* rArr);
void cmp(const char* input, const char* ans);
bool retry();
void result(int qCount, int score);
void cursor(int x);
void clear();


int main()
{
	game();
}
void game()
{
	int i = 0;
	srand((unsigned int)time(NULL));

	char q[Q_MAX][256] =
	{
		{ "2020年に発売され、ヒットしたNintendo Switchのゲーム「〇〇〇〇 どうぶつの森」。〇〇〇〇に入る言葉は？"},
		{ "2010年代にスマートフォンでヒットしたソーシャルゲーム「パズドラ」の正式名称は？" },
		{ "2000年代にガラケーでヒットした、自転車に乗った棒人間を操作して遊ぶゲームの名称は？" },
		{ "1990年代にゲームセンターに設置され、ブームとなった写真シール機「プリクラ」の正式名称は？"},
		{ "1980年代に大ヒットした家庭用ゲーム機「ファミコン」の正式名称は？" },
		{"セガのキャラクター「ソニック」の元になった動物は？（カタカナで）"},
		{"1998年にゲームセンターで稼働した矢印を踏む音楽ゲーム「DDR」、「ダンレボ」の正式名称は？（カタカナで）"},
		{"「11（10進数）」の2進数は？"},
		{"「10010（2進数）」の10進数は？"},
		{"5 × 6 ＋ 8 ÷ 2 = ？"}
	};
	char ans[Q_MAX][256] =
	{
		{ "あつまれ"},
		{"パズル＆ドラゴンズ"},
		{"チャリ走"},
		{"プリント倶楽部"},
		{"ファミリーコンピュータ"},
		{"ハリネズミ"},
		{"ダンスダンスレボリューション"},
		{"1011"},
		{"18"},
		{"34"}
	};
	time_t sTimer;
	time_t cTimer;
	char input[256];
	char inpChar = '\0';
	int inpLen;
	int r;
	int rArr[Q_CMAX];
	for (i = 0; i < Q_CMAX; i++)
	{

		clear();
		sTimer = time(NULL);
		while (true)
		{
			r = rand() % Q_MAX;
			if (i > 0)
			{
				if (!cmpRand(i, r, rArr))
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		rArr[i] = r;
		sTimer;
		printf("\n%d / %d 問目\n", i + 1, Q_CMAX);
		printf("%s\n", q[r]);
		inpLen = 0;
		input[0] = '\0';

		while (true)
		{
			cTimer = time(NULL);
			cursor(4); // ↓4行目以降
			printf("%s", input);
			if (kbhit()) // キーが押されたら
			{
				inpChar = getch();
				if (inpChar == BACKSPACE)
				{
					if (inpLen > 0)inpLen--;
					input[inpLen] = '\0';
				}
				else if (inpChar == ENTER)
				{
					break;
				}
				else
				{
					if (inpLen < 256)
					{
						input[inpLen] = inpChar;
						inpLen++;
						input[inpLen] = '\0';
					}
				}
			}
			if (cTimer - sTimer > Q_TIME)
			{
				printf("時間切れ");
				return;
			}
			Sleep(50);
		}
		cmp(input, ans[r]);
		if (i + 1 == Q_CMAX || !retry())
		{
			result(i + 1, score);
			return;
		}
	}
}
bool cmpRand(int i, int r, const int* rArr) // 前のループで出てきた問題かチェック
{
	for (int j = 0; j < i; j++)
	{
		if (r == rArr[j])
		{
			return true;
		}
		else
		{

		}
	}
	return false;
}
void cmp(const char* input, const char* ans) // 回答と答えの比較
{
	if (strcmp(input, ans) == 0)
	{
		printf("正解です。\n\n");
		score++;
	}
	else
	{
		printf("間違いです。正しい答えは、%s\n\n", ans);
	}
}
bool retry() // リトライするかどうか
{
	char key = '\0';

	printf("もう一度挑戦する？ yes:y, no:n");
	while (true)
	{
		if (kbhit()) key = getch();
		if (key == 'y')
		{

			return true;
		}
		else if (key == 'n')
		{
			return false;
		}
		else
		{

		}
	}
}
void result(int qCount, int score) // 結果を表示
{
	const char* resultStr[] =
	{
		"Poor",
		"Bad",
		"Good",
		"Great!",
		"Perfect!!",
		"Marvelous!!!",
	};

	printf("\n%d 問中%d 問正解", qCount, score);
	printf("\n%s", resultStr[score]);
}
void cursor(int y)
{
	printf("\x1b[%dH", y);	// カーソルをy行に移動
}
void clear()
{
	printf("\x1b[2J\x1b[H"); // 画面上の文字を消してカーソルを一番最初の行に移動する
}