#include <stdio.h>

typedef void (*ActFun)(void *);

typedef struct ACT_TABLE_s {
	int event;
	ActFun eventActFun;
} ACT_TABLE_t;

typedef struct STATE_TABLE_s
{                           
    int state;              
    ACT_TABLE_t *StateTable;
} STATE_TABLE_t;            

int FSM_getNumActTable(ACT_TABLE_t *pActTable)      
{                                                   
    return sizeof(*pActTable) / sizeof(ACT_TABLE_t);
}

int FSM_getNumStateTable(STATE_TABLE_t *FsmTable)
{
    return sizeof(*FsmTable) / sizeof(STATE_TABLE_t);
}

