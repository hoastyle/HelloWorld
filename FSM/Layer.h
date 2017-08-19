#include <stdio.h>
#include <stdlib.h>

typedef void (*ActFun) (void *);

typedef struct ACT_TABLE_s {
	int event;
	ActFun eventActFun;
} ACT_TABLE_t;

typedef struct STATE_TABLE_s {
	int state;
	int eventSize;
	ACT_TABLE_t *StateTable;
} STATE_TABLE_t;

int FSM_getNumActTable(STATE_TABLE_t * FsmTable)
{
	return FsmTable->eventSize;
}

int FSM_getNumStateTable(STATE_TABLE_t * FsmTable)
{
	return sizeof(*FsmTable) / sizeof(STATE_TABLE_t);
}
