#include <stdio.h>

// ? 未定义
#define INIT_TIMEOUT

typedef enum {
	UP_SIG,
	DOWN_SIG,
	ARM_SIG,
	TICK_SIG,
} bomb_signal;

typedef enum {
	SETTING_STATE,
	TIMING_STATE,
} bomb_state;

typedef struct bomb_s {
	int timeout;
	int code;
	int fine_time;
} bomb_t;

void bomb_create(bomb_t *bomb, int code)
{
	bomb.code = code;
}

void bomb_init(bomb_t *bomb)
{
	bomb.timeout = INIT_TIMEOUT;
}

void state_setting()
{

}

void state_timing()
{

}

void main()
{
	bomb_create();
	bomb_init();
}
