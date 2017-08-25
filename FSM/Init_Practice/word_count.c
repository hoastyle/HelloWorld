/* Implement function to count number of word based on state machine */
/* 
 *	State Machine
 *
 *		  		OUT IN
 *	Empty 		OUT OUT
 *	Not Empty   IN  IN
 */

#include <stdio.h>

typedef enum {
	OUT,
	IN,
} state_t;

typedef struct fsm_s {
	state_t cur_state;
	int count;
} fsm_t;

void fsm_init(fsm_t *fsm, state_t state)
{
	fsm->cur_state = state;
	fsm->count = 0;
}

void fsm_word(fsm_t *fsm, char c)
{
	state_t state;
	int count = 0;

	state = fsm->cur_state;
	count = fsm->count;

	if (state == OUT) {
		if (c == ' ' || c == '\t')
			state = OUT;
		else {
			state = IN;
			count++;
		}
	} else {
		if (c != ' ' && c != '\t')
			state = IN;
		else {
			state = OUT;
		}
	}

	fsm->cur_state = state;
	fsm->count = count;
}

void main(void)
{
	char c;
	
	fsm_t fsm;
	fsm_init(&fsm, OUT);
	while ( scanf("%c", &c) != EOF && c != '\n' )
		fsm_word(&fsm, c);

	printf("单词个数: %d\n", fsm.count);
	return;
}
