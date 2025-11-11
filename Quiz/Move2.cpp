#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <ctime>

enum JudgeMassage {
	Large = 0,
	LittleLarge = 1,
	LittleShort = 2,
	Short = 3,
	Hit = 4
};

const char* Massage[] = {
	"‚à‚Á‚Æ‘å‚«‚¢‚ºI",
	"‚à‚¤‚¿‚å‚Á‚Æ‘å‚«‚¢‚ñ‚¾‚æ‚È`B",
	"‚à‚¤‚¿‚å‚Á‚Æ¬‚³‚¢‚ñ‚¾‚æ‚È`B",
	"‚à‚Á‚Æ¬‚³‚¢‚ºI",
	"‘å`“–‚½‚Ÿ`‚è`II"
};

static bool Judge(int input,int answer);
static JudgeMassage JudgeTell(int input,int answer);

void Move2() {
	srand((unsigned int)time(NULL));

	const int Range = 100;
	int RandomNumber = rand() % Range + 1;
	int turn = 1;
	int Input = 0;

	printf("\n”“–‚ÄƒQ[ƒ€‚Ö‚æ‚¤‚±‚»I‚±‚±‚Å‚ÍŽ„‚ªŽv‚¢•‚‚©‚×‚Ä‚¢‚é”Žš‚ð“–‚Ä‚Ä‚¢‚½‚¾‚«‚Ü‚·I‚Å‚Ís‚Á‚Ä‚Ý‚Ü‚µ‚å‚¤I\n");
	printf("(‚¿‚È‚Ý‚ÉA”Žš‚Í1`99‚Ü‚Å‚Ì’†‚Å‚·B)\n");

	do {
		printf("%d‰ñ–Ú>", turn);
		scanf("%d", &Input);

	} while (Judge(Input,RandomNumber));
}

static bool Judge(int input,int answer) {
	JudgeMassage JM = JudgeTell(input, answer);
	printf("%s\n\n", Massage[JM]);

	switch (JM) {
		case Large:
		case LittleLarge:
		case LittleShort:
		case Short:
			return true; break;
		default:
			return false; break;
	}
}

static JudgeMassage JudgeTell(int input, int answer) {
	return
		answer - input >= 20 ? Large :
		(answer - input > 0 && answer - input < 20) ? LittleLarge :
		(answer - input > -20 && answer - input < 0) ? LittleShort :
		answer - input <= -20 ? Short : Hit;
}
