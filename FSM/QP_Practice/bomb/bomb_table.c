/* Bomb implementation by FSM in table way */
/* More things to do 
 * - Add multi task to handle all these?
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/kbhit.h"

#define INIT_TIMEOUT 10

#define TRAN(bomb, target) (bomb->curState = target)

void bomb_boom();

/* Signal */
typedef enum {
	UP_SIG,
	DOWN_SIG,
	ARM_SIG,
	TICK_SIG,
} bomb_signal;

/* State */
typedef enum {
	SETTING_STATE,
	TIMING_STATE,
} bomb_state;

struct bomb_s;
typedef struct bomb_s bomb_t;

/* Root event */
typedef struct event_s {
	int sig;
} event_t;

typedef struct tick_event_s {
	event_t super;
	int fine_time;
} tick_event_t;

typedef void (*act_func) (bomb_t * bomb, event_t * e);

typedef struct event_map_s {
	int event;
	act_func event_act_func;
} event_map_t;

typedef struct state_map_s {
	int state;
	int event_size;
	event_map_t *event_table;
} state_map_t;

typedef struct bomb_s {
	state_map_t *bomb_table;
	int timeout;
	int code;
	int defcode;
	bomb_state curState;
} bomb_t;

void setting_up_func(bomb_t * bomb, event_t * e)
{
	if (bomb->timeout < 60) {
		++bomb->timeout;
		printf("timeout is %d\n", bomb->timeout);
	}
}

void setting_down_func(bomb_t * bomb, event_t * e)
{
	if (bomb->timeout > 0) {
		--bomb->timeout;
		printf("timeout is %d\n", bomb->timeout);
	}
}

void setting_arm_func(bomb_t * bomb, event_t * e)
{
	bomb->code = 0;
	TRAN(bomb, TIMING_STATE);
	printf("Enter count down state\n");
}

void timing_up_func(bomb_t * bomb, event_t * e)
{
	bomb->code <<= 1;
	bomb->code |= 1;
}

void timing_down_func(bomb_t * bomb, event_t * e)
{
	bomb->code <<= 1;
}

void timing_arm_func(bomb_t * bomb, event_t * e)
{
	if (bomb->code == bomb->defcode) {
		TRAN(bomb, SETTING_STATE);
		printf("\n\n\nThe boom was successfully lifted!\n");
		printf("Back to setting state\n\n\n");
	} else {
		printf("\n\n\nFailed!\n\n\n");
		bomb->code = 0;
	}
}

void timing_tick_func(bomb_t * bomb, event_t * e)
{
	if (((tick_event_t *) e)->fine_time == 0) {
		--bomb->timeout;
		printf("\nCount down: timeout is %d", bomb->timeout);
		if (bomb->timeout == 0)
			bomb_boom();
	}
}

/* These three array can be merged, please refer to example table in following code */
event_map_t setting_table[] = {
	{UP_SIG, setting_up_func}
	,
	{DOWN_SIG, setting_down_func}
	,
	{ARM_SIG, setting_arm_func}
	,
};

event_map_t timing_table[] = {
	{UP_SIG, timing_up_func}
	,
	{DOWN_SIG, timing_down_func}
	,
	{ARM_SIG, timing_arm_func}
	,
	{TICK_SIG, timing_tick_func}
	,
};

state_map_t bomb_state_table[] = {
	{SETTING_STATE, sizeof(setting_table) / sizeof(event_map_t),
	 setting_table}
	,
	{TIMING_STATE, sizeof(timing_table) / sizeof(event_map_t), timing_table}
	,
};

/* Example table */
/*
typedef void (*Tran)(struct StateTableTag *me, Event const *e);

static const Tran bomb2_state_table[MAX_STATE][MAX_SIG] = {
    { (Tran)&Bomb2_setting_UP,  (Tran)&Bomb2_setting_DOWN, 
      (Tran)&Bomb2_setting_ARM, &StateTable_empty },       
    { (Tran)&Bomb2_timing_UP,   (Tran)&Bomb2_timing_DOWN,  
      (Tran)&Bomb2_timing_ARM,  (Tran)&Bomb2_timing_TICK  }
}; 
*/

/* Construct function */
void bomb_create(bomb_t * bomb, int code)
{
	bomb->defcode = code;
}

void bomb_init(bomb_t * bomb)
{
	bomb->bomb_table = bomb_state_table;
	bomb->timeout = INIT_TIMEOUT;
	TRAN(bomb, SETTING_STATE);
}

void bomb_boom()
{
	printf("\n|||||||||||||||||||\
		    \n|------BOOM-------|\
			\n|-----------------|\
			\n|||||||||||||||||||\n");
	exit(0);
}

void bomb_dispatch(bomb_t * bomb, event_t * e)
{
	act_func t;
	state_map_t state;
	event_map_t event;
	//   assert(e->sig < me->n_signals);          /* require the signal in range */
	if (e->sig == 3 && bomb->curState == 0)
		goto error;
	state = bomb->bomb_table[bomb->curState];
	event = state.event_table[e->sig];
	t = event.event_act_func;
	//t = bomb->bomb_table[bomb->curState].event_table[e->sig].event_act_func;
	(*t) (bomb, e);		/* execute the transition function */
	//    assert(me->state < me->n_states);   /* ensure that state stays in range */
 error:
	return;
}

void main()
{
	bomb_t bomb;
	event_t *e = (event_t *) 0;

	static event_t up_evt = { UP_SIG };
	static event_t down_evt = { DOWN_SIG };
	static event_t arm_evt = { ARM_SIG };

	bomb_create(&bomb, 8);
	bomb_init(&bomb);

	printf("Time Bomb (Nested switch)\n"
	       "Press 'u'   for UP   event\n"
	       "Press 'd'   for DOWN event\n"
	       "Press 'a'   for ARM  event\n" "Press <Esc> to quit.\n");

	for (;;) {
		// Question: 是否可以使用timer interrupt
		static tick_event_t tick_evt = { TICK_SIG, 0 };

		// 100ms
		usleep(100000);

		/* Reduce coupling */
		if (++tick_evt.fine_time == 10)
			tick_evt.fine_time = 0;

		bomb_dispatch(&bomb, (event_t *) & tick_evt);

		/* contruct event */
		/* 只有输入的时候才停下 */
		if (kbhit()) {
			switch (getchar()) {
			case 'u':{
					printf("\nUP: ");
					e = &up_evt;
					break;
				}
			case 'd':{
					printf("\nDOWN: ");
					e = &down_evt;
					break;
				}
			case 'a':{
					printf("\nARM: ");
					e = &arm_evt;
					break;
				}
			case '\33':{
					printf("\nESC: ");
					fflush(stdout);
					exit(0);
					break;
				}
			}

			if (e != (event_t *) 0) {
				bomb_dispatch(&bomb, e);
			}
		}
	}
}
