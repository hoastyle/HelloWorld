#ifndef __MULTILAYER_H__
#define __MULTILAYER_H__

typedef enum {
	L1_STATE1,
	L1_STATE2,
	L1_STATE3,
	L2_STATE1,
	L2_STATE2,
} STATE_t;

typedef enum {
	L1_EVENT1,
	L1_EVENT2,
	L1_EVENT3,
	L2_EVENT1,
	L1_L2_EVENT1,
	L1_L2_EVENT2,
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

char *s_state[5] =
    { "L1_STATE1", "L1_STATE2", "L1_STATE3", "L2_STATE1", "L2_STATE2" };
char *s_event[6] =
    { "L1_EVENT1", "L1_EVENT2", "L1_EVENT3", "L2_EVENT1", "L1_L2_EVENT1",
	"L1_L2_EVENT2"
};

#endif
