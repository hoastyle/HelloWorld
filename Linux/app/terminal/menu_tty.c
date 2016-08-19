#include <stdio.h>
#include <stdlib.h>

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);

/* 
 * 1. 显示菜单
 * 2. 选择
 * 3. 选择和菜单对比
 * 4. 如果有，输出。如果没有，则报错
 * 5. 如果为q，则退出
 * */
int main()
{
	int choice;
	FILE *input;
	FILE *output;

	//测试输出是否和终端相连
	if (!isatty(fileno(stdout))) {
		fprintf(stderr, "You are not a terminal\n");
	}

	input = fopen("/dev/tty", "r");
	output = fopen("/dev/tty", "w");
	if (!input || !output)
		fprintf(stderr, "Unable to open /dev/tty\n");

	do {
		choice = getchoice("Please select an action:", menu);
		printf("You have chosen %c\n", choice);
	} while (choice != 'q');

	return 0;
}

int getchoice(char *greet, char *choices[])
{
	char **option;
	int choice;
	int chosen = 0;
	option = choices;

	printf("%s\n", greet);


	while (*option) {
		printf("%s\n", *option);
		option++;
	}

	do {
		choice = getchar();
	} while (choice == '\n');
	option = choices;
	while (*option) {
		if (choice == *option[0]) {
			chosen = 1;
			break;
		}
		option++;
	}

	if (chosen != 1)
		printf("incorrect choice, select again\n");

	return choice;
}
