#include <stdio.h>
#include <stdlib.h>

/* for kbhit */
#include <termios.h>  
#include <unistd.h>  
#include <fcntl.h> 

#define INIT_TIMEOUT 10

#define TRAN(bomb, target) (bomb->curState = target)

int kbhit(void)  
{  
	struct termios oldt, newt;  
	int ch;  
	int oldf;  

	tcgetattr(STDIN_FILENO, &oldt);  
	newt = oldt;  
	newt.c_lflag &= ~(ICANON | ECHO);  
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);  
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);  
	ch = getchar();  
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
	fcntl(STDIN_FILENO, F_SETFL, oldf);  

	if(ch != EOF)  
	{  
	  ungetc(ch, stdin);  
	  return 1;  
	}  
	return 0;  
} 

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

/* Root event */
typedef struct event_s {
	int sig;
} event_t;

typedef struct tick_event_s {
	event_t super;
	int fine_time;
} tick_event_t;

typedef struct bomb_s {
	int timeout;
	int code;
	int defcode;
	bomb_state curState;
} bomb_t;

/* Construct function */
void bomb_create(bomb_t *bomb, int code)
{
	bomb->defcode = code;
}

void bomb_init(bomb_t *bomb)
{
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

/* This function can also be implemented by table */
void bomb_dispatch(bomb_t *bomb, event_t *e)
{
	switch (bomb->curState) {
		case SETTING_STATE: {
			switch (e->sig) {
				/* 不引起状态变化 */
				case UP_SIG:
					if (bomb->timeout < 60) {
						++bomb->timeout;
						printf("timeout is %d\n", bomb->timeout);
					}
					break;
				case DOWN_SIG:
					if (bomb->timeout > 0) {
						--bomb->timeout;
						printf("timeout is %d\n", bomb->timeout);
					}
					break;
				/* 引起状态变化 */
				case ARM_SIG: 
					bomb->code = 0;
					TRAN(bomb, TIMING_STATE);
					printf("Enter count down state\n");
					break;
			}
			break;
		}

		case TIMING_STATE: {
			switch (e->sig) {
				case UP_SIG: {
					bomb->code <<= 1;
					bomb->code |= 1;
					break;
				}
				case DOWN_SIG: {
					bomb->code <<= 1;
					break;
				}
				case ARM_SIG: {
					if (bomb->code == bomb->defcode) {
						TRAN(bomb, SETTING_STATE);
						printf("\n\n\nThe boom was successfully lifted!\n");
						printf("Back to setting state\n\n\n");
					} else {
						printf("\n\n\nFailed!\n\n\n");
						bomb->code = 0;
					}
					break;
				}
				case TICK_SIG: {
					if (((tick_event_t *)e)->fine_time == 0) {
						--bomb->timeout;
						printf("\nCount down: timeout is %d", bomb->timeout);
						if (bomb->timeout == 0)
							bomb_boom();
					}
					break;
				}
			}
			break;
		}
	}
}

void main()
{
	bomb_t bomb;
	event_t *e = (event_t *)0;

	static event_t up_evt   = { UP_SIG   };
	static event_t down_evt = { DOWN_SIG };
	static event_t arm_evt  = { ARM_SIG  };

	bomb_create(&bomb, 8);
	bomb_init(&bomb);

	printf("Time Bomb (Nested switch)\n"
			"Press 'u'   for UP   event\n"
			"Press 'd'   for DOWN event\n"
			"Press 'a'   for ARM  event\n"
			"Press <Esc> to quit.\n");

	for (;;) {
		// Question: 是否可以使用timer interrupt
		static tick_event_t tick_evt = { TICK_SIG, 0 };	

		// 100ms
		usleep(100000);

		/* Reduce coupling */
		if (++tick_evt.fine_time == 10)
			tick_evt.fine_time = 0;

		bomb_dispatch(&bomb, (event_t *)&tick_evt);

		/* contruct event */
		/* 只有输入的时候才停下 */
		if (kbhit()) {
			switch (getchar()) {
				case 'u': {
					printf("\nUP: ");
					e = &up_evt;
					break;
				}
				case 'd': {
					printf("\nDOWN: ");
					e = &down_evt;
					break;
				}
				case 'a': {
					printf("\nARM: ");
					e = &arm_evt;
					break;
				}
				case '\33': {
					printf("\nESC: ");
					fflush(stdout);
					exit(0);
					break;
				}
			}

			if (e != (event_t *)0) {
				bomb_dispatch(&bomb, e);
			}
		}
	}
}
