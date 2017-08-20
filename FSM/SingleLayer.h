#ifndef __SINGLELAYER_H__
#define __SINGLELAYER_H__

typedef enum {
	STATE1,
	STATE2,
	STATE3,
} STATE_t;

typedef enum {
	EVENT1,
	EVENT2,
	EVENT3,
} EVENT_t;

typedef void (*ActFun) (void *);

typedef struct ACT_TABLE_s {
	EVENT_t event;
	ActFun eventActFun;
} ACT_TABLE_t;

typedef struct STATE_TABLE_s {
	STATE_t state;
	int eventSize;
	ACT_TABLE_t *StateTable;
} STATE_TABLE_t;

char *s_state[3] = { "STATE1", "STATE2", "STATE3" };

#endif
