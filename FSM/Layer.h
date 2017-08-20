#include <stdio.h>
#include <stdlib.h>

int FSM_getNumActTable(STATE_TABLE_t * FsmTable)
{
	return FsmTable->eventSize;
}

int FSM_getNumStateTable(STATE_TABLE_t * FsmTable)
{
	return sizeof(*FsmTable) / sizeof(STATE_TABLE_t);
}
